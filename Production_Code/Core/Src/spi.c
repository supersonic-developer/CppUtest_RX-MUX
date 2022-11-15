/**
  ******************************************************************************
  * File Name          : SPI.c
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "error_detection.h"
#include "app.h"
#include "rc_superv_logic.h"
#include "adc.h"
#include <string.h>
//SPI flags
uint8_t SPI1_Flag_TxRxReady = 0;
uint8_t SPI1_Flag_ProcessReady=0; //When PWM signal is created this flag is set
uint8_t SPI1_First_Message=1;
uint8_t SPI1_Flag_BufferTarget=0;

//Buffers
SPI_FH_MSG fromFH_Buff0;
SPI_FH_MSG fromFH_Buff1;
SPI_FH_MSG toFH_Buff;
SPI_FH_MSG process_Buff;
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */
  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA4     ------> SPI1_NSS
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA2_Stream2;
    hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmarx,hdma_spi1_rx);

    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA2_Stream3;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PA4     ------> SPI1_NSS
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmarx);
    HAL_DMA_DeInit(spiHandle->hdmatx);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void CopyData_IntoTransferBuffer()
{
	// Copy data into transfer buffer
	for (int i=0;i<sizeof(toFH_Buff);i++)
		toFH_Buff.rawU8[i]=process_Buff.rawU8[i];

	//copy PWM values (process_Buff contains the signal from the AP)
	copy_PWM_To_SPI_Struct();

	// Calculate checksum
	toFH_Buff.checksum=0;
	for (int cnt=4;cnt<sizeof(toFH_Buff)/2-1;cnt++)
		toFH_Buff.checksum ^=toFH_Buff.rawU16[cnt];
}

void CopyData_IntoProcessBuffer(SPI_FH_MSG *currentBuffer)
{
	//Calculate checksum
	uint16_t inChecksum=0;
	for(int cnt=4;cnt<sizeof(toFH_Buff)/2-1;cnt++)
		inChecksum ^= currentBuffer->rawU16[cnt];

	// Delete error flags from the previous communication cycle
	DeleteErrorFlag();

	// Store error
	if(inChecksum!=currentBuffer->checksum)
		errors.spi|=WRONG_FH_CHECKSUM;

	// Copy data into process buffer
	for (int i=0;i<sizeof(toFH_Buff.servoValues.PWM_data);i++)
	{
		process_Buff.servoValues.PWM_data.rawPWMData[i]=currentBuffer->servoValues.PWM_data.rawPWMData[i];
	}
}

/*
 * @brief Handle full duplex SPI communication
 * @note In autopilot mode, the reference PPM signals in the process_Buff
 * @retval HAL status
 */
HAL_StatusTypeDef SPI1_TransmitReceive()
{
	HAL_StatusTypeDef SPI_Status=HAL_OK;

	//First message is dummy, do not save it to process buffer
	if(SPI1_First_Message)
	{
		SPI1_First_Message=0;
		SPI_Status=HAL_SPI_TransmitReceive_DMA(&hspi1,toFH_Buff.rawU8,fromFH_Buff0.rawU8,sizeof(toFH_Buff));
	}

	// Previous communication cycle ended, save data and get ready for next cycle
	if(SPI1_Flag_TxRxReady)
	{
		process_Buff.status1&=0xFFFD;
		// process_Buff.status2++; // Possible solution to display RX-MUX activity in EDL (not tested, just an idea)
		SPI1_Flag_TxRxReady=0;
		CopyData_IntoTransferBuffer();
		if(SPI1_Flag_BufferTarget==0)
		{
			SPI_Status=HAL_SPI_TransmitReceive_DMA(&hspi1,toFH_Buff.rawU8,fromFH_Buff1.rawU8,sizeof(toFH_Buff));
			SPI1_Flag_BufferTarget=1;
			CopyData_IntoProcessBuffer(&fromFH_Buff0);
		}
		else if(SPI1_Flag_BufferTarget==1)
		{
			SPI_Status=HAL_SPI_TransmitReceive_DMA(&hspi1,toFH_Buff.rawU8,fromFH_Buff0.rawU8,sizeof(toFH_Buff));
			SPI1_Flag_BufferTarget=0;
			CopyData_IntoProcessBuffer(&fromFH_Buff1);
		}

		/* Start battery measurement for the next cycle */
		HAL_ADC_Start_DMA(&hadc1, adc_buff, adc_buff_length);
	}

	return SPI_Status;
}

void SPI1_Reset_Periphery()
{
	HAL_SPI_MspDeInit(&hspi1);
	HAL_SPI_MspInit(&hspi1);
	MX_SPI1_Init();
}

//SPI callback interrupt handler
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == hspi1.Instance){
		SPI1_Flag_TxRxReady = 1; /* this is for the spi code to use*/

		AP_src_struct.State = src_active; /* these are for error detection */
		AP_src_struct.timestamp_last_valid_frame = (uint16_t)__HAL_TIM_GET_COUNTER(&htim6);
		AP_src_struct.new_data_FLAG = 1;
	}
}


void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == hspi1.Instance){
		errors.spi |= hspi->ErrorCode;
		process_Buff.status1|=0x2;
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
