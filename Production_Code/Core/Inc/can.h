/**
  ******************************************************************************
  * File Name          : CAN.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __can_H
#define __can_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#include "fifo.h"

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern CAN_HandleTypeDef hcan3;

/* USER CODE BEGIN Private defines */


extern CAN_HandleTypeDef hcan1;  			/*CAN periphery used for communication with servos */

extern uint8_t CAN1_Flag_RxPending;			/*flag for indicating incoming msg */
extern uint8_t CAN2_Flag_RxPending;			/*flag for indicating incoming msg */
extern uint8_t CAN3_Flag_RxPending;			/*flag for indicating incoming msg */


//extern uint8_t CAN1_Flag_TxComplete;
//extern uint8_t CAN2_Flag_TxComplete;
extern uint8_t CAN3_Flag_TxComplete;

extern FIFO_CAN_S_MSG CAN1_tx_msg_fifo;		/* fifo to queue up outgoing messages */
extern FIFO_CAN_S_MSG CAN2_tx_msg_fifo;		/* fifo to queue up outgoing messages */



HAL_StatusTypeDef CAN1_Setup();
HAL_StatusTypeDef CAN2_Setup();

/* USER CODE END Private defines */

void MX_CAN1_Init(void);
void MX_CAN2_Init(void);
void MX_CAN3_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
