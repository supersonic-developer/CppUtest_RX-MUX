#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "app.h"
#include "stm32f413xx.h"
#include "usart.h"
#include "exbus.h"
}

void Init_Registers();
void Free_Registers();

TEST_GROUP(App)
{
    void setup()
    {
        Init_Registers();
    }

    void teardown()
    {
        Free_Registers();
        mock("exbus").checkExpectations();
        mock().clear();
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

TEST(App, EXBus_Init_Called_test)
{
    mock("exbus")
        .expectOneCall("EXBus_Init");

    APP_Init();
}

TEST(App, EXBus_Handler_Called_test)
{
    mock("exbus")
        .expectOneCall("EX_BUS_Handler")
        .withParameter("RC_ID", 1);
    mock("exbus")
        .expectOneCall("EX_BUS_Handler")
        .withParameter("RC_ID", 2);

    APP_Go();
}

