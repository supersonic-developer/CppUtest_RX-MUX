/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "SPI_Comm_MSG_Struct.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN Private defines */
 extern SPI_HandleTypeDef hspi1;

//Flags
extern uint8_t SPI1_Flag_ProcessReady;
extern uint8_t SPI1_Flag_BufferTarget;


//Buffers
extern SPI_FH_MSG toFH_Buff;            //itt kiegeszitettem extern-re
extern SPI_FH_MSG process_Buff;          //itt kiegeszitettem extern-re
/* USER CODE END Private defines */

void MX_SPI1_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef SPI1_TransmitReceive();
void CopyData_IntoTransferBuffer();
void CopyData_IntoProcessBuffer(SPI_FH_MSG *currentBuffer);
void SPI1_Reset_Periphery();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
