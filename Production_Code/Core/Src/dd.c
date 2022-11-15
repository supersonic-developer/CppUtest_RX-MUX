/*
 * dd.c
 *
 * This file handles CANopen tasks, and implements DD control
 *
 *  Created on: Jan 17, 2022
 *      Author: fbalazs
 */


#include "dd.h"
#include "CANopen.h"
#include "OD.h"
#include "can.h"
#include "CO_driver_target.h"
#include "tim.h"

/* Private define ------------------------------------------------------------*/

/* default values for CO_CANopenInit() and other can open related things */
#define NMT_CONTROL \
            CO_NMT_STARTUP_TO_OPERATIONAL \
          | CO_NMT_ERR_ON_ERR_REG \
          | CO_ERR_REG_GENERIC_ERR \
          | CO_ERR_REG_COMMUNICATION
#define FIRST_HB_TIME 500
#define SDO_SRV_TIMEOUT_TIME 1000
#define SDO_CLI_TIMEOUT_TIME 1000
#define SDO_CLI_BLOCK false
#define OD_STATUS_BITS NULL


/* DD specific bit masks and values */

#define SW_state_mask_partial 			0x004F 		/* Mask used to get device current state from statusword, w/o bit 5  		*/
#define SW_state_fault					0x0008		/* Device is in Fault state, use width mask_partial    				 		*/
#define SW_state_s_o_d					0x0040		/* s_o_d = switch_on_disabled 										 		*/
#define SW_state_mask_partial_and_HV	0x005F 		/* Mask used to get device current state from statusword, w/o bit 5  		*/
#define SW_state_s_o_d_and_HV			0x0050		/* s_o_d = switch_on_disabled AND High Voltage is present 			 		*/

#define SW_state_mask_full 				0x006F 		/* Mask used to get device current state from statusword, w/  bit 5  		*/
#define SW_State_motor_on				0x0027		/* DD is in oeration enabled state, in code that is called "motor on"		*/
#define SW_state_switched_on			0x0021		/* DD is in "ready to switch on" mode which is callad switched on in code 	*/

#define SW_HV_present_mask 				0x0010 		/* If HighVoltage is present bit 8 is set in statusword */

#define SW_SP_and_POS_mask 				0xF76F 		/* Mask used to get SP and POS relevant data from StatusWord */
#define SW_mvmnt_started 				0x1227 		/* StatusWord MoVeMeNT started */
#define SW_mvmnt_ended					0x1627

#define SW_SP_cleared_mask				0xF36F		/* Mask for determining if SP has been cleared */
#define	SW_SP_cleared					0x0227 		/* StatusWord SetPoint cleared */

#define DD_CW_index 					0x6040
#define	DD_CW_clear_sp					0x2F
#define DD_CW_start_mvmnt				0x3F
#define DD_CW_fault_reset				0x80
#define DD_CW_switch_on 				0x06
#define DD_CW_turn_motor_on 			0x0F

#define DD_rel_pos_index				0x607A

#define DD_BV_index						0x300D
#define DD_BV_subindex					0x06

#define subindex_zero					0x0

#define DD_EMCY_COBID 					0xFE

#define DD_err_wait_time				1000		/* wait time in ms, before DD tries to restart after a problem */

/* Global  variables ---------------------------------------------------------*/
DD_object_t DD_object;

/* Private variables ---------------------------------------------------------*/

/* CANopen */
CO_t *CO = NULL; 				/* CANopen object */
void *CANptr = NULL; 			/* CAN module address */

uint16_t CO_proc_tim_value = 0;		/* get tim10 (16 bit) value to calculate timeDifference between calls for C_process() */
uint16_t CO_periodic_proc_tim_value = 0;  /* get tim10 value for the periodic handler */


/* Private function prototypes -----------------------------------------------*/
void DD_MotorOn_state_handler(void);
uint8_t DD_download_params(void);
CO_SDO_return_t SDO_client_upload(void);
CO_SDO_return_t SDO_client_download_initiate(uint16_t index, uint8_t subindex, size_t sizeIndicated, uint32_t data);
CO_SDO_return_t SDO_client_download(void);
CO_ReturnError_t NMT_reset_DD(void);
void DD_Emergency_callback (const uint16_t ident, const uint16_t errorCode, const uint8_t errorRegister, const uint8_t errorBit, const uint32_t infoCode);



/* -----------------------------------------------  Functions ---------------------------------------------------------------------------------------------------------------- */

/* Initialize CANopenNode and DD state machine */
CO_ReturnError_t DD_init (void){

	if (DD_object.current_state == DD_Not_used)
		return CO_ERROR_ILLEGAL_ARGUMENT;			/* some other channel was already configured for DD, and only one DD per RXMUX is permitted */

	uint8_t pendingNodeId = RXMUX_CANopen_node_ID;
	uint8_t activeNodeId = RXMUX_CANopen_node_ID;
	uint16_t pendingBitRate = 1000;
	CO_ReturnError_t err;

    /* Configure CANopen  */

    /* Allocate memory */
    CO_config_t *config_ptr = NULL;

    CO = CO_new(config_ptr, NULL);
    if (CO == NULL) {
        return 0;
    }

	/* Wait rt_thread. */ /* Comments are from example, not me */
	CO->CANmodule->CANnormal = false;

	/* Enter CAN configuration. */
	CO_CANsetConfigurationMode((void *)&CANptr);
	CO_CANmodule_disable(CO->CANmodule);

	/* initialize CANopen */
	err = CO_CANinit(CO, CANptr, pendingBitRate);
	if (err != CO_ERROR_NO) {
		return err;
	}


	activeNodeId = pendingNodeId;
	uint32_t errInfo = 0;

	err = CO_CANopenInit(CO,                /* CANopen object */
						 NULL,              /* alternate NMT */
						 NULL,              /* alternate em */
						 OD,                /* Object dictionary */
						 OD_STATUS_BITS,    /* Optional OD_statusBits */
						 NMT_CONTROL,       /* CO_NMT_control_t */
						 FIRST_HB_TIME,     /* firstHBTime_ms */
						 SDO_SRV_TIMEOUT_TIME, /* SDOserverTimeoutTime_ms */
						 SDO_CLI_TIMEOUT_TIME, /* SDOclientTimeoutTime_ms */
						 SDO_CLI_BLOCK,     /* SDOclientBlockTransfer */
						 activeNodeId,
						 &errInfo);
	if(err != CO_ERROR_NO && err != CO_ERROR_NODE_ID_UNCONFIGURED_LSS) {
		return err;
	}

	err = CO_CANopenInitPDO(CO, CO->em, OD, activeNodeId, &errInfo);
	if(err != CO_ERROR_NO) {
		return err;
	}

	/* Register custom emergency callback */
	CO_EM_initCallbackRx(CO->em, *DD_Emergency_callback);

	/* start CAN */
	CO_CANsetNormalMode(CO->CANmodule);

	/* get first timer value */
	CO_proc_tim_value = __HAL_TIM_GetCounter(&htim10); /* if needed tim2 (PPM) could be used, but make sure to start timer even if PPM is not used */


	/* DD specific part  -----------------------------------------------  */

	DD_object.current_state = DD_Offline;
	DD_object.state_change_occurred = 0;
	DD_object.p_DD_config = &DD_config;

	DD_object.p_DD_status_word 		= &(OD_RAM.x2008_DD_statusword);
	DD_object.p_DD_actual_current 	= &(OD_RAM.x200A_DD_actual_current);
	DD_object.p_DD_actual_tempr 	= &(OD_RAM.x200B_DD_actual_temperature);
	DD_object.p_DD_actual_pos 		= &(OD_RAM.x2009_DD_actual_position);
	DD_object.p_DD_actual_voltage 	= &(OD_RAM.x200C_DD_actual_voltage);

	DD_object.SDO_status_own = SDO_idle;	/* used only in motor_on state */
	DD_object.wait_for_SW = 0;
	DD_object.timer_value = 0;

	DD_object.last_error = DD_err_none;

	DD_object.new_pos_wanted = POS_idle;

    return CO_ERROR_NO;
}

uint32_t resend_slowdown_counter = 0;

void DD_handler(void)
{
		/*----------------------- first deal with CANopen --------------------------------------- */

		/* get time difference since last function call */
		uint32_t timeDifference_us;
		uint16_t counter_current = __HAL_TIM_GetCounter(&htim10);  /* if needed tim2 (PPM) could be used, but make sure to start timer even if PPM is not used */

		if (counter_current > CO_proc_tim_value)
			timeDifference_us = (uint32_t)(counter_current - CO_proc_tim_value);
		else
			timeDifference_us = (uint32_t)(0xFFFF - CO_proc_tim_value + counter_current + 1);   /* overflow every 65 ms*/

		CO_proc_tim_value = __HAL_TIM_GetCounter(&htim10);

		/* CANopen process */
		CO_process(CO, false, timeDifference_us, NULL); 	/* The return value of this function would only be interesting if an other device could reset the RXMUX. (The DD can't do that) */


		/* ------------------------- DD state machine --------------------------------------- */
		switch (DD_object.current_state)
		{
			case DD_Not_used:
				break;			/* Program should never get to here */

			case DD_Offline:

				/* state transition is handled in CO_driver_rxmux.c */
				break;

			case DD_Not_ready_to_switch_on:

				/*If we just got to this state, and RXMux CANopen is ready send first message*/
				if (DD_object.state_change_occurred && CO->CANmodule->firstCANtxMessage == 0)
				{
					if (NMT_reset_DD() == CO_ERROR_NO){
						DD_object.state_change_occurred = 0;
					}
				}

				/* If DD status word was updated, and is indicating correct state */
				if (DD_check_SW(SW_state_mask_partial_and_HV, SW_state_s_o_d_and_HV)) /*device status bits are set correctly for switch on disabled and High Voltage is present */
				{
					/* change state */
					DD_object.current_state = DD_Switch_on_disabled;  /*  <-------------------- STATE TRANSITION HERE ----------    */
					DD_object.state_change_occurred = 1;
				}
				break;

			case DD_Switch_on_disabled:

				/* If fault occured, transition to fault state */
				if(DD_check_SW(SW_state_mask_partial, SW_state_fault))
				{
					DD_object.current_state = DD_Fault;    /*  <-------------------- STATE TRANSITION HERE ----------    */
					DD_object.state_change_occurred = 1;
					DD_object.timer_value = HAL_GetTick();
				}

				/* Call this function periodically to set all DD parameters. If it returns 1 all parameters are set */
				if (DD_download_params() != 1)
					break;  /* exit switch, so that we don't yet go to next state */

				/* if all parameters were downloaded, send command to transition to next state */
				if (DD_object.state_change_occurred) /*If we just got to this state, initiate SDO download */
				{
					SDO_client_download_initiate(DD_CW_index, 0x0, 0, DD_CW_switch_on);
					DD_object.state_change_occurred = 0;
				}
				else
				{
					CO_SDO_return_t retval;
					retval = SDO_client_download();
					if (retval < CO_SDO_RT_ok_communicationEnd)
						DD_object.state_change_occurred = 1; /* resend download */
					else
						if (DD_check_SW(SW_state_mask_full, SW_state_switched_on))
						{
							DD_object.current_state = DD_Switched_on;    /*  <-------------------- STATE TRANSITION HERE ----------    */
							DD_object.state_change_occurred = 1;
						}
						else if(retval == CO_SDO_RT_ok_communicationEnd)
						{
							resend_slowdown_counter++;
							if (resend_slowdown_counter % 50 == 0)
								DD_object.state_change_occurred = 1;  //resend temp
						}
				}
				break;

			case DD_Switched_on:						/* Official name is "ready to switch on" */

				/* Fault occured, transition to fault state */
				if(DD_check_SW(SW_state_mask_partial, SW_state_fault))
				{
					DD_object.current_state = DD_Fault;     /*  <-------------------- STATE TRANSITION HERE ----------    */
					DD_object.state_change_occurred = 1;
					DD_object.timer_value = HAL_GetTick();
				}

				/* if we just got to this state, send command to transition to next state */
				if (DD_object.state_change_occurred)
				{
					/*If we just got to this state, initiate SDO download */
					SDO_client_download_initiate(DD_CW_index, subindex_zero, 0, DD_CW_turn_motor_on);
					DD_object.state_change_occurred = 0;
				}
				else
				{
					if (SDO_client_download() < CO_SDO_RT_ok_communicationEnd)
						DD_object.state_change_occurred = 1; /* resend download */
					else
						if (DD_check_SW(SW_state_mask_full,SW_State_motor_on))
						{
							DD_object.current_state = DD_Motor_on;    /*  <-------------------- STATE TRANSITION HERE ----------    */
							//DD_object.state_change_occured = 1;
						}
				}
				break;

			case DD_Motor_on: 							/* Official name is "operation enabled" */

				DD_MotorOn_state_handler();
				break;

			case DD_Fault:

				/* wait a bit before doing anything so transient states can play out */
				if (HAL_GetTick() - DD_object.timer_value <= DD_err_wait_time)
				{
					break;
				}


				/* if error is manageable try to go back to normal operation */
				if(DD_object.last_error > DD_err_none && DD_object.last_error < DD_err_unknown)
				{
					/* if we succeeded, cahnge state */
					if (DD_check_SW(SW_state_mask_partial, SW_state_s_o_d))
					{
						DD_object.current_state = DD_Switch_on_disabled;    /*  <-------------------- STATE TRANSITION HERE ----------    */
						DD_object.state_change_occurred = 1;

						/* reset defults before going back to normal operation*/

						DD_object.last_error = DD_err_none;
						DD_object.wait_for_SW = 0;
						DD_object.timer_value = 0;

					}

					if (/*DD_object.state_change_occured &&*/ CO->SDOclient[0].state == CO_SDO_ST_IDLE )
					{
						SDO_client_download_initiate(DD_CW_index, subindex_zero, 0, DD_CW_fault_reset);
						DD_object.state_change_occurred = 0;
					}
					else
						if (SDO_client_download() < CO_SDO_RT_ok_communicationEnd)
						{
							//DD_object.state_change_occured = 1; /* resend */
						}
				}

				break;

		}

		/* ------------------------------------  DD state machine end   ------------------------------------------------ */


		if (CAN3_Flag_TxComplete || CAN3_Flag_RxPending)
		{
			//service interrupt
			CO_CANinterrupt(CO->CANmodule);
		}

}


/* this is called from set_indicators(), because it needs to be called every ms CO_SYNC_init */
void DD_periodic_handler(void)
{
	CO_LOCK_OD(CO->CANmodule);
	if (!CO->nodeIdUnconfigured && CO->CANmodule->CANnormal)
	{
		bool_t syncWas = false;
		/* difference since last function call */
		uint32_t timeDifference_us = 1000; /* this way it's much more precise (compared to if we actually measure the time difference) */

		#if (CO_CONFIG_SYNC) & CO_CONFIG_SYNC_ENABLE
		syncWas = CO_process_SYNC(CO, timeDifference_us, NULL);
		#endif
		#if (CO_CONFIG_PDO) & CO_CONFIG_RPDO_ENABLE
		CO_process_RPDO(CO, syncWas, timeDifference_us, NULL);
		#endif
		#if (CO_CONFIG_PDO) & CO_CONFIG_TPDO_ENABLE
		CO_process_TPDO(CO, syncWas, timeDifference_us, NULL);
		#endif

		/* Further I/O or nonblocking application code may go here. */
	}
	CO_UNLOCK_OD(CO->CANmodule);
}

uint8_t DD_download_params(void)
{
	/* if all parameters are set return 1, else set the next parameter */
	if(DD_object.p_DD_config->counter == DD_num_of_init_params)
		return 1;
	else
	{
		if( CO->SDOclient[0].state == CO_SDO_ST_IDLE )
		{
			uint8_t counter = DD_object.p_DD_config->counter;
			uint16_t index = DD_object.p_DD_config->param_set[counter].index;
			uint8_t subindex = DD_object.p_DD_config->param_set[counter].subindex;
			uint32_t data = DD_object.p_DD_config->param_set[counter].value;

			if (index == 0) /*invalid parameter, dont try to set it, skip to the next one */
			{
				DD_object.p_DD_config->counter++;
				return 0;
			}

			SDO_client_download_initiate(index, subindex, 0, data);
		}
		else
			if(SDO_client_download() == CO_SDO_RT_ok_communicationEnd)
				 DD_object.p_DD_config->counter++;

		return 0;
	}
}

void DD_MotorOn_state_handler(void)
{
	/* Fault occured, transition to fault state */
	if(DD_check_SW(SW_state_mask_partial, SW_state_fault))
	{
		DD_object.current_state = DD_Fault;   		 /*  <-------------------- STATE TRANSITION HERE ----------    */
		DD_object.state_change_occurred = 1;
		DD_object.timer_value = HAL_GetTick();
	}

	/* If we sent out a CW that will generate SW RPDO, we wait for it here */
	if (DD_object.wait_for_SW)
	{
		/* IF status_word has been updated since last call, update the variables keeping track of different states */
		if ( DD_check_SW(SW_SP_cleared_mask, SW_SP_cleared) && (DD_object.new_pos_wanted == POS_requested))
		{
			DD_object.new_pos_wanted = POS_prev_sp_cleared;
			DD_object.wait_for_SW = 0;
		}

		if ( DD_check_SW(SW_SP_and_POS_mask, /*SW_mvmnt_ended*/ SW_mvmnt_started) && DD_object.new_pos_wanted == POS_sent) /* only allow transition from previous state */
		{
			DD_object.new_pos_wanted = POS_idle;
			DD_object.wait_for_SW = 0;
		}

		if ( DD_check_SW(SW_state_mask_full, SW_state_switched_on)) /* only allow transition from previous state */
		{
			DD_object.current_state = DD_Switched_on;				 /*  <-------------------- STATE TRANSITION HERE ----------    */
			DD_object.state_change_occurred = 0;
			return;
		}
	}

	/* If not waiting for SW, and SDO client is free initiate next SDO down- or upload */
	if ((CO->SDOclient[0].state == CO_SDO_ST_IDLE) && (!DD_object.wait_for_SW))
	{
		/* If necessary initiate new SDO-s */
		if (DD_object.new_pos_wanted == POS_requested )
		{
			SDO_client_download_initiate(DD_CW_index, subindex_zero, 0, DD_CW_clear_sp);
			DD_object.SDO_status_own = SDO_download_initiated;      /* just used to keep track if upload or download function should be called */
		}

		if (DD_object.new_pos_wanted == POS_prev_sp_cleared )
		{
			SDO_client_download_initiate(DD_rel_pos_index, 0, 0, DD_object.new_relative_pos);
			DD_object.SDO_status_own = SDO_download_initiated;
		}

		if (DD_object.new_pos_wanted == POS_sent )
		{
			SDO_client_download_initiate(DD_CW_index, subindex_zero, 0, DD_CW_start_mvmnt );
			//delay?
			DD_object.SDO_status_own = SDO_download_initiated;
		}

		if (DD_object.voltage_wanted && DD_object.new_pos_wanted == POS_sent)
		{
			CO_SDOclientUploadInitiate(&CO->SDOclient[0], DD_BV_index, DD_BV_subindex, SDO_CLI_TIMEOUT_TIME, 0 );
			DD_object.SDO_status_own = SDO_upload_initiated;
			DD_object.voltage_wanted = 0;
		}

		/* if requested initiate state transition */
		if (DD_object.state_change_occurred)
		{
			SDO_client_download_initiate(DD_CW_index, subindex_zero, 0, DD_CW_switch_on);
			DD_object.SDO_status_own = SDO_download_initiated;
		}
	}


	/* Actually send SDOs and wait for response */
	if (DD_object.SDO_status_own == SDO_download_initiated ) /* download initiated  */
		if (SDO_client_download() <= CO_SDO_RT_ok_communicationEnd)  /* communication ended or aborted */
		{
			DD_object.SDO_status_own = SDO_idle;
			DD_object.wait_for_SW = 1;
			if (DD_object.new_pos_wanted == POS_prev_sp_cleared) /* if we just sent the new position data */
			{
				DD_object.new_pos_wanted = POS_sent;
				DD_object.wait_for_SW = 0;
			}
		}
	if (DD_object.SDO_status_own == SDO_upload_initiated ) /* upload initiated  */
		if (SDO_client_upload() <= CO_SDO_RT_ok_communicationEnd)  /* communication ended or aborted */
				DD_object.SDO_status_own = SDO_idle;
}


CO_SDO_return_t SDO_client_upload(void)
{
 	CO_SDO_abortCode_t SDOabortCode;

 	size_t	sizeIndicated;
 	size_t	sizeTransferred = 0;

 	uint8_t answer[4]; 		/* we only use expedited transfer so max 4 bytes */

	CO_SDO_return_t retval_sdo;
	retval_sdo = CO_SDOclientUpload(&CO->SDOclient[0], 500, 0, &SDOabortCode, &sizeIndicated, &sizeTransferred, NULL);
	if (retval_sdo == CO_SDO_RT_ok_communicationEnd )
	{
		CO_SDOclientUploadBufRead(&CO->SDOclient[0], answer, sizeTransferred);

		/* if we got Voltage data */
		if(CO->SDOclient[0].index == DD_BV_index && CO->SDOclient[0].subIndex == DD_BV_subindex)
		{

			/*convert bytestirng to float32_t */
			*((uint8_t*) DD_object.p_DD_actual_voltage + 0) = answer[0];
			*((uint8_t*) DD_object.p_DD_actual_voltage + 1) = answer[1];
			*((uint8_t*) DD_object.p_DD_actual_voltage + 2) = answer[2];
			*((uint8_t*) DD_object.p_DD_actual_voltage + 3) = answer[3];

		}

	}

	return retval_sdo;
}

CO_SDO_return_t SDO_client_download_initiate(uint16_t index, uint8_t subindex, size_t sizeIndicated, uint32_t data)
{
	CO_SDO_return_t retval_sdo;

	if (CO_SDOclientDownloadInitiate(&CO->SDOclient[0], index, subindex, sizeIndicated, SDO_CLI_TIMEOUT_TIME, 0 ) != CO_SDO_RT_ok_communicationEnd)
		return CO_SDO_RT_wrongArguments;

	const uint8_t data_buffer[] ={(data >> 0) & 0xFF, (data >> 8) & 0xFF, (data >> 16) & 0xFF, (data >> 24) & 0xFF } ;

	retval_sdo = CO_SDOclientDownloadBufWrite(&CO->SDOclient[0], data_buffer, 4);

	return retval_sdo;
}

CO_SDO_return_t SDO_client_download(void)
{
	/* usfeful fo r debug */
	CO_SDO_abortCode_t SDOabortCode;
	size_t sizeTransferred;

	return CO_SDOclientDownload (&CO->SDOclient[0], 500, 0, 0, &SDOabortCode, &sizeTransferred, NULL );
}

FORCE_INLINE CO_ReturnError_t NMT_reset_DD(void)
{
	return CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_OPERATIONAL, DD_object.CO_node_ID);
}

void DD_Emergency_callback (const uint16_t ident,
							const uint16_t errorCode,
		                    const uint8_t errorRegister,
		                    const uint8_t errorBit,
		                    const uint32_t infoCode)
{
	// TODO (DD) store error codes in custom entries in OD
	if (ident == DD_EMCY_COBID)
	{
		if (errorCode == 0x3120 && errorRegister == 0x05)
		{
			/* Error: "Under-voltage: power supply is shut down or it has too high an output impedance." */
			DD_object.last_error =  DD_err_low_voltage;

		}
		else if (errorCode == 0xFF10 && errorRegister == 0x81) /*Error: failed to start motor */
		{
			DD_object.last_error =  DD_err_failed_to_start_motor;
		}
		else if (0 /* next error we want to handle here */)
		{

		}
		else /* unknown error */
		{
			DD_object.last_error =  DD_err_unknown;
		}
	}

	return;
}
