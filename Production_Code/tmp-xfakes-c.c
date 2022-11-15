/*
    Fakes generated from: tmp-build-errors.txt

    Generated file to help to quickly stub C-linkage unresolved external references

    * When EXPLODING_FAKE_FOR is executed, a message is printed and the test run is existed
    * You could customize EXPLODING_FAKE_FOR to only fail the test
    * Add this file to your test build.
    * Do not include the header files for the referenced functions. The C-linker does not care.

    Note: a EXPLODING_FAKE_FOR() is generated for global variables too.
    * They will explode upon write :-)
    * You might want to resolve these a different way.

*/

#include <stdio.h>
#include <stdlib.h>


#define MESSAGE printf("%s was running\n", __func__)
#define FAKE_FOR(f) int f(void); int f(void) { return 0; }
#define FAKE_FOR_TICK(f) int f(void); int f(void) { return tick+=500; }



unsigned short tick = 0;
FAKE_FOR(CO_CANinit)
FAKE_FOR(CO_CANinterrupt)
FAKE_FOR(CO_CANmodule_disable)
FAKE_FOR(CO_CANopenInit)
FAKE_FOR(CO_CANopenInitPDO)
FAKE_FOR(CO_CANsetConfigurationMode)
FAKE_FOR(CO_CANsetNormalMode)
FAKE_FOR(CO_EM_initCallbackRx)
FAKE_FOR(CO_NMT_sendCommand)
FAKE_FOR(CO_SDOclientDownload)
FAKE_FOR(CO_SDOclientDownloadBufWrite)
FAKE_FOR(CO_SDOclientDownloadInitiate)
FAKE_FOR(CO_SDOclientUpload)
FAKE_FOR(CO_SDOclientUploadBufRead)
FAKE_FOR(CO_SDOclientUploadInitiate)
FAKE_FOR(CO_new)
FAKE_FOR(CO_process)
FAKE_FOR(CO_process_RPDO)
FAKE_FOR(CO_process_SYNC)
FAKE_FOR(EE_Init)
FAKE_FOR(EE_ReadVariable)
FAKE_FOR(EE_WriteVariable)
FAKE_FOR(HAL_ADC_ConfigChannel)
FAKE_FOR(HAL_ADC_Init)
FAKE_FOR(HAL_ADC_Start_DMA)
FAKE_FOR(HAL_ADC_Stop_DMA)
FAKE_FOR(HAL_CAN_ActivateNotification)
FAKE_FOR(HAL_CAN_AddTxMessage)
FAKE_FOR(HAL_CAN_ConfigFilter)
FAKE_FOR(HAL_CAN_DeactivateNotification)
FAKE_FOR(HAL_CAN_GetRxFifoFillLevel)
FAKE_FOR(HAL_CAN_GetRxMessage)
FAKE_FOR(HAL_CAN_GetTxMailboxesFreeLevel)
FAKE_FOR(HAL_CAN_Init)
FAKE_FOR(HAL_CAN_Start)
FAKE_FOR(HAL_DMA_DeInit)
FAKE_FOR(HAL_DMA_Init)
FAKE_FOR(HAL_Delay)
FAKE_FOR(HAL_FLASH_Unlock)
FAKE_FOR(HAL_GPIO_DeInit)
FAKE_FOR(HAL_GPIO_Init)
FAKE_FOR(HAL_GPIO_ReadPin)
FAKE_FOR(HAL_GPIO_WritePin)
FAKE_FOR_TICK(HAL_GetTick)
FAKE_FOR(HAL_HalfDuplex_Init)
FAKE_FOR(HAL_I2C_Init)
FAKE_FOR(HAL_I2C_Slave_Receive_DMA)
FAKE_FOR(HAL_I2C_Slave_Transmit_DMA)
FAKE_FOR(HAL_I2C_MspDeInit)
FAKE_FOR(HAL_I2C_MspInit)
FAKE_FOR(HAL_IWDG_Init)
FAKE_FOR(HAL_IWDG_Refresh)
FAKE_FOR(HAL_Init)
FAKE_FOR(HAL_NVIC_DisableIRQ)
FAKE_FOR(HAL_NVIC_EnableIRQ)
FAKE_FOR(HAL_NVIC_SetPriority)
FAKE_FOR(HAL_RCC_ClockConfig)
FAKE_FOR(HAL_RCC_OscConfig)
FAKE_FOR(HAL_SPI_Init)
FAKE_FOR(HAL_SPI_TransmitReceive_DMA)
FAKE_FOR(HAL_TIMEx_ConfigBreakDeadTime)
FAKE_FOR(HAL_TIMEx_MasterConfigSynchronization)
FAKE_FOR(HAL_TIM_Base_Init)
FAKE_FOR(HAL_TIM_Base_Start)
FAKE_FOR(HAL_TIM_Base_Start_IT)
FAKE_FOR(HAL_TIM_Base_Stop_IT)
FAKE_FOR(HAL_TIM_ConfigClockSource)
FAKE_FOR(HAL_TIM_IC_ConfigChannel)
FAKE_FOR(HAL_TIM_IC_Init)
FAKE_FOR(HAL_TIM_IC_Start_IT)
FAKE_FOR(HAL_TIM_PWM_ConfigChannel)
FAKE_FOR(HAL_TIM_PWM_GetState)
FAKE_FOR(HAL_TIM_PWM_Init)
FAKE_FOR(HAL_TIM_PWM_Start)
FAKE_FOR(HAL_TIM_PWM_Stop)
FAKE_FOR(HAL_TIM_ReadCapturedValue)
FAKE_FOR(HAL_UART_AbortReceive)
FAKE_FOR(HAL_UART_Init)
FAKE_FOR(HAL_UART_Receive_DMA)
FAKE_FOR(HAL_UART_Transmit_DMA)
FAKE_FOR(OD)
FAKE_FOR(OD_RAM)
FAKE_FOR(HAL_CAN_MspInit)
FAKE_FOR(HAL_CAN_MspDeInit)