/**
  ******************************************************************************
  * File Name          : i2c_client.c
  * Description        : This file provides methods for handling communication with client application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app.h"
#include "i2c_client.h"
#include "config.h"
#include "i2c.h"
#include "servo.h"
#include "can_servo.h"
#include "eeprom.h"
#include "tim.h"
#include "pwm.h"
#include "iwdg.h"
#include "can.h"

// Variable for communication phases
CommunicationPhase commPhase=receiveCommand;

//Buffers
InputBuffer inBuff;
uint8_t outBuff[1000];

// Status
HAL_StatusTypeDef I2C_Status=HAL_OK;

// Commands
#define CheckConn  0xA1
#define  EmcyStop  0xF2
#define  WriteServo  0xC1
#define  ReadServo  0x1C
#define  WriteHeader  0xE4
#define  ReadHeader  0x4E
#define  Save  0x1D
#define  Move 0x2F
#define  GetStatus  0xD2 // In final concept it is an unimplemented command (no need)
#define  ACK  0x79
#define  NACK  0x1F


HAL_StatusTypeDef I2C_Check_ConfigMode()
{
	// Start receive message from Client application
	I2C_Status=HAL_I2C_Slave_Receive_DMA(&hi2c1,&inBuff.command,1);
	uint32_t tickstart = HAL_GetTick();

	// Wait for message or exit after 2 second of waiting
	while(((HAL_GetTick() - tickstart) < 2000) && !I2C1_Flag_RxReady){}

	// If message arrived and if it is ping command, change app state
	if(I2C1_Flag_RxReady && inBuff.command==CheckConn)
	{
		I2C1_Flag_RxReady=0;
		state=ConfigState;
		outBuff[0]=ACK;
		I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,1);
	}
	else // If there was not config message, reinitialize the periphery
	{
		HAL_I2C_MspDeInit(&hi2c1);
		HAL_I2C_MspInit(&hi2c1);
		MX_I2C1_Init();
	}
	return I2C_Status;
}

uint8_t CheckSum_Calculate(uint8_t data[], uint16_t length)
{
	uint8_t checkSum=0;
	for(int i=0;i<length;i++)
		checkSum+=data[i];
	return checkSum^=0xFF;
}

void ValidateCommand()
{
	if(inBuff.command==EmcyStop || inBuff.command==Save || inBuff.command==GetStatus)
	{
		outBuff[0]=ACK;
		commPhase=sendOrReceiveData;
	}
	else if(((inBuff.command==WriteHeader || inBuff.command==ReadHeader) && inBuff.nextmsg_length==(HeaderLength+1)) ||
			((inBuff.command==WriteServo || inBuff.command==ReadServo) && inBuff.nextmsg_length==(2*NumberOfServos*Servo_CH_Handle_Length+1)))
	{
		outBuff[0]=ACK;
		commPhase=sendOrReceiveData;
	}
	else if(inBuff.command==Move && inBuff.nextmsg_length==5)
	{
		outBuff[0]=ACK;
		commPhase=sendOrReceiveData;
	}
	else
	{
		outBuff[0]=NACK;
		commPhase=receiveCommand;
	}
}

void ValidateCheckSum()
{
	// If checksum is good, send ACK
	if(inBuff.data[inBuff.nextmsg_length-1]==CheckSum_Calculate(inBuff.data,inBuff.nextmsg_length-1))
	{
		outBuff[0]=ACK;
		// If received Header or Servo Data, save it into structure
		if(inBuff.command==WriteHeader)
		{
			for(int count=0;count<HeaderLength/2 ;count++)
				headerData.rawU8[HeaderLength/2+count]=inBuff.data[HeaderLength/2+count];
		}
		else if(inBuff.command==WriteServo)
		{
			// Copy received data into servo handle array
			for(int count=0;count<NumberOfServos;count++)
			{
				for(int i = 0;i < 2*Servo_CH_Handle_Length;i++)
					servoData[count].rawU8[i]=inBuff.data[2*count*Servo_CH_Handle_Length+i];
			}
		}
		else if(inBuff.command==Move)
		{
			int cnt=0;
			uint32_t signalValue;

			// Find selected actuator
			while(cnt<12 && Servo_Channels[cnt]->CH_ID!=inBuff.data[0])
				cnt++;

			// Create actuator signal according to input buffer data
			signalValue=(inBuff.data[3]<<8) | inBuff.data[2];

			// Send out signal, inBuff.data[1] byte defines that it is a PWM or CAN signal
			if(inBuff.data[1]=='p' && isValid_PWM_Channel(Servo_Channels[cnt]->PWM_CH)){
				PWM_UpdateOutput(Servo_Channels[cnt]->PWM_CH_handle, signalValue);
			}
			else if(inBuff.data[1]=='c')
			{
				Servo_Channels[cnt]->CANServo_handle->cmd_struct.new_pos=(uint16_t)signalValue;
				CANServo_cmd(Servo_Channels[cnt]->CANServo_handle);
				CANx_transmit_servo_msg_queue(&hcan1);
				CANx_transmit_servo_msg_queue(&hcan2);
			}
		}
	}
	// If wrong checksum, send NACK
	else
		outBuff[0]=NACK;
}

HAL_StatusTypeDef I2C_Handle_Commands()
{
	HAL_IWDG_Refresh(&hiwdg);
	if((I2C1_Flag_TxReady || I2C1_Flag_RxReady) && commPhase==receiveCommand)
	{
		I2C1_Flag_TxReady=0;
		I2C1_Flag_RxReady=0;
		I2C_Status=HAL_I2C_Slave_Receive_DMA(&hi2c1,inBuff.rawU8,3);
		commPhase=validateCommand;
	}

	if(I2C1_Flag_RxReady && commPhase==validateCommand)
	{
		I2C1_Flag_RxReady=0;
		ValidateCommand();
		I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,1);
	}

	if(I2C1_Flag_TxReady && commPhase==sendOrReceiveData)
	{
		I2C1_Flag_TxReady=0;
		switch(inBuff.command)
		{
			case EmcyStop:
				I2C_EmergencyStop();
				break;
			case WriteServo:
				I2C_Update_ServoData();
				break;
			case ReadServo:
				I2C_Send_ServoData();
				break;
			case WriteHeader:
				I2C_Update_HeaderData();
				break;
			case ReadHeader:
				I2C_Send_HeaderData();
				break;
			case Save:
				I2C_SaveData_inEEPROM();
				break;
			case Move:
				I2C_Receive_MoveServoData();
				break;
			case GetStatus:
				// Get status
				break;
			default:
				break;
		}
	}

	if(I2C1_Flag_RxReady && commPhase==validateCheckSum)
	{
		I2C1_Flag_RxReady=0;
		ValidateCheckSum();
		I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,1);
		commPhase=receiveCommand;
	}
	return I2C_Status;
}

void I2C_EmergencyStop()
{
	// Servo configuration variable just for shorter code
	Servo_CH_Status setup=none;

	// Loop through every servo and turn off each of them
	for(int cnt=0; cnt<12;cnt++)
	{
		outBuff[0]=ACK;
		setup=Servo_Channels[cnt]->actual_status;
		if((setup==RX1_PWM || setup==RX2_PWM) && isValid_PWM_Channel(Servo_Channels[cnt]->PWM_CH))
		{
			if(PWM_Stop(Servo_Channels[cnt]->PWM_CH_handle)!=HAL_OK)
			{
				outBuff[0]=NACK;
				break;
			}
		}
		else if(setup==RX1_DD || setup==RX2_DD)
		{
			//Vészleállás a DD-re?
		}
		else // CAN actuators
		{
			Servo_Channels[cnt]->CANServo_handle->cmd_struct.e_stop=e_stop_on_mtr_free;
			if(CANServo_write_reg(Servo_Channels[cnt]->CANServo_handle, power_config_reg, can_and_servo_broadcast)!=HAL_OK)
			{
				outBuff[0]=NACK;
				break;
			}
			if(setup==RX1_CAN1 || setup==RX2_CAN1)
				CANx_transmit_servo_msg_queue(&hcan1);
			else if(setup==RX1_CAN2 || setup==RX2_CAN2)
				CANx_transmit_servo_msg_queue(&hcan2);
		}
	}
	I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,1);
	commPhase=receiveCommand;
}

void I2C_Receive_MoveServoData()
{
	I2C_Status=HAL_I2C_Slave_Receive_DMA(&hi2c1,inBuff.data,inBuff.nextmsg_length);
	commPhase=validateCheckSum;
}

void I2C_Send_ServoData()
{
	// Copy loaded data into output buffer
	for(int count=0;count<NumberOfServos;count++)
	{
		for(int i = 0;i < 2*Servo_CH_Handle_Length;i++)
			outBuff[count*NumberOfServos+i]=servoData[count].rawU8[i];
	}
	outBuff[2*NumberOfServos*Servo_CH_Handle_Length]=CheckSum_Calculate(outBuff,2*NumberOfServos*Servo_CH_Handle_Length);
	I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,2*NumberOfServos*Servo_CH_Handle_Length+1);
	commPhase=receiveCommand;
}

void I2C_Update_ServoData()
{
	I2C_Status=HAL_I2C_Slave_Receive_DMA(&hi2c1,inBuff.data,inBuff.nextmsg_length);
	commPhase=validateCheckSum;
}

void I2C_Send_HeaderData()
{
	FlushBuffer(); // Need because of ST stupid things
	for(int i=0;i<HeaderLength;i++)
		outBuff[i]=headerData.rawU8[i];
	outBuff[HeaderLength]=CheckSum_Calculate(outBuff,HeaderLength);
	I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,HeaderLength+1);
	commPhase=receiveCommand;
}

void I2C_Update_HeaderData()
{
	I2C_Status=HAL_I2C_Slave_Receive_DMA(&hi2c1,inBuff.data,inBuff.nextmsg_length);
	commPhase=validateCheckSum;
}

void I2C_SaveData_inEEPROM()
{
	if(CONF_Store()==HAL_OK)
		outBuff[0]=ACK;
	else
		outBuff[0]=NACK;
	I2C_Status=HAL_I2C_Slave_Transmit_DMA(&hi2c1,outBuff,1);
	commPhase=receiveCommand;
}

void FlushBuffer()
{
	for(int i=0;i<sizeof(outBuff);i++)
			outBuff[i]=0;
}
