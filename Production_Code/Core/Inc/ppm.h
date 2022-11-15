/*
* ppm.h
*/


#ifndef INC_PPM_H_
#define INC_PPM_H_

#include "stdio.h"
#include "tim.h"
#include "fifo.h"


#define NUM_OF_PPM_CHANNELS (16) 	///< Number of input PPM Channels - 16
#define NUM_Of_PULSES_TO_DECODE (NUM_OF_PPM_CHANNELS+1) ///< Num of pulses to decode: 17
#define NUM_OF_PULSES_TO_DETECT (NUM_OF_PPM_CHANNELS+2) ///< Num of pulses to detect: 18
#define PPM_MIN_VALUE 5000 	/* 1 ms */
#define PPM_NEUTRAL_VALUE (7500u) /* 1.5 ms */
#define PPM_MAX_VALUE 10000 /* 2 ms */
#define PPM_GAP_VALUE 20000 /* 4 ms */
#define PPM_TOLERANCE 1250  /* 0.25 ms. Receiver should always put out between 0.75ms and 2.25ms */

typedef enum PPM_RCIdType {
	PPM_RC1,
	PPM_RC2
}PPM_RCId;

typedef enum PPM_ChIdType {
	PPM_Ch1,
	PPM_Ch2,
	PPM_Ch3,
	PPM_Ch4,
	PPM_Ch5,
	PPM_Ch6,
	PPM_Ch7,
	PPM_Ch8,
	PPM_Ch9,
	PPM_Ch10,
	PPM_Ch11,
	PPM_Ch12,
	PPM_Ch13,
	PPM_Ch14,
	PPM_Ch15,
	PPM_Ch16,
} PPM_ChId;

//typedef struct PPM_RecDataType {

//};


extern uint8_t PPM_Flag_RC1_DataIsAvailable;
extern uint8_t PPM_Flag_RC2_DataIsAvailable;

extern uint16_t PPM_RC1Buffer[];
extern uint16_t PPM_RC2Buffer[];


HAL_StatusTypeDef PPM_Init();
HAL_StatusTypeDef PPM_Handle();




#endif /*  INC_PPM_H */
