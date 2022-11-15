/*
 * ecu_uart.h
 *
 *  Created on: Jan 19, 2022
 *      Author: novoz
 *  Description: contains all the methods for handling ECU UART communication
 */

#ifndef INC_ECU_UART_H_
#define INC_ECU_UART_H_



#endif /* INC_ECU_UART_H_ */

// ************************ Defines ************************ //
#define ECUAddress 1
#define ENG_DATA_OFFSET 8
#define RPM_MIN	36000
#define RPM_MAX	106000
#define ENGINE_THRESHOLD 7400

// ******************* Defines ************************ //
typedef enum DeviceStateType
{
	TurnedOff,
	TurningOff,
	TurningOn,
	TurnedOn,
}DeviceState;

typedef enum EcuAnswerType
{
	WSM,
	TCO,
	RAC,
	WRP
}EcuAnswer;

typedef enum TurbineStateType
{
	OFF,
	WaitforRPM,
	Ignite,
	Accelerate,
	Stabilise,
	LearnHI,
	LearnLO,
	NotInterpreted,
	SlowDown,
	Manual,
	AutoOff,
	Run,
	AccelerationDelay,
	SpeedReg,
	TwoShaftRegulate,
	PreHeat1,
	PreHeat2,
	MainFStrt,
	BurnerOff,
	KerosFullOn
}TurbineState;

typedef struct EcuHsAnswerType
{
	union{
		struct{
			int turbineRPM;
			int turbineEGT;
			float pumpVoltage;
			int turbineState;
			float throttlePos;
		};
		uint8_t rawECUData[20];
	};

}EcuHsAnswer;

extern uint8_t UART1_Flag_TxReady;
extern uint8_t UART1_Flag_RxReady;
extern uint8_t UART1_Flag_Timer;
extern HAL_StatusTypeDef UART1_Status;
extern uint8_t rxBuffer[50];
extern uint8_t receivedByte;
extern uint16_t numBytesReceived;
extern uint8_t validatedEngineState;
extern uint8_t engineSwitchWindow;

// ************************ Prototypes ************************* //
// Command functions
HAL_StatusTypeDef SendWSMPacket(uint8_t SerialCommandOn);
HAL_StatusTypeDef SendTCOPacket(uint8_t engineOn);
HAL_StatusTypeDef SendRACPacket();
HAL_StatusTypeDef SendWRPPacket(uint32_t RPM);

// Char array handler functions
uint8_t CompareBuffers(const char* buffer1, const char* buffer2);
void ConvertCharToByte(int length);
void ConvertByteToChar();
float ConvertDigitsToRealNum(char* digits);
void ConvertNumToDigits(char* digits, uint32_t realNum);

// Communication protocol handler functions
void ProcessReceivedMsg();
void SplitHsAnswer();
void ECUControl();
void ECUHandler();
void RestartTimer();
void StartCommunicationWithECU();
void HandleTurnedOnECUandJetEng();
uint32_t CalculateRPM();
void copy_ECU_To_SPI_Struct(int offset);
void isECUforCurrentRXMUX();
