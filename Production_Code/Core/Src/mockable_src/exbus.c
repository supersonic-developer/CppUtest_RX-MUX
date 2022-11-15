/*
 * exbus.c
	http://www.jetimodel.com/en/Telemetry-Protocol/JETI-Telemetry-Communication-Protocol/
 *
 *  Created on: Feb 15, 2021
 *      Author: andkovac
 */
#include "exbus.h"
#include "error_detection.h"
#include "tim.h"


// global variables for RC1 communication
EX_BUS_ChannelData RC1_EXBusRxBuffer1;
EX_BUS_ChannelData RC1_EXBusRxBuffer2;
uint8_t RC1_EXBus_Flag_NewChDataReceived = 0;
uint16_t RC1_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];
EX_Bus_Comm_Struct RC1_EXBus_struct;


// global variables for RC2 communication
EX_BUS_ChannelData RC2_EXBusRxBuffer1;
EX_BUS_ChannelData RC2_EXBusRxBuffer2;
uint8_t RC2_EXBus_Flag_NewChDataReceived = 0;
uint16_t RC2_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];
EX_Bus_Comm_Struct RC2_EXBus_struct;


void EXBus_Init()
{
	RC1_EXBus_struct.commState=Wait_Header;
	RC1_EXBus_struct.usedBuffer=&RC1_EXBusRxBuffer1;
	RC1_EXBus_struct.validBuffer=&RC1_EXBusRxBuffer2;
	RC1_EXBus_struct.NewChDataReceived=&RC1_EXBus_Flag_NewChDataReceived;
	RC1_EXBus_struct.Received_PPM_Values=&RC1_EXBus_received_ppm_values[0];
	RC1_EXBus_struct.UART_Flag_TxReady=1;
	RC1_EXBus_struct.huart=&huart4;
	RC1_EXBus_struct.sourceOfControl=&EXBus_RC1_src_struct;

	RC2_EXBus_struct.commState=Wait_Header;
	RC2_EXBus_struct.usedBuffer=&RC2_EXBusRxBuffer1;
	RC2_EXBus_struct.validBuffer=&RC2_EXBusRxBuffer2;
	RC2_EXBus_struct.NewChDataReceived=&RC2_EXBus_Flag_NewChDataReceived;
	RC2_EXBus_struct.Received_PPM_Values=&RC2_EXBus_received_ppm_values[1];
	RC2_EXBus_struct.UART_Flag_TxReady=1;
	RC2_EXBus_struct.huart=&huart2;
	RC2_EXBus_struct.sourceOfControl=&EXBus_RC2_src_struct;

}

void EXBus_RxCallback_Handler(EX_Bus_Comm_Struct* currentRC)
{
	if(currentRC->commState==Wait_Header && // if we wait header and received header 1st byte
	(currentRC->receivedByte==EXBUS_CH_DATA_MSG || currentRC->receivedByte==EXBUS_TELEM_OR_JETIBOX_REQUEST))
	{
		currentRC->receivedBytes=0;
		currentRC->usedBuffer->rawEXBusData[currentRC->receivedBytes++]=currentRC->receivedByte;
		currentRC->commState=Data_Flow;
	} //if header was received and now we are getting data flow
	else if(currentRC->commState==Data_Flow && currentRC->receivedBytes<sizeof(currentRC->usedBuffer->rawEXBusData))
	{
		currentRC->usedBuffer->rawEXBusData[currentRC->receivedBytes++]=currentRC->receivedByte;
		if(currentRC->usedBuffer->len==currentRC->receivedBytes)
		{
			currentRC->commState=Wait_Header;
			currentRC->UART_Flag_RxReady=1;
			EX_BUS_ChannelData *temp=currentRC->usedBuffer;
			currentRC->usedBuffer=currentRC->validBuffer;
			currentRC->validBuffer=temp;
		}
	} // some error occured, restart receiving cycle and save error
	else
	{
		errors.rc_input|=EXBUS_ERROR;
		currentRC->commState=Wait_Header;
	}
	currentRC->UART_Status=HAL_UART_Receive_DMA(currentRC->huart, &currentRC->receivedByte, 1);
}

EX_Bus_Comm_Struct* Select_RC(uint8_t RC_ID)
{
	if(RC_ID==1)
		return &RC1_EXBus_struct;
	else if(RC_ID==2)
		return &RC2_EXBus_struct;
	else
		return NULL;
}
//Functions to calculate crc16 (16 bit checksum) based on the received bytes
uint16_t crc_ccitt_update( uint16_t crc, uint8_t data )
{
	uint16_t ret_val;
	data ^= (uint8_t)(crc) & (uint8_t)(0xFF);
	data ^= data << 4;
 	ret_val = ((((uint16_t)data << 8) | ((crc & 0xFF00) >> 8)) ^ (uint8_t)(data >> 4) ^ ((uint16_t)data << 3));
 	return ret_val;
}

uint16_t get_crc16z(uint8_t *p, uint16_t len)
{
	uint16_t crc16_data=0;
	while(len--)
	{
		crc16_data=crc_ccitt_update(crc16_data, p[0]);
		p++;
	}
	return crc16_data;
}

void Update_EXBus_Struct(EX_Bus_Comm_Struct* currentRC)
{
	if(currentRC==NULL)
		return;
	// Refresh last valid frame time
	currentRC->sourceOfControl->timestamp_last_valid_frame=__HAL_TIM_GET_COUNTER(&htim6);

	// Set flag to main loop and copy data
	*(currentRC->NewChDataReceived)=1;
	for(int i=0;i<EXBUS_NUM_OF_CHANNELS;i++)
	{
		// Copy data and rescale it (original unit of data is 125ns, the new is 200ns)
		*(currentRC->Received_PPM_Values+i)=currentRC->validBuffer->otherData[i]*125/200;
		//RC1_EXBus_received_ppm_values[i]=RC1_ValidBuffer->otherData[i]*125/200;
		/*if(EXBus_received_ppm_values[i]>10000)
			EXBus_received_ppm_values[i]=10000;
		else if(EXBus_received_ppm_values[i]<5000)
			EXBus_received_ppm_values[i]=5000;*/
	}

	// Clear buffer
	for(int i=0;i<sizeof(RC1_EXBusRxBuffer1);i++)
		currentRC->validBuffer->rawEXBusData[i]=0;
}

void Send_Telemetry_Message(EX_Bus_Comm_Struct* currentRC)
{
	if(currentRC==NULL)
		return;
	currentRC->txBuffer.header[0]=EXBUS_TELEM_HEADER;
	currentRC->txBuffer.header[1]=EXBUS_RESP_ENABLED;
	currentRC->txBuffer.len=8;
	currentRC->txBuffer.packetID=currentRC->validBuffer->packetID;
	currentRC->txBuffer.dataID=EXBUS_EXTELEM;
	currentRC->txBuffer.dataLen=0;
	currentRC->txBuffer.otherData[0]=get_crc16z(currentRC->txBuffer.rawEXBusData,currentRC->txBuffer.len-2);
	if(currentRC->UART_Flag_TxReady)
	{
		currentRC->UART_Flag_TxReady=0;
		currentRC->UART_Status=HAL_UART_AbortReceive(currentRC->huart);
		currentRC->UART_Status=HAL_UART_Transmit_DMA(currentRC->huart,currentRC->txBuffer.rawEXBusData , currentRC->txBuffer.len);
	}
}

void EX_BUS_Handler(uint8_t RC_ID)
{
	EX_Bus_Comm_Struct* currentRC=Select_RC(RC_ID);
	if(currentRC==NULL)
		return;
	if(currentRC->UART_Flag_RxReady)
	{
		currentRC->UART_Flag_RxReady=0;
		uint16_t crc=currentRC->validBuffer->otherData[currentRC->validBuffer->dataLen/2];
		/* Check:
		 * + if the header was correct
		 * + if it was a channel data message
		 * + if the CRC was correct
		 */
		if(currentRC->validBuffer->header[0]==EXBUS_CH_DATA_MSG &&
		   currentRC->validBuffer->dataID==EXBUS_DATAID &&
		   (get_crc16z(currentRC->validBuffer->rawEXBusData,currentRC->validBuffer->len-2)==crc))
		{	Update_EXBus_Struct(currentRC);	}
		/* In case of telemetry request check:
		 * + if the header was correct
		 * + if it was a telemetry request message
		 * + if respond is enabled
		 * + if the CRC was correct
		 */
		if(currentRC->validBuffer->header[0]==EXBUS_TELEM_OR_JETIBOX_REQUEST &&
		   currentRC->validBuffer->dataID==EXBUS_EXTELEM &&
		   currentRC->validBuffer->header[1]==EXBUS_RESP_ENABLED &&
		   (get_crc16z(currentRC->validBuffer->rawEXBusData,currentRC->validBuffer->len-2)==crc))
		{	Send_Telemetry_Message(currentRC);	}
	}
	else if(currentRC->huart->RxState==HAL_UART_STATE_READY && currentRC->huart->gState==HAL_UART_STATE_READY)
		currentRC->UART_Status=HAL_UART_Receive_DMA(currentRC->huart, &currentRC->receivedByte, 1);
}




