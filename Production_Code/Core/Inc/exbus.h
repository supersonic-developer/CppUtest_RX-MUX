/*
 * exbus.h
 *
 *  Created on: Feb 15, 2021
 *      Author: andkovac
 */

#ifndef EXBUS_H_
#define EXBUS_H_

#include "stm32f4xx_hal.h"
#include "rc_superv_logic.h"
#include "usart.h"



/* Defines */
#define EXBUS_NUM_OF_CHANNELS NUM_OF_PPM_CHANNELS
/* ----------------- HEADER -----------------*/
// Possible 1st byte from receiver
#define EXBUS_CH_DATA_MSG				0x3E
#define EXBUS_TELEM_OR_JETIBOX_REQUEST	0x3D
// Possible 2nd byte from receiver
#define EXBUS_RESP_ENABLED				0x01
#define EXBUS_RESP_DISABLED			 	0x03
// Possible 1st byte to receiver (transmitter direction)
#define EXBUS_TELEM_HEADER				0x3B
/* ------------- END OF HEADER --------------*/
// Possible data IDs
#define EXBUS_DATAID 					0x31
#define EXBUS_EXTELEM 					0x3A
#define EXBUS_REQEST_JETIBOX_MENU		0x3B


/* Structures and enumerates used for communication */
typedef struct EX_BUS_ChannelData {
	union{
		struct{
			uint8_t header[2];
			uint8_t len;
			uint8_t packetID;
			uint8_t dataID;
			uint8_t dataLen;
			uint16_t otherData[25]; // Maximum 24 channel + CRC
		};
		uint8_t rawEXBusData[56];
	};
}EX_BUS_ChannelData;


typedef enum T_EXBus_State
{
	Wait_Header,
	Data_Flow,
}EXBus_State;

typedef struct EX_Bus_Comm_Struct
{
	struct{
		EXBus_State commState;
		uint8_t receivedByte;
		EX_BUS_ChannelData* usedBuffer;
		EX_BUS_ChannelData* validBuffer;
		EX_BUS_ChannelData  txBuffer;
		uint16_t receivedBytes;
		HAL_StatusTypeDef UART_Status;
		uint8_t UART_Flag_RxReady;
		uint8_t UART_Flag_TxReady;
		/* These variables used in rc_superv_logic or in usart,
		 * so it is useful to access them outside of structure variable */
		uint8_t* NewChDataReceived;
		uint16_t* Received_PPM_Values;
		UART_HandleTypeDef* huart;
		RC_Src_Struct_t* sourceOfControl;
	};
}EX_Bus_Comm_Struct;


extern uint8_t RC1_EXBus_Flag_NewChDataReceived;
extern EX_BUS_ChannelData RC1_EXBusRxBuffer1;
extern EX_BUS_ChannelData RC1_EXBusRxBuffer2;
extern uint16_t RC1_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];
/* Global variables */
extern EX_Bus_Comm_Struct RC1_EXBus_struct;
extern EX_Bus_Comm_Struct RC2_EXBus_struct;
// Variables for RC supervisor logic
extern uint8_t RC1_EXBus_Flag_NewChDataReceived;
extern uint16_t RC1_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];
extern uint8_t RC2_EXBus_Flag_NewChDataReceived;
extern uint16_t RC2_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];



/* Prototypes */
void EX_BUS_Handler(uint8_t RC_ID);
uint16_t get_crc16z(uint8_t *p, uint16_t len);
uint16_t crc_ccitt_update( uint16_t crc, uint8_t data );
void Update_EXBus_Struct(EX_Bus_Comm_Struct* currentRC);
void Send_Telemetry_Message(EX_Bus_Comm_Struct* currentRC);
EX_Bus_Comm_Struct* Select_RC(uint8_t RC_ID);
void EXBus_Init();
void EXBus_RxCallback_Handler(EX_Bus_Comm_Struct* currentRC);
EX_Bus_Comm_Struct* Select_RC(uint8_t RC_ID);



#endif /* EXBUS_H_ */
