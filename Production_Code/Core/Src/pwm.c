/*
* pwm.c
*/

#include "pwm.h"



HAL_StatusTypeDef PWM_Start(PWM_CH_Typedef* pwmCH) {

	if(HAL_TIM_PWM_GetState(pwmCH->htim) == HAL_TIM_STATE_READY) {
		//Start generating PWM signal
		if(HAL_TIM_PWM_Start(pwmCH->htim, pwmCH->timChannel) != HAL_OK) {
			  return HAL_ERROR;
		  }
	}

	return HAL_OK;
}
HAL_StatusTypeDef PWM_Stop(PWM_CH_Typedef* pwmCH) {

	//Stop generating PWM signal
	if(HAL_TIM_PWM_Stop(pwmCH->htim, pwmCH->timChannel) != HAL_OK) {
		  return HAL_ERROR;
	}

	return HAL_OK;
}

/* Output value has to be between PWM_MIN_VALUE and PWM_MAX_VALUE
 * In normal operation the function setting the outputValue before calling this.
 */
HAL_StatusTypeDef PWM_UpdateOutput(PWM_CH_Typedef* pwmCH, uint32_t outputValue) {

	/* check if there is actually a channel assigned */
	if(!isValid_PWM_Channel(pwmCH->channelNum)){
		return HAL_ERROR;
	}

	if(PWM_MIN_VALUE >= outputValue) {

		*(pwmCH->ccrReg) = (uint32_t)PWM_MIN_VALUE;

	} else if (PWM_MAX_VALUE <= outputValue) {

		*(pwmCH->ccrReg) = (uint32_t)PWM_MAX_VALUE;
	} else {

		*(pwmCH->ccrReg) = (uint32_t)outputValue;
	}
	return HAL_OK;
}

HAL_StatusTypeDef PWM_StopAll() {

	for(int i = 0; i < LAST_PWM_CH; ++i) {
		if(PWM_Channels[i]) {
			if(PWM_Stop(PWM_Channels[i]) != HAL_OK) {
				return HAL_ERROR;
			}
		}
	}
	return HAL_OK;
}



FORCE_INLINE uint8_t isValid_PWM_Channel(uint8_t ch_id){
	return (FIRST_PWM_CH < ch_id && LAST_PWM_CH > ch_id);
}

/*
HAL_StatusTypeDef PWM_StartAll() {

	for(int i = 0; i < LAST_PWM_CH; ++i) {
		if(PWM_EN[i] && PWM_Channels[i]) {
			if(PWM_Start(PWM_Channels[i]) != HAL_OK) {
				return HAL_ERROR;
			}
		}
	}
	return HAL_OK;
}

HAL_StatusTypeDef PWM_UpdateAll() {

	for(int i = 0; i < LAST_PWM_CH; ++i) {
			if(PWM_EN[i]) {
				if(PWM_UpdateOutput(PWM_Channels[i], PWM_Outputs[i]) != HAL_OK) {
					return HAL_ERROR;
				}
			}
		}
		return HAL_OK;

}
*/
