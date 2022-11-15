/*
 * app.h
 *
 *  Created on: Sep 21, 2020
 *      Author: andkovac
 */

#ifndef APP_H_
#define APP_H_


#include "stm32f4xx.h"
#include "error_detection.h"

/* turn on/off independent watchdog */
#define USE_IWDG (1)

/* if =1 the MCU will stop the IWDG when entering HALT mode, so you can debug the code with active IWDG */
#define IWDG_DEBUG_ON (1)

/* warning for turning IWDG off*/
#if USE_IWDG == (0)
	#warning Indipendent WATCHDOG disabled!!! It should only be disabled for debug purpuses.
#endif

typedef enum APP_StateType{
	ConfigState,
	RunState,
	ErrorState,
}APP_State;


typedef enum RXMUX_ID
{
	RXMUX1 = 1U,
	RXMUX2 = 2U
}RXMUX_ID;

HAL_StatusTypeDef APP_Init();
HAL_StatusTypeDef APP_Go();
void APP_ErrorHandler();
void copy_PWM_To_SPI_Struct(void);
void Set_StatusFlags();
extern RXMUX_ID rxmuxID;
extern APP_State state;
extern uint8_t IWDG_Reset_FLAG;
extern uint16_t RXMUptime;

extern uint8_t command_DD_and_CAN_timing_FLAG;     /* set to one if DD and/or CAN servos should be updated */

extern Source_Ind_Types source_indicator;

#endif /* APP_H_ */
