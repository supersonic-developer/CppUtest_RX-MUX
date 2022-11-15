#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "exbus.h"
#include "stm32f413xx.h"
}

EX_Bus_Comm_Struct RC1_EXBus_struct;
EX_Bus_Comm_Struct RC2_EXBus_struct;
uint8_t RC1_EXBus_Flag_NewChDataReceived = 0;
uint16_t RC1_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];
uint8_t RC2_EXBus_Flag_NewChDataReceived = 0;
uint16_t RC2_EXBus_received_ppm_values[EXBUS_NUM_OF_CHANNELS];

void EX_BUS_Handler(uint8_t RC_ID)
{
    mock("exbus").
        actualCall("EX_BUS_Handler").
        withParameter("RC_ID", RC_ID);
}

void EXBus_Init()
{
    mock("exbus").
        actualCall("EXBus_Init");
}

void EXBus_RxCallback_Handler(EX_Bus_Comm_Struct* currentRC)
{
    mock("exbus").
        actualCall("EXBus_RxCallback_Handler").
        withParameter("currentRC", currentRC);
}