/*
 * can_servo.h
 *
 *  Created on: Jul 19, 2021
 *      Author: fbalazs
 *
 *  For general description, and servo setup and info see can_servo.c
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_CAN_SERVO_H_
#define INC_CAN_SERVO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define servo_comms_check_timeout_value 	25   /*in ticks (ms) */
#define servo_inti_timeout_value        	25   /*in ticks (ms) */


/* register addresses in the can servo
 * R: 		read only
 * R/W: 	read and write
 * R/W +S:  read and write, but after write it needs save and power reset to take effect
 * 			(not supported in this code, so effectively the register is read only)
 *
 * Steps of adding registers
 *
 * 		1) Add address and name to this enum
 * 		2) Add register data to the desired struct (init, cmd, or diag)
 * 		3) If it is R/W register add case to CANServo_write_reg()
 * 		If it's part of init struct
 * 			4.1.1) Add it to the CANServo_write_init_params() (also increase condition in while() by 1)
 * 			4.1.2) Add it to the CANServo_check_init_params() function (re-number case if needed)
 * 			4.1.3) Add it to the CANServo_process_incoming_msgs() initialization section
 * 			4.1.4) add it to CANServo_copy_default_setup(), or don't forget to initialize otherwise
 * 		If it's part of cmd
 * 			4.2.1) Add it to CANServo_cmd() function
 * 			If you want to read the register as well see 4.3.2)
 * 		If it's part of diag
 * 			4.3.1) Add it to CANServo_diag() function
 * 			4.3.2) Add it to CANServo_process_incoming_msgs() functions
 * 		If it's part of comms_chechk
 * 			4.4.1) Add it to CANServo_comms_check() function (don't forget to adjust the counter)
 * 			4.4.2) Add it to CANServo_process_incoming_msgs() functions
 *
 * */
typedef enum __CANServo_reg_typedef
{
	id_reg				=	0x32U, /* R/W +S*/
	run_mode_reg		=	0x44U, /* R/W +S*/
	pos_max_limit_reg	=	0xB0U, /* R/W   */
	pos_min_limit_reg	=	0xB2U, /* R/W   */
	velocity_max_reg	=	0x54U, /* R/W   */
	new_pos_reg 		=	0x1EU, /* R/W   */
	mcu_temp_reg		= 	0x14U, /* R     */
	voltage_reg			=	0x12U, /* R     */
	curr_position_reg	= 	0x0CU, /* R     */
	power_config_reg	=   0x46U, /* W		*//* Used for forced emergency stop */
}CANServo_reg_typedef;


/* enum of servo status and errors */
typedef enum __CANServo_status_typedef
{
	Comms_Error 	= 0x00U,
	Servo_Normal	= 0x01U,
	Uninitialized 	= 0x02U,
	Error 			= 0x03U

}CANServo_status_typedef;

typedef enum __CANServo_e_stop_enum
{
	e_stop_off 			= 0x0000U,
	e_stop_on_mtr_free 	= 0x0200U,
}CANServo_e_stop_enum;

/*
 * structure for servo initialization.
 * If you modify this, you have to modify
 * CANServo_init() and the corresponding part of CANServo_process_incoming_msgs() as well,
 * and CANServo_write_reg if thats not done already.
 * */
typedef struct
{
	uint16_t pos_max_limit;
	uint16_t pos_min_limit;
	uint16_t velocity_max;
	uint8_t  initCounter;
} CANServo_init_struct;

/* structure for servo control */
typedef struct __CANServo_cmd_struct
{
	uint16_t new_pos;
	uint16_t e_stop;

}CANServo_cmd_struct;

/* structure for servo diagnostics */
typedef struct __CANServo_diagn_struct
{
	uint16_t mcu_temp;   	/*current setup: 100Hz polling*/
	uint16_t voltage;		/*current setup: 100Hz polling*/

	uint16_t current_pos;  	/* fix 200 Hz polling */
}CANServo_diagn_struct;

/* struct for servo handle */
typedef struct __CANServo_Handle
{
	uint16_t can_arb_id; 	/* this only changes after save, and power reset */
	uint16_t can_mode; 		/* this only changes after save, and power reset */
	uint8_t id; 			/* this only changes after save, and power reset */
	uint16_t run_mode; 		/* this only changes after save, and power reset */
	uint8_t assigned_can;
	CANServo_status_typedef status;
	CANServo_init_struct init_struct;
	CANServo_cmd_struct cmd_struct;
	CANServo_diagn_struct diagn_struct;
}CANServo_Handle;

/* custom msg storage format. Since the CAN periphery can only hold 3 messages,
 * and we have to send out 2messages/servo/cycle, we need a FIFO or queue to
 * store all the messages, until  we can transmit them. This structure holds
 * the the assembled message.
 * (important parts of the CAN tx header (not all, to save space) and the data field itself)
 */
typedef struct __CANServoTxMsg_Struct
{
	uint32_t can_StdId;
	uint32_t can_DLC;
	uint8_t  data[7];   /* Designed for longest servo msg only */
} CANServoTxMsg_Struct;

/* Enum to choose if we want to send a servo message with the servo's
 * designated CAN arbitration id, or the CAN broadcast arb. id (0x00).
 * For requesting data, you can use CAN broadcast arb. id together with servo broadcast id
 * to save on the number of messages.
 */
typedef enum __CanServoUseBroadcast_Enum
{
	own_id,
	can_broadcast,
	can_and_servo_broadcast
}CanServoUseBroadcast_Enum;


extern uint8_t servoTX_CAN1_FLAG;
extern uint8_t servoTX_CAN2_FLAG;
extern uint8_t servoOnCAN1_FLAG;
extern uint8_t servoOnCAN2_FLAG;

/* Golbal function prototypes ---------------------------------------------------------------------- */


/* copy default parameters to servo handle */
HAL_StatusTypeDef CANServo_copy_default_setup(CANServo_Handle* hservo);



/* control functions */
HAL_StatusTypeDef CANServo_init(CANServo_Handle* hservo);

HAL_StatusTypeDef CANServo_cmd(CANServo_Handle* hservo);
HAL_StatusTypeDef CANServo_diag();

/* input processors for CAN peripherys */
HAL_StatusTypeDef CANx_process_incoming_msgs(CAN_HandleTypeDef* hcan);


/* low level transmit function, to actually send out CAN messages */
HAL_StatusTypeDef CANx_transmit_servo_msg_queue(CAN_HandleTypeDef* hcan);

HAL_StatusTypeDef CANServo_write_reg(CANServo_Handle* hservo, CANServo_reg_typedef reg, CanServoUseBroadcast_Enum broadcast);


/* USER CODE END Prototypes */

#endif /* INC_CAN_SERVO_H_ */
