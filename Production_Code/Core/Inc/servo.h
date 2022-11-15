/*
 * servo.h
 *
 *  Created on: Jul 28, 2021
 *      Author: fbalazs
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"

#include "can_servo.h"
#include "arm_math.h"
#include "pwm.h"


#define ppm_lut_points 	3 		/* data point in ppm->pwm and ppm->deg LUTs */
#define ppm_lut_min 	5000	/* starting data point in ppm->pwm and ppm->deg LUTs, also used for boundary check */
#define ppm_lut_spacing 2500	/* distance between data points in ppm->pwm and ppm->deg LUTs */
#define ppm_lut_max 	10000 	/* max ppm value the program can receive, used for boundary check */

#define NUM_OF_OUTPUT_CHANNELS 12 	/* number of ouptut channels used on 1 RX-MUX, all of them can be CAN and/or PWM, max is 12 for pwm, about 12 for one CAN */



/* enum to keep track of the channels status, what is active,
 * and what has to be set up
 *  */
typedef enum __Servo_CH_Status
{
	RX1_PWM,
	RX1_CAN1,
	RX1_CAN2,
	RX1_DD,
	RX2_PWM,
	RX2_CAN1,
	RX2_CAN2,
	RX2_DD,
	none = 255U
}Servo_CH_Status;

/*Handle for the logical servoCH unit */
typedef struct __Servo_CH_Handle
{
	/* config structure */
	uint8_t CH_ID;					/* Channel identifier */
	//ez szerintem nem kell runtime tarolni uint8_t assigned_RX_MUX;		/* Number of the RX-MUX  (1 or 2) */
	uint8_t PPM_in_CH;				/* PPM input channel from the receiver */
	uint8_t AP_in_CH; 				/* Autopilot input channel */
	float32_t PWM_LUT_values [3];	/* y values for PWM LUT */
	uint8_t PWM_CH;					/* assigned PWM output channel */
	float32_t CAN_LUT_values [3];	/* y values for CAN LUT, encoding:  90°/4096 */
	uint8_t CAN_ID;					/* CAN arb. ID and servo ID of the assigned servo */
	/* end of config structure, 30 bytes in total*/

	arm_linear_interp_instance_f32 ppm_to_pwm_struct;
	arm_linear_interp_instance_f32 ppm_to_deg_struct;

	/* PWM channel */
	PWM_CH_Typedef* PWM_CH_handle;
	uint16_t  current_pwm_out;  	//nem tudom kell-e, debugnal hasznos

	/* CAN servo related things */
	CANServo_Handle* CANServo_handle;

	/* other */
	uint16_t signal; 				/* incoming signal */
	Servo_CH_Status config_status;	/* configured status of the channel */ //--ez lehet nem kell
	Servo_CH_Status actual_status;	/* current status of the channel */

	uint32_t PWM_MAF_state; 		/* storage variable, for the moving average filter */


}Servo_CH_Handle;


extern Servo_CH_Handle* Servo_Channels[];

/* instance init */
void prepare_Servo_channels(void);

/* command functions */
HAL_StatusTypeDef Servo_CH_init(Servo_CH_Handle* hservo_CH);
HAL_StatusTypeDef Servo_CH_command(Servo_CH_Handle* hservo_CH, uint16_t ppm_value);
HAL_StatusTypeDef Servo_CH_diag();

HAL_StatusTypeDef Servo_CH_init_ALL(void);
HAL_StatusTypeDef Servo_CH_command_ALL_RC(uint16_t* rc_ppm_values);
HAL_StatusTypeDef Servo_CH_command_ALL_AP(uint16_t* ap_ppm_values);

#endif /* INC_SERVO_H_ */
