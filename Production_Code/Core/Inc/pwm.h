/*
* pwm.h
*/


#ifndef INC_PWM_H_
#define INC_PWM_H_

#define FIRST_PWM_CH  (1u)
#define LAST_PWM_CH (12u)
#define PWM_MAX_VALUE (10000u)
#define PWM_MIN_VALUE (5000u)

#include "main.h"
#include "tim.h"


typedef enum __PWM_CH_IDs
{
	PWM_CH1_ID= 1U,
	PWM_CH2_ID = 2U,
	PWM_CH3_ID = 3U,
	PWM_CH4_ID = 4U,
	PWM_CH5_ID = 5U,
	PWM_CH6_ID = 6U,
	PWM_CH7_ID = 7U,
	PWM_CH8_ID = 8U,
	PWM_CH9_ID = 9U,
	PWM_CH10_ID = 10U,
	PWM_CH11_ID = 11U,
	PWM_CH12_ID = 12U
} PWM_CH_IDs ;

typedef struct PWM_CH
{
	uint8_t channelNum; 		/* PWM channel number */
	TIM_HandleTypeDef* htim; 	/* TIM instance */
	volatile uint32_t* ccrReg; 	/* TIM capture/compare register */
	uint32_t timChannel;		/* TIM output CH */
}PWM_CH_Typedef;




static PWM_CH_Typedef PWM_CH1  = {channelNum:PWM_CH1_ID, htim:&htim4, ccrReg:&TIM4->CCR1, timChannel:TIM_CHANNEL_1}; // PWM channel 1: TIM 4 channel 1
static PWM_CH_Typedef PWM_CH2  = {channelNum:PWM_CH2_ID, htim:&htim4, ccrReg:&TIM4->CCR2, timChannel:TIM_CHANNEL_2}; // PWM channel 2: TIM 4 channel 2
static PWM_CH_Typedef PWM_CH3  = {channelNum:PWM_CH3_ID, htim:&htim4, ccrReg:&TIM4->CCR3, timChannel:TIM_CHANNEL_3}; // PWM channel 3: TIM 4 channel 3
static PWM_CH_Typedef PWM_CH4  = {channelNum:PWM_CH4_ID, htim:&htim4, ccrReg:&TIM4->CCR4, timChannel:TIM_CHANNEL_4}; // PWM channel 4: TIM 4 channel 4

static PWM_CH_Typedef PWM_CH5  = {channelNum:PWM_CH5_ID, htim:&htim3, ccrReg:&TIM3->CCR1, timChannel:TIM_CHANNEL_1};
static PWM_CH_Typedef PWM_CH6  = {channelNum:PWM_CH6_ID, htim:&htim3, ccrReg:&TIM3->CCR2, timChannel:TIM_CHANNEL_2};
static PWM_CH_Typedef PWM_CH7  = {channelNum:PWM_CH7_ID, htim:&htim3, ccrReg:&TIM3->CCR3, timChannel:TIM_CHANNEL_3};
static PWM_CH_Typedef PWM_CH8  = {channelNum:PWM_CH8_ID, htim:&htim3, ccrReg:&TIM3->CCR4, timChannel:TIM_CHANNEL_4};


static PWM_CH_Typedef PWM_CH9  = {channelNum:PWM_CH9_ID,  htim:&htim1, ccrReg:&TIM1->CCR1, timChannel:TIM_CHANNEL_1};
static PWM_CH_Typedef PWM_CH10 = {channelNum:PWM_CH10_ID, htim:&htim1, ccrReg:&TIM1->CCR2, timChannel:TIM_CHANNEL_2};
static PWM_CH_Typedef PWM_CH11 = {channelNum:PWM_CH11_ID, htim:&htim1, ccrReg:&TIM1->CCR3, timChannel:TIM_CHANNEL_3};
static PWM_CH_Typedef PWM_CH12 = {channelNum:PWM_CH12_ID, htim:&htim1, ccrReg:&TIM1->CCR4, timChannel:TIM_CHANNEL_4};

/* Suppress "defined but not used warning" for this variable only (it is used but in other files, and the compiler complained) */
#pragma GCC diagnostic ignored "-Wunused-variable"
	static PWM_CH_Typedef* PWM_Channels[] = {&PWM_CH1, &PWM_CH2, &PWM_CH3, &PWM_CH4, &PWM_CH5, &PWM_CH6, &PWM_CH7, &PWM_CH8, &PWM_CH9, &PWM_CH10, &PWM_CH11, &PWM_CH12};
#pragma GCC diagnostic pop


HAL_StatusTypeDef PWM_Start(PWM_CH_Typedef* pwmCh);
HAL_StatusTypeDef PWM_Stop(PWM_CH_Typedef* pwmCh);
HAL_StatusTypeDef PWM_UpdateOutput(PWM_CH_Typedef* pwmCh, uint32_t outputValue);
HAL_StatusTypeDef PWM_StopAll();
uint8_t isValid_PWM_Channel(uint8_t ch_id);

/*
HAL_StatusTypeDef PWM_StartAll();
HAL_StatusTypeDef PWM_StopAll();
HAL_StatusTypeDef PWM_UpdateAll();
*/
#endif /*  INC_PWM_H */
