/*
 * i2c_client.h
 *
 *  Created on: 7 Sep 2021
 *      Author: Zsombor Novozánszki
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* USER CODE BEGIN Private defines */
typedef struct T_Input_Buffer
{
	union{
		uint8_t rawU8[580];
		struct{
			uint16_t nextmsg_length;
			uint8_t command;
			uint8_t data[576];
			uint8_t checksum;
		 };
	};
} InputBuffer;

typedef enum CommunicationPhaseType
{
	receiveCommand,
	validateCommand,
	sendOrReceiveData,
	validateCheckSum
}CommunicationPhase;

extern CommunicationPhase commPhase;
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef I2C_Check_ConfigMode();
HAL_StatusTypeDef I2C_Handle_Commands();
uint8_t CheckSum_Calculate(uint8_t data[], uint16_t length);
void ValidateCommand();
void ValidateCheckSum();
void I2C_Send_ServoData();
void I2C_Update_ServoData();
void I2C_Send_HeaderData();
void I2C_Update_HeaderData();
void I2C_SaveData_inEEPROM();
void I2C_Receive_MoveServoData();
void I2C_EmergencyStop();
void FlushBuffer();


/* USER CODE END Prototypes */

