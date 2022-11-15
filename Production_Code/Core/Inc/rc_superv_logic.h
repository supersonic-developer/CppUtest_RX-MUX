/*
 * rc_superv_logic.h
 *
 *  Created on: Oct 4, 2021
 *      Author: fbalazs
 */

#ifndef INC_RC_SUPERV_LOGIC_H_
#define INC_RC_SUPERV_LOGIC_H_

//#include "main.h"
#include <stdint.h>
#include "ppm.h"

/* This section is used to ENABLE inputs */
#define USE_RC1_PPM		1U
#define USE_RC1_EXBUS	1U
#define USE_RC2_PPM		1U
#define USE_RC2_EXBUS	1U

/* Time interval in 0.1 ms after a source is declared inactive */
#define EXBus_Error_Timeout  	(10000)
#define PPM_RC1_Error_Timeout 	(10000)
#define EXBus2_Error_Timeout	(10000)
#define PPM_RC2_Error_Timeout 	(10000)
#define AP_Error_Timeout		(10000)

/* Time interval in 0.1 ms after a missing packet/frame is logged for a source */
//TODO ezeket az erteket bekalibralni(ha lesz uj SPI struktura)
#define EXBus_Frame_Timeout  	(1000)
#define PPM_RC1_Frame_Timeout 	(1000)
#define EXBus2_Frame_Timeout	(1000)
#define PPM_RC2_Frame_Timeout 	(1000)
#define AP_Frame_Timeout 		(1000)

#define RC_Select_Channel		(13)	 /* "ECU and CMD" channel index (FCC index), for changing between RC inputs */
#define RC_Select_Threshold 	(7600U)  /* 1520 us */
#define AP_Control_Channel 		(15)	 /* "Auto Pilot" channel (FCC index) */
#define AP_Control_Threshold	(8500U)


typedef enum SourceStateEnum_t {
	src_inactive,
	src_active
}SourceState_t;

typedef enum __SignalSource_Enum_t {
	RC1_PPM,
	RC1_EXBus,
	RC2_PPM,
	RC2_EXBus,
	RaspberryPi,
	Error_No_RC_Input,
}SignalSource_Enum_t;

typedef struct __RC_Source_Struct_t {
	uint16_t last_valid_data [NUM_OF_PPM_CHANNELS];  /* assumes that PPM EXBus and SBus all have the same number of channels */

	uint16_t timestamp_last_valid_frame;
	SourceState_t  State;
	uint8_t new_data_FLAG;

}RC_Src_Struct_t;

typedef struct __AP_Source_Struct_t {
	//uint16_t* p_to_last_valid_data;  /* assumes that PPM EXBus and SBus all have the same number of channels */

	volatile uint16_t timestamp_last_valid_frame;
	volatile SourceState_t  State;
	uint8_t new_data_FLAG;

}AP_Src_Struct_t;

/* Globals ----------------*/
extern SignalSource_Enum_t Active_RC_Source;
extern RC_Src_Struct_t* pActive_RC_Source;

extern RC_Src_Struct_t PPM_RC1_src_struct;
extern RC_Src_Struct_t PPM_RC2_src_struct;
extern RC_Src_Struct_t EXBus_RC1_src_struct;
extern RC_Src_Struct_t EXBus_RC2_src_struct;

extern AP_Src_Struct_t AP_src_struct;

void Init_SignalSource_structures_ALL(void);
void Check_SignalSources_ALL(void);  /* checks RC and AP signals, needs too be called as frequently as possible */

SignalSource_Enum_t Select_RC_SignalSource(void); /* actually selects which RC source to use in a given 5ms loop */

#endif /* INC_RC_SUPERV_LOGIC_H_ */
