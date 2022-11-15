/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "indicators.h"
#include "can_servo.h"
#include "fifo.h"

uint8_t CAN1_Flag_RxPending = 0;
uint8_t CAN2_Flag_RxPending = 0;
uint8_t CAN3_Flag_RxPending = 0;

//uint8_t CAN1_Flag_TxComplete = 0;
//uint8_t CAN2_Flag_TxComplete = 0;
uint8_t CAN3_Flag_TxComplete = 0;

// CAN_FilterTypeDef sFilterConfig; //declare CAN filter structure  //araktam lokalba

FIFO_CAN_S_MSG CAN1_tx_msg_fifo; 	/*fifo to store CAN servo msgs */
FIFO_CAN_S_MSG CAN2_tx_msg_fifo; 	/*fifo to store CAN servo msgs */

uint32_t CAN1_Error = 0;
uint32_t CAN2_Error = 0;
uint32_t CAN3_Error = 0;


/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;
CAN_HandleTypeDef hcan3;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 5;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = ENABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }

}
/* CAN3 init function */
void MX_CAN3_Init(void)
{

  hcan3.Instance = CAN3;
  hcan3.Init.Prescaler = 5;
  hcan3.Init.Mode = CAN_MODE_NORMAL;
  hcan3.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan3.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan3.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan3.Init.TimeTriggeredMode = DISABLE;
  hcan3.Init.AutoBusOff = DISABLE;
  hcan3.Init.AutoWakeUp = DISABLE;
  hcan3.Init.AutoRetransmission = ENABLE;
  hcan3.Init.ReceiveFifoLocked = DISABLE;
  hcan3.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan3) != HAL_OK)
  {
    Error_Handler();
  }

}


/* USER CODE BEGIN 1 */

/*
 * CAN1 setup is here. CAN1 is used for CAN servos
 * CAN2 not yet implemented. I intend them for CAN servos if needed
 * CAN3 Used for DD with CANopen. Init and start is implemented in CO_driver.c
 */
HAL_StatusTypeDef CAN1_Setup() {

	CAN_FilterTypeDef sFilterConfig;

	/* Configure CAN filter, to allow all messages
	 *
	 */
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) { //configure CAN filter
		return HAL_ERROR;
	}

	//Start the CAN peripheral
	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
		return HAL_ERROR;
	}

	//Activate CAN notification
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		return HAL_ERROR;
	}

	//Initialize msg storage fifo, needed to queue more than 3 msgs
	CAN1_tx_msg_fifo.in = 0;
	CAN1_tx_msg_fifo.out = 0;
	CAN1_tx_msg_fifo.mask = MAX_FIFO_SIZE_CAN_S_MSG - 1;

	return HAL_OK;
}

HAL_StatusTypeDef CAN2_Setup() {

	CAN_FilterTypeDef sFilterConfig;

	/* Configure CAN filter, to allow all messages
	 *
	 */
	sFilterConfig.FilterBank = 27;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if(HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK) { //configure CAN filter
		return HAL_ERROR;
	}

	//Start the CAN peripheral
	if (HAL_CAN_Start(&hcan2) != HAL_OK)
	{
		return HAL_ERROR;
	}

	//Activate CAN notification
	if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		return HAL_ERROR;
	}

	//Initialize msg storage fifo, needed to queue more than 3 msgs
	CAN2_tx_msg_fifo.in = 0;
	CAN2_tx_msg_fifo.out = 0;
	CAN2_tx_msg_fifo.mask = MAX_FIFO_SIZE_CAN_S_MSG - 1;

	return HAL_OK;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == hcan1.Instance)
	{
		CAN1_Flag_RxPending = 1;
		HAL_CAN_DeactivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	}
	else if(hcan->Instance == hcan2.Instance)
	{
		CAN2_Flag_RxPending = 1;
		HAL_CAN_DeactivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	}
	else if(hcan->Instance == hcan3.Instance)
	{
		CAN3_Flag_RxPending = 1;
		HAL_CAN_DeactivateNotification(&hcan3, CAN_IT_RX_FIFO0_MSG_PENDING);
	}


}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == hcan1.Instance)
	{

	}
	/*---------------------
	else if(hcan->Instance == hcan2->Instance)
	{

	}
	---------------------------------*/
	else if(hcan->Instance == hcan3.Instance)
	{
		CAN3_Flag_TxComplete = 1;
	}
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == hcan1.Instance)
	{

	}
	/*---------------------
	else if(hcan->Instance == hcan2->Instance)
	{

	}
	---------------------------------*/
	else if(hcan->Instance == hcan3.Instance)
	{
		CAN3_Flag_TxComplete = 1;
	}
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == hcan1.Instance)
	{

	}
	/*---------------------
	else if(hcan->Instance == hcan2->Instance)
	{

	}
	---------------------------------*/
	else if(hcan->Instance == hcan3.Instance)
	{
		CAN3_Flag_TxComplete = 1;
	}
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
