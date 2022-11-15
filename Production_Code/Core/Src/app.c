/*
 * app.c
 *
 *  Created on: Sep 21, 2020
 *      Author: andkovac
 */

#include "app.h"

#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "indicators.h"
#include "pwm.h"
#include "ppm.h"
#include "can.h"
#include "spi.h"
#include "i2c.h"
#include "dma.h"
#include "exbus.h"
#include "can_servo.h"
#include "servo.h"
#include "adc.h"
#include "i2c_client.h"
#include "config.h"
#include "eeprom.h"
#include "default_config.h"
#include "rc_superv_logic.h"
#include "error_detection.h"
#include "iwdg.h"
#include "dd.h"
#include "ecu_uart.h"



APP_State state = RunState;

RXMUX_ID rxmuxID;

uint8_t IWDG_Reset_FLAG = 0;                    /* if we are starting from a watchdog reset, we do things differently */

uint8_t command_DD_and_CAN_timing_FLAG = 0;     /* set to one if DD and/or CAN servos should be updated */

Source_Ind_Types source_indicator = 0; 			/* indicates AP, MANUAL, NONE, or "AP wanted but not available " */
Source_Ind_Types source_ind_prev = 0;			/* needed for LED indicators */
uint32_t ms_cntr = 0;
uint16_t RXMUptime = 0; 						/* Uptime counter. Incremented every second. */

/* private functions */
void wait_for_RC_at_init(void);
void copy_PPM_to_SPI_struct(void);
void copy_VBAT_to_SPI_struct(void);
void copy_DD_diag_to_SPI_struct(void);
uint8_t AP_conditions_met(void);
uint8_t AP_selected(void);
void set_DD_and_CANServo_flags(void);
void periodic_handler(void);



HAL_StatusTypeDef APP_Init() {

	/*get cause of reset */
	if((RCC->CSR) & 1U<<29) {
		/*If it's a watchdog reset set the flag */
		IWDG_Reset_FLAG = 1;
	}

	/* Reset RCC Status register so flags don't accumulate over resets */
	RCC->CSR |= 1U << 24;

	/* Zero uptime */
	RXMUptime = 0;
	/* start timer 14. IT every second, this is used for counting the uptime*/
	HAL_TIM_Base_Start_IT(&htim14);

	/* Start timer 7 -> 1ms time base */
	HAL_TIM_Base_Start_IT(&htim7);

	/* Start timer 6 -> 0.1ms time base, for signal source error detection */
	HAL_TIM_Base_Start_IT(&htim6);

	/* start 1us timebase for CANopen (DD) */
	HAL_TIM_Base_Start(&htim10);

	/* Initialize LED indicators  */
	IND_Init();

	/* Read GPIOs to identify the current RX-MUX and reinitialize I2C periphery*/
	if(HAL_GPIO_ReadPin(GPIOE,ADDR_JP1_Pin)==GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOE,ADDR_JP2_Pin)==GPIO_PIN_SET)
		rxmuxID=RXMUX1;
	else if(HAL_GPIO_ReadPin(GPIOE,ADDR_JP1_Pin)==GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOE,ADDR_JP2_Pin)==GPIO_PIN_RESET)
		rxmuxID=RXMUX2;
	MX_I2C1_Init();

	/* CAN bus initialization */
	if(CAN1_Setup() != HAL_OK) {
		 //TODO log CAN init_fail (ha lesz uj SPI struktura)
	}
	if(CAN2_Setup() != HAL_OK) {
		 //TODO log CAN init_fail (ha lesz uj SPI struktura)
	}

	/* Assign CAN servo handles, to Servo_cahnnel handles,
	 * Set default PWM values */
	prepare_Servo_channels();

	/* initialize EEPROM, and read configuration from it */
	if(EmulationEEPROM_Init()!=HAL_OK){
		EEPROM_Error_Log();
		default_config();
	}
	else if(CONF_Load()!=HAL_OK){
		EEPROM_Error_Log();
		default_config();
	}

	/* Apply the configuration, to the runtime variables */
	if(CONF_Update_Runtime_Handles() != HAL_OK){
		//TODO log init fails (ha lesz uj SPI struktura)
	}

	/* wait to see if connected PC wants to initiate config mode
	 * If the watchdog caused the reset, we don't need config mode (function is blocking) */
	if (!IWDG_Reset_FLAG) {
		I2C_Check_ConfigMode();  //TODO itt lehetnek logolni kivant dolgok? (ha lesz uj SPI struktura)
	}

	/* servo channel init, contains both can and pwm servo, AND DD  */
	Servo_CH_init_ALL(); //TODO can servo error handling

	/* prepare storage variables for the RC sources */
	Init_SignalSource_structures_ALL();

	/* init PPM input(s) capture */
	#if (USE_RC1_PPM == 1U || USE_RC2_PPM == 1U)
		PPM_Init();
	#endif
	#if (USE_RC1_EXBUS==1U || USE_RC2_EXBUS==1U)
		EXBus_Init();
	#endif

	/* Set indicators to default */
	IND_SetLED(Red_LED,Off,No);
	IND_SetLED(Green_LED,On,Normal);
	IND_Handler();

	/*  watchdog */
	if (USE_IWDG != 0){

		/* initialize and start watchdog */
		MX_IWDG_Init();

		/* configure watchdog stop when debugging */
		if (IWDG_DEBUG_ON != 0)
			DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;
	}

	// Determine that if current RX-MUX should control the jet engine
	isECUforCurrentRXMUX();

	return HAL_OK;
}


HAL_StatusTypeDef run() {

	/* get PPM values from RC1 and RC2 if available */
	#if (USE_RC1_PPM == 1U || USE_RC2_PPM == 1U)
		if (PPM_Handle() != HAL_OK){
			//TODO log PPM errors
		}
	#endif


	//TODO majd EXBUS meg SBUS handler ide jon
	EX_BUS_Handler(1);
	EX_BUS_Handler(2);

	/* SPI communication */
	Set_StatusFlags();
	SPI1_TransmitReceive();

	/* Update all of  the RC input channels, get new data (if available), run error detection,
	 * check AP source for activity */
	Check_SignalSources_ALL();

	/* transmit CAN servo data if queue is not empty */
	if (servoTX_CAN1_FLAG){
		CANx_transmit_servo_msg_queue(&hcan1);
	}
	if (servoTX_CAN2_FLAG){
		CANx_transmit_servo_msg_queue(&hcan2);
	}

	/* process incoming CAN servo data */
	CANx_process_incoming_msgs(&hcan1);
	CANx_process_incoming_msgs(&hcan2);

	/* select which input to use,
	 * data from the selected input is available in: SignalSource_Structure* pActive_RC_Source  */
	Active_RC_Source =  Select_RC_SignalSource();

	/* ECU  */
	ECUHandler();

	/* send out command, and set indicators, based on previous step, and AP switch position */
	if (Active_RC_Source == Error_No_RC_Input)
	{
		/* Go into failsafe mode
		 * Currently this only means to keep last valid values, and set indicator */

		source_indicator = ERROR_NO_INPUT;
	}
	else
	{
		/* copy active RC receiver data to SPI message struct for logging */
		copy_PPM_to_SPI_struct();

		/* send out the signals from autopilot */
		if(AP_conditions_met()){
			/* command channels from AP */
			Servo_CH_command_ALL_AP(process_Buff.servoValues.PWM_data.aPWMData);
			source_indicator = AP_MODE;
		}
		/* send out the signals from RC */
		else{
			/*command channels from RC input */
			Servo_CH_command_ALL_RC(pActive_RC_Source->last_valid_data);
			source_indicator = MANUAL_MODE;

			if(AP_selected()){
				/* error, AP is selected but not available */
				source_indicator = AP_SELECTED_BUT_NOT_AVAILABLE;
			}
		}
	}

	/* Handle DD (CANopen main thread + DD state machine) */
	/* There is also a line in set_indicators(); !! (thats the call of the timed thread of CANopen)*/
	if (DD_object.current_state != DD_Not_used) {
		DD_handler();
	}


	/* decide if we should command new position and diagnostics to DD and CAN servos*/
	set_DD_and_CANServo_flags();

	/* Actually command DD. Can servos are dealt with in servo.c but the same flag is used */
	if(command_DD_and_CAN_timing_FLAG)
	{
		/* get diagnostics data from servos */
		Servo_CH_diag();

		/* set DD request flags */
		if(DD_object.current_state != DD_Not_used)
		{
			DD_object.voltage_wanted = 1;
			DD_object.new_pos_wanted = POS_requested;
		}

	}


	/* Get battery voltage */
	if(ADC_VBAT_READY_FLAG){
		/* current solution: SPI1_TransmitReceive() starts an ADC conversion, if SPI communication was successful
		 * then,  HAL_ADC_ConvCpltCallback() sets ADC_VBAT_READY_FLAG */
		copy_VBAT_to_SPI_struct();
	}

	/* copy dignostic data from the DD to the SPI struct*/
	copy_DD_diag_to_SPI_struct();

	/* deal with the indicators */
	periodic_handler();

	if (USE_IWDG != 0){
		/* refresh watchdog only at the end of the cycle*/
		HAL_IWDG_Refresh(&hiwdg);
	}

	return HAL_OK;
}

/* should we delete this ? */
void APP_ErrorHandler() {

	state = ErrorState;

	while(1) {
		APP_Go();
	}
}


HAL_StatusTypeDef APP_Go() {

	switch (state) {
		case RunState:
			if(run() != HAL_OK)
				return HAL_ERROR;
			break;
		case ConfigState:
			if(I2C_Handle_Commands()!=HAL_OK)
				return HAL_ERROR;
			break;
		case ErrorState:
			if(run() != HAL_OK)
				return HAL_ERROR;
			break;
	}
	return HAL_OK;
}


/* copy active RC receiver data to SPI message struct for logging */
void copy_PPM_to_SPI_struct (void)
{
	for (uint8_t idx=0; idx<NUM_OF_PPM_CHANNELS; idx++)
	{
		process_Buff.servoValues.PPM_data.aPPMData[idx] = pActive_RC_Source->last_valid_data[idx];
	}
}


/* send PWM outputs for logging if not in autopilot */
void copy_PWM_To_SPI_Struct(void)
{
	uint8_t mode;
	for (uint8_t idx=0; idx < NUM_OF_OUTPUT_CHANNELS; idx++)
	{
		uint8_t ch_id = Servo_Channels[idx]->AP_in_CH;

		/* we can only log 19 channels, so only channels with chId 1-19 get logged*/
		if (ch_id < 19)
		{
			mode=Servo_Channels[idx]->config_status & 0b11;
			if (mode==0)  {
				//process_Buff.servoValues.PWM_data.aPWMData[ch_id] = (uint16_t)*(Servo_Channels[idx]->PWM_CH_handle->ccrReg);
				//ez igy nem jo, mert felulirasra kerul ami az AP-tol jott az elso ciklusban, es utana mindig rossz lesz.

				if(isValid_PWM_Channel(Servo_Channels[idx]->PWM_CH)){
					toFH_Buff.servoValues.PWM_data.aPWMData[ch_id] = (uint16_t)*(Servo_Channels[idx]->PWM_CH_handle->ccrReg);
				}
			}
			/*else
			{
				toFH_Buff.servoValues.PWM_data.aPWMData[ch_id] = 0;  //was causing issues when it got to an unused channel.
			} */
		}
	}
}

void Set_StatusFlags()
{
	// Set status bits to sign current flight mode (AP, Jeti, Graupner)
	if(PPM_RC1_src_struct.State==src_active)
		process_Buff.status1|=0x10;
	else
		process_Buff.status1&=0xFFEF;
	if(PPM_RC2_src_struct.State==src_active)
		process_Buff.status1|=0x20;
	else
		process_Buff.status1&=0xFFDF;
	if(source_indicator==AP_MODE)
		process_Buff.status1|=0x1;
	else
		process_Buff.status1&=0xFFFE;
	if(source_indicator==MANUAL_MODE)
	{
		if(Active_RC_Source==RC1_PPM || Active_RC_Source==RC1_EXBus)
			process_Buff.status1|=0x40;
		else
			process_Buff.status1&=0xFFBF;
		if(Active_RC_Source==RC2_PPM || Active_RC_Source==RC2_EXBus)
			process_Buff.status1|=0x80;
		else
			process_Buff.status1&=0xFF7F;
	}

	/* copy uptime to the SPI struct */
	process_Buff.status2 = RXMUptime;
}

void copy_VBAT_to_SPI_struct(void)
{
	ADC_VBAT_READY_FLAG = 0;
	uint16_t VBat1 = 0;
	uint16_t VBat2 = 0;

	/* GET the 10 measurements, and average them */
	for(uint8_t idx = 0; idx < (adc_buff_length/2); idx++)
	{
		VBat1 += (uint16_t)adc_buff[2*idx];
		VBat2 += (uint16_t)adc_buff[2*idx+1];
	}
	VBat1 = (uint16_t)( VBat1 / ((float32_t)(adc_buff_length/2)));
	VBat2 = (uint16_t)( VBat2 / ((float32_t)(adc_buff_length/2)));

	if(rxmuxID==RXMUX1)
		process_Buff.servoValues.battery_data.battery = VBat1;  //TODO log BATT2 (ha lesz uj SPI struktura)
	else
		process_Buff.servoValues.battery_data.battery = VBat2;

}

void copy_DD_diag_to_SPI_struct(void)
{

	if (DD_object.current_state != DD_Not_used)
	{
		S_DD_PARAMETERS * buffer = NULL;
		if (rxmuxID == RXMUX1){
			buffer = &(process_Buff.DDvalues.DD1);
		}
		else if(rxmuxID == RXMUX2){
			buffer = &(process_Buff.DDvalues.DD2);
		}

		if (buffer == NULL){
			return;
		}

		//TODO (DD) sort out SPI struct, type cast problems

		buffer->position 		= (uint16_t) *(DD_object.p_DD_actual_pos); 		/* int32_t   -> uint16_t, [user defined, count] should be ok, as pos is limited to 10000 counts */
		buffer->current			= (uint16_t) *(DD_object.p_DD_actual_current); 	/* int16_t   -> uint16_t  [per thousand of rated current] */
		buffer->voltage			= (uint16_t) *(DD_object.p_DD_actual_voltage); 	/* float32_t -> uint16_t  [V] !!!!! */
		buffer->aOtherData[0] 	= (uint16_t) *(DD_object.p_DD_actual_tempr); 	/* int16_t   -> uint16_t  [°C]  */
	}



}

/* Function decides if there is new data for the CANServos and/or DD,
 * and sets their flags accordingly */
void set_DD_and_CANServo_flags(void){
	if (source_indicator == MANUAL_MODE || source_indicator == AP_SELECTED_BUT_NOT_AVAILABLE){

			if (pActive_RC_Source->new_data_FLAG == 1){
				command_DD_and_CAN_timing_FLAG = 1;
				pActive_RC_Source->new_data_FLAG = 0;
			}
			else{
				command_DD_and_CAN_timing_FLAG = 0;   /* since FALAG is used in multiple places (simultaneously) it has to be reset here */
			}
		}
		else if (source_indicator == AP_MODE)
		{
			if (AP_src_struct.new_data_FLAG == 1){
				command_DD_and_CAN_timing_FLAG = 1;
				AP_src_struct.new_data_FLAG = 0;
			}
			else{
				command_DD_and_CAN_timing_FLAG = 0;
			}
		}

		/* if we are in FAILSAFE don't to anything with DD and CAN servos */
		if (source_indicator == ERROR_NO_INPUT){
			command_DD_and_CAN_timing_FLAG = 0;
		}
}

/* For things that are required to be called every x ms (ish) */
void periodic_handler(void){

	if(TIM_Flag_1ms) {

		TIM_Flag_1ms = 0;
		ms_cntr++;

		// Call indicator handler once in every 1 ms
		IND_Handler();

		/* call DD periodic handler */
		if (DD_object.current_state != DD_Not_used)
		{
			DD_periodic_handler();
		}

		/* i have to do it this way because IND_SetLED() can't handle too frequent calling */
		if((ms_cntr%5 == 0) && (source_indicator != source_ind_prev)) /* i have to do it this way because IND_SetLED() can't handle too frequent calling */
		{
			switch (source_indicator){
				case ERROR_NO_INPUT:
					IND_SetLED(Red_LED,Off,No);
					IND_Handler();
					IND_SetLED(Red_LED,On,Normal);
					break;
				case MANUAL_MODE:
					IND_SetLED(Red_LED,On,No);
					break;
				case AP_MODE:
					IND_SetLED(Red_LED,Off,No);
					break;
				case AP_SELECTED_BUT_NOT_AVAILABLE:
					IND_SetLED(Red_LED,Off,No);
					IND_Handler();
					IND_SetLED(Red_LED,On,UltraFast);
					break;
			}

			source_ind_prev = source_indicator;
		}
	}
}

FORCE_INLINE uint8_t AP_conditions_met(void){

	if(AP_selected() == 0)
		return 0;

	if(AP_src_struct.State == src_inactive)
		return 0;

	return 1U;
}

FORCE_INLINE uint8_t AP_selected(void){
	if(Active_RC_Source == Error_No_RC_Input)
		return 0;

	if(pActive_RC_Source->last_valid_data[AP_Control_Channel] <=  AP_Control_Threshold)
		return 0;

	return 1U;
}
