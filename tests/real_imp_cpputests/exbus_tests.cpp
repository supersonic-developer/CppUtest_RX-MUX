#include "CppUTest/TestHarness.h"

extern "C"
{
#include "exbus.h"
#include "usart.h"
#include "rc_superv_logic.h"
#include "stm32f413xx.h"
}

void Init_Registers();
void Free_Registers();

TEST_GROUP(EXBus)
{
    void setup()
    {
        Init_Registers();
    }

    void teardown()
    {
        Free_Registers();
    }
};

RCC_TypeDef* RCC;
DBGMCU_TypeDef* DBGMCU;

void Init_Registers()
{
    RCC = (RCC_TypeDef*)malloc(sizeof(RCC_TypeDef));
    DBGMCU = (DBGMCU_TypeDef*)malloc(sizeof(DBGMCU_TypeDef));
}

void Free_Registers()
{
    free(RCC);
    free(DBGMCU);
}


TEST(EXBus, EXBus_Init_test)
{
    EXBus_Init();
    LONGS_EQUAL(Wait_Header, RC1_EXBus_struct.commState);
    POINTERS_EQUAL(&RC1_EXBusRxBuffer1, RC1_EXBus_struct.usedBuffer);
    POINTERS_EQUAL(&RC1_EXBusRxBuffer2, RC1_EXBus_struct.validBuffer);
    POINTERS_EQUAL(&RC1_EXBus_Flag_NewChDataReceived, RC1_EXBus_struct.NewChDataReceived);
    POINTERS_EQUAL(&RC1_EXBus_received_ppm_values[0], RC1_EXBus_struct.Received_PPM_Values);
    LONGS_EQUAL(1, RC1_EXBus_struct.UART_Flag_TxReady);
    POINTERS_EQUAL(&huart4, RC1_EXBus_struct.huart);
    POINTERS_EQUAL(&EXBus_RC1_src_struct, RC1_EXBus_struct.sourceOfControl);
}

TEST(EXBus, Select_RC_test)
{
    POINTERS_EQUAL(&RC1_EXBus_struct, Select_RC(1));
    POINTERS_EQUAL(&RC2_EXBus_struct, Select_RC(2));
    POINTERS_EQUAL(nullptr, Select_RC(3));
}