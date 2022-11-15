/*
 * servo.c
 *
 *  Created on: Jul 28, 2021
 *      Author: fbalazs
 */

#include "servo.h"
#include "can_servo.h"
#include "tim.h"
#include "pwm.h"
#include "app.h"
#include "ppm.h"
#include "SPI_Comm_MSG_Struct.h"
#include "dd.h"
#include "config.h"
#include "rc_superv_logic.h"

#define MAF_coef (480u)
#define default_PWM_at_start (7500)
#define default_PWM_at_start_throttle (5000)
#define VTAIL_OFFSET (7500u)

/*These are just local handles with local numbering.
 * They all contain a "CH_ID" member, that's the global identifier, between all RX_MUXs.
 */
Servo_CH_Handle Servo_Handle_1;
Servo_CH_Handle Servo_Handle_2;
Servo_CH_Handle Servo_Handle_3;
Servo_CH_Handle Servo_Handle_4;
Servo_CH_Handle Servo_Handle_5;
Servo_CH_Handle Servo_Handle_6;
Servo_CH_Handle Servo_Handle_7;
Servo_CH_Handle Servo_Handle_8;
Servo_CH_Handle Servo_Handle_9;
Servo_CH_Handle Servo_Handle_10;
Servo_CH_Handle Servo_Handle_11;
Servo_CH_Handle Servo_Handle_12;


extern CANServo_Handle* hCANservos[];		//TODO cleanup extern definitions here, and at any related place
extern PWM_CH_Typedef* PWM_Channels[];

Servo_CH_Handle* Servo_Channels[NUM_OF_OUTPUT_CHANNELS] = {&Servo_Handle_1, &Servo_Handle_2, &Servo_Handle_3, &Servo_Handle_4, &Servo_Handle_5, &Servo_Handle_6, &Servo_Handle_7, &Servo_Handle_8, &Servo_Handle_9, &Servo_Handle_10, &Servo_Handle_11, &Servo_Handle_12} ;


/* --------------- prototypes ----------------------- */
uint16_t PWM_MAF(uint32_t* maf_State, uint16_t signal);
uint16_t Vtail2Rudder(uint16_t signal_r, uint16_t signal_l);


/*
 * Assign a CANServe handle to each Servo_channel handle.
 * Set signal to neutral
 */
void prepare_Servo_channels(void)
{
	for (int idx=0; idx<NUM_OF_OUTPUT_CHANNELS; idx++)
	{
		Servo_Channels[idx]->CANServo_handle = hCANservos[idx];
		Servo_Channels[idx]->signal = default_PWM_at_start;

		/* prepare storage varibale for the moving average filter. */
		Servo_Channels[idx]->PWM_MAF_state = default_PWM_at_start * MAF_coef;
	}
}



/* Initialize servo_CH. If needed initializes canServo and starts pwm channel. (based on config_status)
 * Updates actual_status to reflect what is actually usable.
 * Returns HAL_OK if actual_status matches config_status.
 * */

HAL_StatusTypeDef Servo_CH_init(Servo_CH_Handle* hservo_CH)
{

	hservo_CH->actual_status = none;
	uint8_t mode=none;
	if(hservo_CH->config_status!=none)
		mode= hservo_CH->config_status & 0b11;

	/* configure pwm related things if needed */
	if(mode==0)
	{

		/* init interpolation instance */
		hservo_CH->ppm_to_pwm_struct.nValues = ppm_lut_points;
		hservo_CH->ppm_to_pwm_struct.x1 = ppm_lut_min;
		hservo_CH->ppm_to_pwm_struct.xSpacing = ppm_lut_spacing;
		hservo_CH->ppm_to_pwm_struct.pYData = hservo_CH->PWM_LUT_values;

		/* set default PWM output
		 *  First check if it is flipased throttle channel */ //TODO erre kene valami hosszabb tavu megoldas

		if (hservo_CH->CH_ID == 19 && hservo_CH->PWM_CH == 10) {
			hservo_CH->signal = default_PWM_at_start_throttle;
			/* prepare storage varibale for the moving average filter. */
			hservo_CH->PWM_MAF_state = default_PWM_at_start_throttle * MAF_coef;

			/* og status set will fail if no PWM output is assigned (ie.: ECU), so we set it here */
			hservo_CH->actual_status = hservo_CH->config_status;
		}
		hservo_CH->current_pwm_out = (uint16_t)arm_linear_interp_f32( &(hservo_CH->ppm_to_pwm_struct), (float32_t)hservo_CH->signal);

		/* assign PWM handle
		 * PWM handle contains the output channel, but channel numbers start with 1
		 * Throttle channel might not have a PWM output, but we still need a logical channel.
		 */
		if (isValid_PWM_Channel(hservo_CH->PWM_CH) ) {
			hservo_CH->PWM_CH_handle = PWM_Channels[hservo_CH->PWM_CH - 1];

			PWM_UpdateOutput(hservo_CH->PWM_CH_handle, hservo_CH->current_pwm_out);

			/* start pwm */
			if(PWM_Start(hservo_CH->PWM_CH_handle) == HAL_OK){

				hservo_CH->actual_status = hservo_CH->config_status;
			}
			else {
				hservo_CH->actual_status=none;
			}
		}
	}

	/* configure CAN servo related things if needed. */
	if(mode==1 || mode==2)
	{
		/* copy default CAN servo values */
		CANServo_copy_default_setup(hservo_CH->CANServo_handle);

		/* set servo CAN id */
		hservo_CH->CANServo_handle->can_arb_id = hservo_CH->CAN_ID;
		/* set servo specific id */
		hservo_CH->CANServo_handle->id = hservo_CH->CAN_ID;

		/* assign CAN periphery */
		if (mode==1){
			hservo_CH->CANServo_handle->assigned_can = 1;
		}
		if (mode==2){
			hservo_CH->CANServo_handle->assigned_can = 2;
		}

		/* set limits on the CAN servo
		 * min max should be the smaller/bigger value, not the first/last in the array */
		if (hservo_CH->CAN_LUT_values[0] >  hservo_CH->CAN_LUT_values[2])
		{
			hservo_CH->CANServo_handle->init_struct.pos_max_limit = hservo_CH->CAN_LUT_values[0];
			hservo_CH->CANServo_handle->init_struct.pos_min_limit = hservo_CH->CAN_LUT_values[2];
		}
		else
		{
			hservo_CH->CANServo_handle->init_struct.pos_max_limit = hservo_CH->CAN_LUT_values[2];
			hservo_CH->CANServo_handle->init_struct.pos_min_limit = hservo_CH->CAN_LUT_values[0];
		}

		/* init interpolation instance */
		hservo_CH->ppm_to_deg_struct.nValues = ppm_lut_points;
		hservo_CH->ppm_to_deg_struct.x1 = ppm_lut_min;
		hservo_CH->ppm_to_deg_struct.xSpacing = ppm_lut_spacing;
		hservo_CH->ppm_to_deg_struct.pYData = hservo_CH->CAN_LUT_values;

		/* Run the initailaztion sequence for CAN servos
		 * 		If the watchdog caused the reset we don't need to reconfigure the CAN servos, the goal is to be back up and runing ASAP
		 */
		HAL_StatusTypeDef  can_init_status;
		if (!IWDG_Reset_FLAG)
		{
			/* normal inti */
			can_init_status = CANServo_init(hservo_CH->CANServo_handle);
		}
		else
		{
			/* dont actually run init, assume every can servo is already set up */
			can_init_status = HAL_OK;
		}
		/* update CAN servo status */
		if(can_init_status == HAL_OK)
		{
			/* update status */
			hservo_CH->actual_status = hservo_CH->config_status;

			/* set flag that there is a CAN servo in use */
			if (hservo_CH->CANServo_handle->assigned_can == 1){
				servoOnCAN1_FLAG = 1;
			}
			else if (hservo_CH->CANServo_handle->assigned_can == 2){
				servoOnCAN2_FLAG = 1;
			}
		}
		else
			hservo_CH->actual_status=none;
	}

	/* Configure CANopen and DD */
	if(mode==3)
	{

		if (DD_init() == CO_ERROR_NO)
		{
			hservo_CH->actual_status = hservo_CH->config_status;

			/* init interpolation instance */
			hservo_CH->ppm_to_deg_struct.nValues = ppm_lut_points;
			hservo_CH->ppm_to_deg_struct.x1 = ppm_lut_min;
			hservo_CH->ppm_to_deg_struct.xSpacing = ppm_lut_spacing;
			hservo_CH->ppm_to_deg_struct.pYData = hservo_CH->CAN_LUT_values;

			DD_object.CO_node_ID	= hservo_CH->CAN_ID;
		}
		else
			hservo_CH->actual_status=none;
	}

	/* return */
	if (hservo_CH->actual_status == hservo_CH->config_status)
	{
		return HAL_OK;
	}
	else
	{
		return HAL_ERROR;
	}
}

/* Update ccr and send out new status to CAN servos if needed, based on actual_status*/
HAL_StatusTypeDef Servo_CH_command(Servo_CH_Handle* hservo_CH, uint16_t ppm_value)
{
	hservo_CH->signal = ppm_value;

	if (hservo_CH->actual_status == none)
	{
		return HAL_ERROR;
	}

	/* if we are in manual mode, apply exponential moving average filter on the OUTGOING PWM signal*/
	if (source_indicator == MANUAL_MODE || source_indicator == AP_SELECTED_BUT_NOT_AVAILABLE)
	{
		if(hservo_CH->CH_ID == 9){
			hservo_CH->signal = Vtail2Rudder(pActive_RC_Source->last_valid_data[2],ppm_value); //PPM 2 and 3 in that order.
		}
		hservo_CH->signal = PWM_MAF(&(hservo_CH->PWM_MAF_state), hservo_CH->signal);

	}
	else{  /* if in autopilot */
		if(hservo_CH->CH_ID == 9){
			hservo_CH->signal = PPM_NEUTRAL_VALUE; /* fixed mid point for ouput for the tailwheel when in AP */
		}
	}

	/* This is needed because built in saturation in arm_linear_interp_f32() is not working correctly */
	if (hservo_CH->signal < PPM_MIN_VALUE)
	{
		hservo_CH->signal = PPM_MIN_VALUE;
	}
	else if(hservo_CH->signal > PPM_MAX_VALUE)
	{
		hservo_CH->signal = PPM_MAX_VALUE;
	}


	uint8_t mode=hservo_CH->config_status & 0b11;
	if(mode==0)
	{
		hservo_CH->current_pwm_out = (uint16_t)arm_linear_interp_f32( &(hservo_CH->ppm_to_pwm_struct), (float32_t)hservo_CH->signal);
		if (isValid_PWM_Channel(hservo_CH->PWM_CH)) {
			PWM_UpdateOutput(hservo_CH->PWM_CH_handle, hservo_CH->current_pwm_out);
		}
	}

	if(mode==1 || mode==2)
	{
		hservo_CH->CANServo_handle->cmd_struct.new_pos = (uint16_t)arm_linear_interp_f32( &(hservo_CH->ppm_to_deg_struct), (float32_t)hservo_CH->signal);
		HAL_StatusTypeDef retval = HAL_OK;
		if (command_DD_and_CAN_timing_FLAG)
		{
			retval = CANServo_cmd(hservo_CH->CANServo_handle);
		}
		return retval;

	}

	if (mode==3)
	{
		DD_object.new_relative_pos = (int32_t)arm_linear_interp_f32( &(hservo_CH->ppm_to_deg_struct), (float32_t)hservo_CH->signal);
	}

	return HAL_OK;
}

/* send diagnostics request to CAN servos 1 broadccast message for all
 * Can servo handle needed so that the CANServoDiag function has a counter.
 * This can be any instance, just use the same one every time
 * */
HAL_StatusTypeDef Servo_CH_diag()
{
	if(servoOnCAN1_FLAG || servoOnCAN2_FLAG)
	{
		return CANServo_diag();
	}

	return HAL_ERROR;
}

/* command functions for all servos.
 * init_ALL doesn't makes sense in current format, maybe with the config from eeprom.
 * diag_ALL is currently useless as we use broadcast msg for CAN servos.
 */

HAL_StatusTypeDef Servo_CH_init_ALL(void)
{
	for(int idx=0; idx < NUM_OF_OUTPUT_CHANNELS; idx++)
	{
			if(Servo_CH_init(Servo_Channels[idx]) != HAL_OK)
			{
				//while(1);
				//return HAL_ERROR;
			}
	}

	return HAL_OK;
}

/* this could be improved if we need to speed up the code */
HAL_StatusTypeDef Servo_CH_command_ALL_RC(uint16_t* rc_ppm_values)
{
	for (uint8_t idx=0; idx < NUM_OF_PPM_CHANNELS; idx++)
	{
		for(uint8_t jdx=0; jdx < NUM_OF_OUTPUT_CHANNELS; jdx++)
		{
			if(Servo_Channels[jdx]->PPM_in_CH == idx)
			{
				Servo_CH_command(Servo_Channels[jdx], rc_ppm_values[idx]);
			}
		}

	}
	return HAL_OK;
}


/* this could be improved if we need to speed up the code */
HAL_StatusTypeDef Servo_CH_command_ALL_AP(uint16_t* ap_ppm_values)
{
	for (uint8_t idx=0; idx < NUM_OF_AP_PWM_CHANNELS; idx++)
	{
		for(uint8_t jdx=0; jdx < NUM_OF_OUTPUT_CHANNELS; jdx++)
		{
			if(Servo_Channels[jdx]->AP_in_CH == idx)
			{
				Servo_CH_command(Servo_Channels[jdx], ap_ppm_values[idx]);
				break;
			}
		}

	}
	return HAL_OK;
}


uint16_t PWM_MAF(uint32_t* maf_State, uint16_t signal)
{
	/* this is the same as the following implementation would be:
	 *
	 * double approxRollingAverage (double avg, double new_sample) {
     * 		avg -= avg / N;
     * 		avg += new_sample / N;
	 *
     *		return avg;
	 *	}
	 *
	 */
//smaller MAF_coef will be faster
	*maf_State += (uint32_t)signal - (*maf_State / MAF_coef);
	return (uint16_t)(*maf_State / MAF_coef);
}//y = y(1/2^4 - 1/2^8) + u/2^4

uint16_t Vtail2Rudder(uint16_t signal_r, uint16_t signal_l){
	uint16_t offset_s_r = signal_r - VTAIL_OFFSET;
	uint16_t offset_s_l = signal_l - VTAIL_OFFSET;

	return (offset_s_r + offset_s_l) + VTAIL_OFFSET;
}

/*uint8_t is_CAN1_Servo_ID(uint16_t id)
{
	return (CAN1_MIN_Servo_ID <= id) && (id <= CAN1_MAX_Servo_ID);
}

uint8_t is_CAN2_Servo_ID(uint16_t id)
{
	return (CAN2_MIN_Servo_ID <= id) && (id <= CAN2_MAX_Servo_ID);
}*/
