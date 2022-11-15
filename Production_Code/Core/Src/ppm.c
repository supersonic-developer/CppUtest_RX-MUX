/*
* ppm.c
*/

#include "ppm.h"
#include "rc_superv_logic.h"
#include "error_detection.h"
#include "iwdg.h"

uint8_t PPM_Flag_RC1_DataIsAvailable = 0;
uint8_t PPM_Flag_RC2_DataIsAvailable = 0;

uint16_t PPM_RC1Buffer[NUM_OF_PPM_CHANNELS];
uint16_t PPM_RC2Buffer[NUM_OF_PPM_CHANNELS];

uint32_t bufferRC1[NUM_OF_PPM_CHANNELS+1];
uint8_t bufferRC1Idx = 0;

uint32_t bufferRC2[NUM_OF_PPM_CHANNELS+1];
uint8_t bufferRC2Idx  = 0;

uint32_t timeStamp1 = 0;
uint32_t timeStamp2 = 0;

uint32_t prevRC1 = 0;
uint32_t currRC1 = 0;

uint32_t prevRC2 = 0;
uint32_t currRC2 = 0;

uint8_t buffIndex = 0;
uint8_t offset;


HAL_StatusTypeDef processTimeStamps(FIFO_Id fifo,
									uint32_t* current,
									uint32_t* previous,
									uint32_t* sourceBuffer,
									uint16_t* targetBuffer,
									uint8_t* idx,
									uint8_t* flag)
{

	while(FIFO_Pop32(fifo, current) != FIFO_EMPTY) {

		if(*current > *previous) {
			sourceBuffer[*idx] = *current - *previous;   //sourceBuffer[bufferRC1Idx] = *current - *previous;
		} else {
			sourceBuffer[*idx] = ((0xFFFFFFFF - *previous) + *current) + 1;  //TODO ezt nezd meg hogy nincs-e hit, elvileg 14 perc utan kene hogy legyen
		}

		if((sourceBuffer[*idx] > PPM_GAP_VALUE) && (*previous != 0) ) {   //elso hibat megszurni

			if(*idx == NUM_OF_PPM_CHANNELS) {
				/* full PPM frame received, set, flag, copy to output buffer */
				*flag = 1;
				for(int i = 0; i < NUM_OF_PPM_CHANNELS; ++i) {
					if (sourceBuffer[i] > PPM_MAX_VALUE + PPM_TOLERANCE || sourceBuffer[i] < PPM_MIN_VALUE - PPM_TOLERANCE){
						/* invalid ppm data, log error */
						if(fifo == FIFO_RC1){
							errors.rc_input |= PPM_RC1_INVALID_FRAME;
						}
						else if(fifo == FIFO_RC2){
							errors.rc_input |= PPM_RC2_INVALID_FRAME;
						}
					} else {
						targetBuffer[i] = (uint16_t)sourceBuffer[i];
					}
				}

				/* store timestamp for error detection */
				if(fifo == FIFO_RC1){
					PPM_RC1_src_struct.timestamp_last_valid_frame = __HAL_TIM_GET_COUNTER(&htim6);
					PPM_RC1_src_struct.new_data_FLAG = 1;
				}
				else if(fifo == FIFO_RC2){
					PPM_RC2_src_struct.timestamp_last_valid_frame = __HAL_TIM_GET_COUNTER(&htim6);
					PPM_RC2_src_struct.new_data_FLAG = 1;
				}
			} else {
				/*partial frame received */
				for(int i = 0; i < *idx; ++i) {
					// don't copy! targetBuffer[PPM_NUM_OF_CHANNELS-*idx + i] = sourceBuffer[i];
				}
			}

			*idx = 0;
			*previous = *current;


			return HAL_OK;
		}

		(*idx)++;
		*previous = *current;
		*current = 0;

		if((*idx)  > NUM_OF_PPM_CHANNELS) {
			(*idx) = 0;
			return HAL_ERROR;
		}
	}

	return HAL_OK;

}

HAL_StatusTypeDef PPM_Init() {

	PPM_Flag_RC1_DataIsAvailable = 0;
	PPM_Flag_RC2_DataIsAvailable = 0;
	prevRC1 = 0;
	currRC1 = 0;
	prevRC2 = 0;
	currRC2 = 0;

	bufferRC1Idx = 0;
	bufferRC2Idx  = 0;
	for(int i = 0; i < NUM_OF_PPM_CHANNELS; ++i) {
		bufferRC1[i] = 0;
		bufferRC2[i] = 0;
		PPM_RC1Buffer[i] = 0;
		PPM_RC2Buffer[i] = 0;

	}

	#if (USE_RC1_PPM == 1U)
	if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK)
		errors.rc_input |= PPM_RC1_INIT_FAILED;
	#endif

	#if (USE_RC2_PPM == 1U)
	if (HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2) != HAL_OK)
		errors.rc_input |= PPM_RC2_INIT_FAILED;
	#endif


	return HAL_OK;
}

HAL_StatusTypeDef PPM_Handle() {

	if(TIM_Flag_ReceivedRC1)
	{
		/* Clear flag from timer IC callback */
		TIM_Flag_ReceivedRC1 = 0;

		/* If we are using RC1 PPM process the data */
		#if (USE_RC1_PPM == 1U)
			if(processTimeStamps(FIFO_RC1, &currRC1, &prevRC1,
			 bufferRC1,PPM_RC1Buffer, &bufferRC1Idx, &PPM_Flag_RC1_DataIsAvailable) != HAL_OK) {
				return HAL_ERROR;
			}
		#endif
	}

	if(TIM_Flag_ReceivedRC2)
	{
		/* Clear flag from timer IC callback */
		TIM_Flag_ReceivedRC2 = 0;

		/* If we are using RC2 PPM process the data */
		#if (USE_RC2_PPM == 1U)
		if(processTimeStamps(FIFO_RC2,
						&currRC2,
						&prevRC2,
						bufferRC2,
						PPM_RC2Buffer,
						&bufferRC2Idx,
						&PPM_Flag_RC2_DataIsAvailable) != HAL_OK) {
			return HAL_ERROR;
		}
		#endif
}


	return HAL_OK;
}
