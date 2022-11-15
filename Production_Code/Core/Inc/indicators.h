/*
 * indicators.h
 *
 *  Created on: 2020. �pr. 23.
 *      Author: Kov�cs Andr�s
 */

#ifndef INC_INDICATORS_H_
#define INC_INDICATORS_H_


#include "gpio.h"

#define NO_BLINK 0
#define NORMAL_BLINK 1000 //ms
#define FAST_BLINK 500 //ms
#define ULTRAFAST_BLINK 200 //ms

#define MAX_PERIOD 9999


typedef enum LED_Type {
	Green_LED,
	Red_LED,
	RGB_LED
}LED;

typedef enum LED_StateType {
	Off,
	On,
	Red,
	Green,
	Blue,
	Aqua,
	Pink,
	Yellow,
	White

}LED_State;

typedef enum LED_BlinkPeriodType {
	No = NO_BLINK,
	Normal = NORMAL_BLINK,
	Fast = FAST_BLINK,
	UltraFast = ULTRAFAST_BLINK
}LED_BlinkPeriod;



typedef struct IND_LED_Type{
	LED led;
	LED_State state;
	LED_State prevState;
	uint8_t needToUpdate;
	uint16_t period;
	uint16_t ms;
}IND_LED;




void IND_Init();

void IND_SetLED(LED led, LED_State state, LED_BlinkPeriod period);

void IND_Handler();



#endif /* INC_INDICATORS_H_ */
