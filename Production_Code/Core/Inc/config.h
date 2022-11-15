/*
 * config.h
 *
 *  Created on: Mar 13, 2020
 *      Author: andkovac
 */

#include "main.h"

#define Servo_CH_Handle_Length 12
#define NumberOfServos 24
#define ConfigHeaderLength 14
#define HeaderLength 28

/*#define CAN1_MIN_Servo_ID 	0x01
#define CAN1_MAX_Servo_ID 	0x60

#define DD_MIN_NODE_ID 		0x61
#define DD_MAX_NODE_ID 		0x70

#define CAN2_MIN_Servo_ID 	0x71
#define CAN2_MAX_Servo_ID 	0xD0
*/
#define Servo_MAX_PWM_CH 	12
#define Servo_MIN_PWM_CH 	1

typedef struct Core_Config_Type {
	union{
		struct{
			char commitId[8];
			char firmwareVersion[6];
			char configId[8];
			char configVersion[6];
		};
		uint16_t rawU16[14];
		uint8_t rawU8[28];
	};
} Header_Config;


typedef struct __Servo_CH_Config_Handle
{
	union{
		struct{
			uint16_t CH_ID;                 /* Channel identifier */
			uint16_t Mode;       			/* Configuration mode (more info under structure) */
	 		uint16_t PPM_in_CH;             /* PPM input channel from the receiver */
	 		uint16_t AP_in_CH;              /* Autopilot input channel */
	 		uint16_t PWM_LUT_values[3];     /* y values for PWM LUT */
	 		uint16_t PWM_CH;                /* assigned PWM output channel */
	 		uint16_t CAN_LUT_values[3];     /* y values for CAN LUT */
	 		uint16_t CAN_ID;                /* CAN arb. ID and servo ID of the assigned servo */
	 	};
	 	uint16_t rawU16[12];
	 	uint8_t rawU8[24];
	};
}__Servo_CH_Config_Handle;

/*	Configuration mode description:
 * 	0:= RXM1 PWM
 * 	1:= RXM1 CAN-1
 * 	2:= RXM1 CAN-2
 * 	3:= RXM1 DD
 * 	4:= RXM2 PWM
 * 	5:= RXM2 CAN-1
 * 	6:= RXM2 CAN-2
 * 	7:= RXM2 DD
 */

extern __Servo_CH_Config_Handle servoData[24];
extern Header_Config headerData;
extern HAL_StatusTypeDef EEPROM_Status;



HAL_StatusTypeDef CONF_Load();
HAL_StatusTypeDef CONF_Store();
HAL_StatusTypeDef EmulationEEPROM_Init();
HAL_StatusTypeDef CONF_Update_Runtime_Handles();
void EEPROM_Error_Log();
void CopyConfigData_RuntimeStruct(uint8_t count_runtime, uint8_t config_runtime);
