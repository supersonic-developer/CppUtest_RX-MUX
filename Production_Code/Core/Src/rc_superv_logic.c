/*
 * rc_superv_logic.c
 *
 * TIM6 is used for timestamping each data frame (RC inputs as well as AP) when they come in, and than this code
 * compares it to the current value of the timer. If it exceeds the defined constants, error bits are set and status info is updated
 *
 * TIM6 is counting up every 0.1 ms, so a full cycle for the timer is 6.5535 s
 *
 *
 *  Created on: Oct 4, 2021
 *      Author: fbalazs
 */

#include "rc_superv_logic.h"
#include "exbus.h"
#include "indicators.h"
#include "error_detection.h"

SignalSource_Enum_t Active_RC_Source = Error_No_RC_Input;
RC_Src_Struct_t* pActive_RC_Source = NULL;

/* Flags:
 *
 *	PPM_Flag_RC1_DataIsAvailable -> set to 1 when PPM frame is fully received
 * 	PPM_Flag_RC2_DataIsAvailable -> set to 1 when PPM frame is fully received
 * 	EXBus_Flag_NewChDataReceived    -> set to 1 when EXBus package is fully received. Data is available in EX_BUS_ChannelData* ChannelDataPrev;
 *
 */

/*
 * Structures
 */
RC_Src_Struct_t PPM_RC1_src_struct; 		/* RC1 aka. Jeti 	 PPM signal*/
RC_Src_Struct_t EXBus_RC1_src_struct;		/* RC1 aka. Jeti 	 digital signal */
RC_Src_Struct_t PPM_RC2_src_struct; 		/* RC2 aka. 2nd Jeti PPM signal */
RC_Src_Struct_t EXBus_RC2_src_struct;		/* RC2 aka. 2nd Jeti digital signal*/

AP_Src_Struct_t AP_src_struct;				/* AutoPilot (this will actually indicate the SPI state)*/

/*
 *  private functions
 */
void Check_RC_SignalSource(RC_Src_Struct_t* signal, uint8_t* flag, uint16_t* buffer, uint16_t frame_missed_timeout, uint16_t error_timeout, uint16_t frame_missed_bit, uint16_t error_bit, uint16_t* error_struct_rc_field);
void Check_AP_SignalSource(AP_Src_Struct_t* signal, uint16_t timeout_frame, uint16_t timeout_error);



void Init_SignalSource_structures_ALL(void)
{
	PPM_RC1_src_struct.State = src_inactive;
	PPM_RC1_src_struct.timestamp_last_valid_frame = 0;
	PPM_RC1_src_struct.new_data_FLAG = 0;

	EXBus_RC1_src_struct.State = src_inactive;
	EXBus_RC1_src_struct.timestamp_last_valid_frame = 0;
	EXBus_RC1_src_struct.new_data_FLAG = 0;

	PPM_RC2_src_struct.State = src_inactive;
	PPM_RC2_src_struct.timestamp_last_valid_frame = 0;
	PPM_RC2_src_struct.new_data_FLAG = 0;

	EXBus_RC2_src_struct.State = src_inactive;
	EXBus_RC2_src_struct.timestamp_last_valid_frame = 0;
	EXBus_RC2_src_struct.new_data_FLAG = 0;

	AP_src_struct.State = src_inactive;
	AP_src_struct.timestamp_last_valid_frame = 0;
	AP_src_struct.new_data_FLAG = 0;
}


/*
 * Checks if an RC signal source is active, sets its state, watches for timeouts,
 * copies the data to the structure (if new data is available)
 *
 * time stamps get stored in the respective processing functions (see ppm.c, exbus.c, sbus.c)
 */
void Check_RC_SignalSource(RC_Src_Struct_t* signal,
						   uint8_t* flag,
						   uint16_t* buffer,
						   uint16_t frame_missed_timeout,
						   uint16_t error_timeout,
						   uint16_t frame_missed_bit,
						   uint16_t error_bit,
						   uint16_t* error_struct_rc_field)
{
	if(*flag)
	{
		*flag = 0;
		/* copy data */
		for (uint8_t idx=0; idx<NUM_OF_PPM_CHANNELS; idx++){
			signal->last_valid_data[idx] = buffer[idx];
		}

		signal->State = src_active;
	}

	/* if we already know there is an error, no need to check, if a new frame/package arrives it will reset the status */
	if(signal->State == src_inactive)
	{
		return;
	}


	/* get current timestamp for error detection */
	uint16_t last_frame_timestamp = signal->timestamp_last_valid_frame;
	uint16_t timer_value = __HAL_TIM_GET_COUNTER(&htim6);

	uint16_t delta = 0;

	/* calculate delta since last valid frame */
	if (timer_value >= last_frame_timestamp)
		delta = timer_value - last_frame_timestamp;
	else
		delta = (((uint16_t)0xFFFF - last_frame_timestamp) + timer_value) + 1U;

	/* error detection*/


	if( delta < frame_missed_timeout)
	{
		/* clear error bit for logging*/
		//TODO clear error bit(ha lesz uj SPI struktura), ez kell vagy eleg a globalis torles?
		/* clear indicator */
		//IND_SetLED(RGB_LED,Off,No);

	}

	/* 1 frame missed, or complete error */
	else
	{
		/* 1 frame missed */
		if( delta >= frame_missed_timeout /*&& delta < error_timeout*/)
		{
			/* set frame missed for logging*/
			*error_struct_rc_field |= frame_missed_bit;
			/* Set indicator */
			//IND_SetLED(RGB_LED,Yellow,No);

		}

		/* frame not detected for too long -> problem */
		if( delta >= error_timeout)
		{
			/*update status, delete stored data*/
			signal->State = src_inactive;
			for (uint8_t idx=0; idx<NUM_OF_PPM_CHANNELS; idx++){
				signal->last_valid_data[idx] = 0;
			}

			/* set error bit for logging*/
			*error_struct_rc_field |= error_bit;

			/* Set indicator */
			//IND_SetLED(RGB_LED,Pink,No);
		}
	}


}


/*
 * This function checks activity on the SPI bus used for communication with flightHAT. If the timeouts are reached the error bit are set
 * It will not check for the validity of the data, just that the HAL_SPI_TxRxCpltCallback() was called.
 */
void Check_AP_SignalSource(AP_Src_Struct_t* signal, uint16_t timeout_frame, uint16_t timeout_error)
{

	/* if we already know there is an error, no need to check, if a new frame/package arrives it will reset the status */
	if(signal->State == src_inactive)
	{
		return;
	}


	/* get current timestamp, and timestamp of last successful frame, for error detection */
	uint16_t last_frame_timestamp = signal->timestamp_last_valid_frame;
	uint16_t timer_value = (uint16_t)__HAL_TIM_GET_COUNTER(&htim6);

	/* calculate delta since last valid frame */
	uint16_t delta = 0;

	if (timer_value >= last_frame_timestamp)
		delta = timer_value - last_frame_timestamp;
	else
	{
		delta = (((uint16_t)0xFFFF - last_frame_timestamp) + timer_value) + 1U;

	}

	/* error detection*/
	if( delta < timeout_frame)
	{
		/* clear error bit for logging*/
		// debug HAL_GPIO_WritePin(user_gpio_GPIO_Port, user_gpio_Pin, GPIO_PIN_RESET);  //timing
		//TODO clear error bit(ha lesz uj SPI struktura)
	}

	/* 1 frame missed, or complete error */
	else
	{
		/* 1 frame missed */
		if( delta >= timeout_frame && delta < timeout_error)
		{
			/* set error bit for logging*/
			//TODO set frame_missed bit(ha lesz uj SPI struktura), ezeknek van ertelme?
			//IND_SetLED(Red_LED,Off,No);
		}

		/* frame not detected for too long -> problem */
		if( delta >= timeout_error)
		{
			//HAL_GPIO_WritePin(user_gpio_GPIO_Port, user_gpio_Pin, GPIO_PIN_SET);  //timing
			/*update status, delete pointer */
			signal->State = src_inactive;
			//signal->p_to_last_valid_data = NULL;


			/* set error bit for logging*/
			//TODO set error bit (ha lesz uj SPI struktura)
		}
	}
}


/*
 * Check all RC and AP signals for activity
 */
void Check_SignalSources_ALL(void)
{
	/*PPM RC1 */
    #if (USE_RC1_PPM == 1U)
	Check_RC_SignalSource(&PPM_RC1_src_struct,
						  &PPM_Flag_RC1_DataIsAvailable,
						  PPM_RC1Buffer,
						  PPM_RC1_Frame_Timeout,
						  PPM_RC1_Error_Timeout,
						  PPM_RC1_FRAME_MISSED,
						  PPM_RC1_ERROR,
						  &(errors.rc_input));
	#endif


	/*EXBus RC1 */
	#if (USE_RC1_EXBUS == 1U)
	Check_RC_SignalSource(&EXBus_RC1_src_struct,
					   	  &RC1_EXBus_Flag_NewChDataReceived,
						  RC1_EXBus_received_ppm_values,
						  EXBus_Frame_Timeout,
						  EXBus_Error_Timeout,
						  EXBUS_FRAME_MISSED,
						  EXBUS_ERROR,
						  &(errors.rc_input));
	#endif

	/*PPM RC2 */
	#if (USE_RC2_PPM  == 1U)
	Check_RC_SignalSource(&PPM_RC2_src_struct,
					   	  &PPM_Flag_RC2_DataIsAvailable,
						  PPM_RC2Buffer,
						  PPM_RC2_Frame_Timeout,
						  PPM_RC2_Error_Timeout,
						  PPM_RC2_FRAME_MISSED,
						  PPM_RC2_ERROR,
						  &(errors.rc_input));
	#endif

	/*EXBus RC2 */
	#if (USE_RC1_EXBUS == 1U)
	Check_RC_SignalSource(&EXBus_RC2_src_struct,
						  &RC2_EXBus_Flag_NewChDataReceived,
						  RC2_EXBus_received_ppm_values,
						  EXBus2_Frame_Timeout,
						  EXBus2_Error_Timeout,
						  EXBUS2_FRAME_MISSED,
						  EXBUS2_ERROR,
						  &(errors.rc_input));
	#endif


	/* Autopilot */
	Check_AP_SignalSource(&AP_src_struct,
						  AP_Frame_Timeout,
						  AP_Error_Timeout);
}


SignalSource_Enum_t Select_RC_SignalSource(void)
{
	uint8_t RC2_avilable;
	RC2_avilable = (EXBus_RC2_src_struct.State == src_active || PPM_RC2_src_struct.State == src_active) ? 1 : 0;

	if(EXBus_RC1_src_struct.State == src_active){
		if (EXBus_RC1_src_struct.last_valid_data[RC_Select_Channel] < RC_Select_Threshold || RC2_avilable == 0)
		{
			pActive_RC_Source = &EXBus_RC1_src_struct;
			IND_SetLED(RGB_LED,Pink,No);
			return RC1_EXBus;
		}
	}

	if(PPM_RC1_src_struct.State == src_active){
		if (PPM_RC1_src_struct.last_valid_data[RC_Select_Channel] < RC_Select_Threshold || RC2_avilable == 0)
		{
			pActive_RC_Source = &PPM_RC1_src_struct;
			IND_SetLED(RGB_LED,Blue,No);
			return RC1_PPM;
		}
	}

	if(EXBus_RC2_src_struct.State == src_active){
		pActive_RC_Source = &EXBus_RC2_src_struct;
		IND_SetLED(RGB_LED,White,No);
		return RC2_EXBus;
	}

	if(PPM_RC2_src_struct.State == src_active){
		pActive_RC_Source = &PPM_RC2_src_struct;
		IND_SetLED(RGB_LED,Yellow,No);
		return RC2_PPM;
	}

	/* if we got to here we have a problem */
	pActive_RC_Source = NULL;
	IND_SetLED(RGB_LED,Off,No);
	return Error_No_RC_Input;
}
