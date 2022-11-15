/*
 * indicators.c
 *
 *  Created on: 2020. �pr. 23.
 *      Author: Kov�cs Andr�s
 */

/* Includes ------------------------------------------------------------------*/
#include "indicators.h"

#include "gpio.h"
#include "tim.h"

struct IND_LED_Type greenLED;
struct IND_LED_Type redLED;
struct IND_LED_Type rgbLED;

// Use when we switch between led states
LED_State tempState;


void checkPeriod(IND_LED* led) {
	// Check if the led is configured to blink
	if(led->period) {
		++(led->ms);
		if(led->ms > led->period) {
			led->needToUpdate = 1;
			//Reset "timer"
			led->ms = 0;
		}
	}
}

void setRGBLed() {
	switch(rgbLED.state) {
		case Off:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_SET);
			break;
		case On:
			return;
		case Red:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_SET);
			break;
		case Green:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_SET);
			break;
		case Blue:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_RESET);
			break;
		case Aqua:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_RESET);
			break;
		case Pink:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_RESET);
			break;
		case Yellow:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_SET);
			break;
		case White:
			HAL_GPIO_WritePin(RGBRLed_GPIO_Port,RGBRLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBGLed_GPIO_Port,RGBGLed_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGBBLed_GPIO_Port,RGBBLed_Pin,GPIO_PIN_RESET);
			break;
	}
}

void IND_Init() {

	//Init green turned off //green normal blinking for normal operation moved to app.c -> APP_init()
	greenLED.led = Green_LED;
	greenLED.state = Off;
	greenLED.prevState = Off;
	greenLED.needToUpdate = 0;
	greenLED.period = No;
	greenLED.ms = 0;

	//Init red led: turned off
	redLED.led = Red_LED;
	redLED.state = Off;
	redLED.prevState = Off;
	redLED.needToUpdate = 0;
	redLED.period = No;
	redLED.ms = 0;

	//Init rgb led: turned off
	rgbLED.led = RGB_LED;
	rgbLED.state = Off;
	rgbLED.prevState = Off;
	rgbLED.needToUpdate = 0;
	rgbLED.period = No;
	rgbLED.ms = 0;

	//Turn off RGB led
	setRGBLed();
}

void IND_SetLED(LED led, LED_State state, LED_BlinkPeriod period) {
	switch (led) {
		case Green_LED:
			//On and Off state can be only applied
			if(state == On || state == Off) {
				greenLED.state = state;
			}
			greenLED.period = period;
			greenLED.needToUpdate = 1;
			break;
		case Red_LED:
			//On and Off state can be only applied
			if(state == On || state == Off) {
				redLED.state = state;
			}
			redLED.period = period;
			redLED.needToUpdate = 1;
			break;
		case RGB_LED:
			//Every state can be applied except On state -> White
			if(state != On) {
				rgbLED.state = state;
			}
			rgbLED.period = period;
			rgbLED.needToUpdate = 1;
			break;
	}
}

void IND_Handler() {

	// Check whether leds need to blink and if they need, observe if period has elapsed and set needToUpdate flags
	checkPeriod(&greenLED);
	checkPeriod(&redLED);
	checkPeriod(&rgbLED);

	if(greenLED.needToUpdate) {
		greenLED.needToUpdate = 0;

		if(greenLED.state == On) {
			HAL_GPIO_WritePin(GreenLed_GPIO_Port,GreenLed_Pin,GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GreenLed_GPIO_Port,GreenLed_Pin,GPIO_PIN_RESET);
		}
		//Update the current state and store the previous one
		tempState = greenLED.state;
		greenLED.state = greenLED.prevState;
		greenLED.prevState = tempState;
	}
	if(redLED.needToUpdate) {
		redLED.needToUpdate = 0;

		if(redLED.state == On) {
			HAL_GPIO_WritePin(RedLed_GPIO_Port,RedLed_Pin,GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(RedLed_GPIO_Port,RedLed_Pin,GPIO_PIN_RESET);
		}
		//Update the current state and store the previous one
		tempState = redLED.state;
		redLED.state = redLED.prevState;
		redLED.prevState = tempState;

	}
	if(rgbLED.needToUpdate) {
		rgbLED.needToUpdate = 0;

		setRGBLed();

		tempState = rgbLED.state;
		rgbLED.state = rgbLED.prevState;
		rgbLED.prevState = tempState;
	}
}

