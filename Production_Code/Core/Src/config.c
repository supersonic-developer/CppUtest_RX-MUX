/*
 * config.c
 *
 *  Created on: 2020. �pr. 24.
 *      Author: Kovacs Andras
 */

#include "config.h"
#include "eeprom.h"
#include "app.h"
#include "error_detection.h"
#include "servo.h"
#include "dd.h"
#include "spi.h"
#include "iwdg.h"
#include "version.h"
#include <string.h>


__Servo_CH_Config_Handle servoData[24];
Header_Config headerData;

HAL_StatusTypeDef EEPROM_Status=HAL_OK;

/* private prototypes */


void EEPROM_Error_Log()
{
	switch (EEPROM_Status)
	{
		case HAL_ERROR:
			errors.eeprom|=FLASH_ERROR;
			break;
		case HAL_BUSY:
			errors.eeprom|=FLASH_BUSY;
			break;
		case HAL_TIMEOUT:
			errors.eeprom|=FLASH_TIMEOUT;
			break;
		default:
			errors.eeprom |= NO_VALID_PG;
			break;
	}
}
HAL_StatusTypeDef EmulationEEPROM_Init()
{
	/* Unlock the Flash Program Erase controller */
	EEPROM_Status=HAL_FLASH_Unlock();

	/* EEPROM Init */
	EEPROM_Status=EE_Init();

	return EEPROM_Status;
}

HAL_StatusTypeDef CONF_Load()
{
	/* Copy version variables into configuration structure */
	for(int i=0;i<8;i++)
		headerData.commitId[i]=SW_RXMUX_v2_git_commit[i];
	for(int i=0;i<6;i++)
		headerData.firmwareVersion[i]=SW_RXMUX_v2_git_tag[i];

	/* Read configuration from flash */
	/* Configuration header */
	for(int count=0;count<ConfigHeaderLength/2 ;count++)
		EEPROM_Status=EE_ReadVariable(VIRT_ADDR_VAR_TAB +count, &headerData.rawU16[HeaderLength/4+count]);

	/* Configuration data */
	for(int count=0;count<NumberOfServos;count++)
	{
		for(int i = 0;i < Servo_CH_Handle_Length;i++)
			EEPROM_Status=EE_ReadVariable(VIRT_ADDR_VAR_TAB + ConfigHeaderLength/2+count*Servo_CH_Handle_Length+i, &servoData[count].rawU16[i]);
	}

	return EEPROM_Status;
}

HAL_StatusTypeDef CONF_Store()
{
	/* Store Configuration in flash memory */
	/* Configuration header */
	for(int count=0;count<ConfigHeaderLength/2;count++)
	{
		EEPROM_Status=EE_WriteVariable(VIRT_ADDR_VAR_TAB +count, headerData.rawU16[HeaderLength/4+count]);
		HAL_IWDG_Refresh(&hiwdg);
	}

	/* Configuration data */
	for(int count=0;count<NumberOfServos;count++)
	{
		for(int i = 0; i < Servo_CH_Handle_Length;i++ )
			EEPROM_Status=EE_WriteVariable(VIRT_ADDR_VAR_TAB + ConfigHeaderLength/2+count*Servo_CH_Handle_Length+i, servoData[count].rawU16[i]);
		HAL_IWDG_Refresh(&hiwdg);
	}

	return EEPROM_Status;
}


/* Updates the runtime handles (Servo_CH_Handle) with data from the config handles (__Servo_CH_Config_Handle)
 */
HAL_StatusTypeDef CONF_Update_Runtime_Handles()
{
	/* set DD to "not used" by default */
	DD_object.current_state = DD_Not_used;

	/* go trough all channels */
	uint8_t count_runtime = 0;
	uint32_t mask=1;
	uint8_t assignedRXMUX=none;

	for(int count=0; count<NumberOfServos; count++, mask*=2)
	{
		assignedRXMUX=none;
		if(servoData[count].Mode!=none)
			assignedRXMUX= ((servoData[count].Mode & 0b100)>>2)+1;

		if (assignedRXMUX==rxmuxID)
		{
			process_Buff.header|=mask;
			CopyConfigData_RuntimeStruct(count_runtime, count);
			count_runtime++;
		}
	}
	/* Fill up unused servo channel spots*/
	while(count_runtime<NUM_OF_OUTPUT_CHANNELS)
	{
		Servo_Channels[count_runtime]->config_status=none;
		count_runtime++;
	}
	return HAL_OK;
}

void CopyConfigData_RuntimeStruct(uint8_t count_runtime, uint8_t count)
{
	/*copy and cast data*/
	Servo_Channels[count_runtime]->CH_ID 		= (uint8_t)servoData[count].CH_ID;
	Servo_Channels[count_runtime]->PPM_in_CH 	= (uint8_t)servoData[count].PPM_in_CH;
	Servo_Channels[count_runtime]->AP_in_CH 	= (uint8_t)servoData[count].AP_in_CH;
	Servo_Channels[count_runtime]->PWM_CH 		= (uint8_t)servoData[count].PWM_CH;
	Servo_Channels[count_runtime]->CAN_ID 		= (uint8_t)servoData[count].CAN_ID;

	for (int idx=0; idx<3; idx++)
	{
		Servo_Channels[count_runtime]->PWM_LUT_values[idx] = (float32_t)servoData[count].PWM_LUT_values[idx];
		Servo_Channels[count_runtime]->CAN_LUT_values[idx] = (float32_t)servoData[count].CAN_LUT_values[idx];
	}

	Servo_Channels[count_runtime]->config_status = servoData[count].Mode;

	/* set channel status */
	if ((Servo_Channels[count_runtime]->config_status & 0b11)==3)
	{
		//Servo_Channels[count_runtime]->config_status = dd_only;
		DD_object.current_state = DD_Offline; /* Only 1 DD per RXMXUX is allowed */
	}
}
