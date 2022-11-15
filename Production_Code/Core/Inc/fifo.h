/*
 * fifo.h
 *
 *  Created on: Sep 25, 2020
 *      Author: andkovac
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stm32f4xx_hal.h"
#include "can_servo.h"

#define MAX_FIFO_SIZE_U32 32  //nem lesz jo az implementacio csak 2 hatvanyokra mukodik
#define MAX_FIFO_SIZE_U8 128  //eredetileg U32 20, U8 80
#define MAX_FIFO_SIZE_CAN_S_MSG 16

typedef struct FIFOTypeU32 {
        uint8_t    in;
        uint8_t    out;
        uint8_t    mask;
        uint32_t   data[MAX_FIFO_SIZE_U32];
} FIFO32;

typedef struct FIFOTypeU8 {
        uint8_t 	in;
        uint8_t 	out;
        uint8_t 	mask;
        uint8_t 	data[MAX_FIFO_SIZE_U8];
} FIFO8;

typedef struct FIFOTypeCANServoMsg {
        uint8_t 	in;
        uint8_t 	out;
        uint8_t 	mask;
        CANServoTxMsg_Struct data[MAX_FIFO_SIZE_CAN_S_MSG];
} FIFO_CAN_S_MSG;

typedef enum FIFO_StatusType {
	FIFO_EMPTY,
	FIFO_FULL,
	FIFO_OK,
	FIFO_ERROR
}FIFO_Status;

uint8_t fifoIsEmpty32(FIFO32 * fifo);
uint8_t fifoIsFull32(FIFO32 * fifo);
FIFO_Status push32(FIFO32 * fifo, uint32_t data);
FIFO_Status pop32(FIFO32 * fifo, uint32_t * data);

uint8_t fifoIsEmpty8(FIFO8 * fifo);
uint8_t fifoIsFull8(FIFO8 * fifo);
FIFO_Status push8(FIFO8 * fifo, uint8_t data);
FIFO_Status pop8(FIFO8 * fifo, uint8_t * data);
uint8_t fifoUnused8(FIFO8* fifo);
uint8_t fifoLen8(FIFO8* fifo);

uint8_t fifoIsEmptyCANs(FIFO_CAN_S_MSG* fifo);
uint8_t fifoIsFullCANs(FIFO_CAN_S_MSG* fifo);
FIFO_Status pushCANs(FIFO_CAN_S_MSG* fifo, CANServoTxMsg_Struct data);
FIFO_Status popCANs(FIFO_CAN_S_MSG* fifo, CANServoTxMsg_Struct * data);
uint8_t fifoUnusedCANs(FIFO_CAN_S_MSG* fifo);
uint8_t fifoLenCANs(FIFO_CAN_S_MSG* fifo);


typedef enum FIFO_IdType {
	FIFO_RC1,
	FIFO_RC2,
	FIFO_EXBUS
}FIFO_Id;


void FIFO_Init();

FIFO_Status FIFO_Push32(FIFO_Id id, uint32_t data);
FIFO_Status FIFO_Pop32(FIFO_Id id, uint32_t* data);

FIFO_Status FIFO_Push8(FIFO_Id id, uint8_t data);
FIFO_Status FIFO_Pop8(FIFO_Id id, uint8_t* data);

#endif /* FIFO_H_ */
