/*
 * error_detection.h
 *
 *  Created on: 22 Jul 2021
 *      Author: novoz
 */

#ifndef ERROR_DETECTION_H_
#define ERROR_DETECTION_H_

#include "stm32f4xx_hal.h"

#define ERROR_Length 13


// Error structure and error types
typedef struct Error_Struct
{
	union
	{
		struct
		{
			uint8_t adc;
			uint16_t servo_present;
			uint8_t can_low_level;
			uint16_t dd;
			uint8_t eeprom;
			uint16_t rc_input;
			uint8_t spi;
			uint8_t i2c;
			uint8_t source_ind;					//TODO ez valamiert nem kerul rendesen bele a strukturaba (majd ha lesz uj struktura)
			uint8_t ecu;
		};
		uint8_t rawErrorData[ERROR_Length];
	 	};
}Errors;

typedef enum T_ADC_Error_Types
{
	lowVoltage=1,
}ADC_Error_Types;

typedef enum T_Servo_Present_Types  /* A CAN servo is indicated missing, if we don't get a reply for the diagnostics request */
{
	MISSING_SERVO1=1,
	MISSING_SERVO2=2,
	MISSING_SERVO3=4,
	MISSING_SERVO4=8,
	MISSING_SERVO5=16,
	MISSING_SERVO6=32,
	MISSING_SERVO7=64,
	MISSING_SERVO8=128,
	MISSING_SERVO9=256,
	MISSING_SERVO10=512,
	MISSING_SERVO11=1024,
	MISSING_SERVO12=2048,
}Servo_Present_Types;

typedef enum T_EEPROM_Error_Types
{
	FLASH_ERROR=1,
	FLASH_BUSY=2,
	FLASH_TIMEOUT=4,
	NO_VALID_PG=8
}EEPROM_Error_Types;

typedef enum T_SPI_Error_Types
{
	WRONG_FH_CHECKSUM=1,
	overrun=4,			// when master wants transmit, but slave could not receive previous message
	FRAME_FORMAT=8,		// when received format is not the same as expected format (it should be 8bit)
	SPI_DMA_TRANSFER=16, 	// DMA transfer error
	flag=32				// TXE, RXNE and BSY flag error (empty Transfer or Receiver buffer)
}SPI_Error_Types;

typedef enum T_I2C_Error_Types
{
	busError=1,
	wrongRXCheckSum=2,
	ACKFailure=4,
	i2coverrun=8,
	I2CDMATransfer=16,
	wrongStart=32,
	size=64,
	DMAParam=128
}I2C_Error_Types;
/*typedef enum T_CAN_Low_Level
{
	// errors come here
}CAN_Low_Level;

typedef enum T_DD_Error_Types
{
	// errors come here
}DD_Error_Types;
*/

typedef enum T_RC_Error_Types
{
	PPM_RC1_FRAME_MISSED 	= 1U, 	/* No data recieved for this amount of time: "PPM_RC1_Frame_Timeout" */
	PPM_RC1_ERROR			= 2U,  	/* No data recieved for this amount of time: "PPM_RC1_Error_Timeout" */
	EXBUS_FRAME_MISSED 		= 4U,	/* No data recieved for this amount of time: "EXBus_Frame_Timeout"   */
	EXBUS_ERROR				= 8U,	/* .... */
	PPM_RC1_INIT_FAILED		= 16U,
	EXBUS_INIT_FAILED 		= 32U,
	PPM_RC1_INVALID_FRAME 	= 64U,
	PPM_RC2_FRAME_MISSED	= 128U,
	PPM_RC2_ERROR			= 256U,
	EXBUS2_FRAME_MISSED		= 512U,
	EXBUS2_ERROR			= 1024U,
	PPM_RC2_INIT_FAILED		= 2048U,
	EXBUS2_INIT_FAILED		= 4096U,
	PPM_RC2_INVALID_FRAME 	= 8192U,

}RC_Error_Types;

typedef enum T_Source_Ind_Types
{
	MANUAL_MODE 						= 1U,
	AP_MODE								= 2U,
	AP_SELECTED_BUT_NOT_AVAILABLE 		= 4U,
	ERROR_NO_INPUT						= 8U,
}Source_Ind_Types;


typedef enum T_ECU_Error_Types
{
	INVALID_FRAME=1,
	UNKNOW_COMMAND=2,
	WRONG_PARAMETER_NUMBER=4,
	WRONG_DATA_FORMAT=8,
	COMMAND_NOT_ALLOWED=16,
}ECU_Error_Types;

//Prototypes
extern Errors errors;
void DeleteErrorFlag();

#endif /* ERROR_DETECTION_H_ */
