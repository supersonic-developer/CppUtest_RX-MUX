// ************************ Includes ************************ //
#include "usart.h"
#include "ecu_uart.h"
#include <string.h>
#include <math.h>
#include "error_detection.h"
#include "spi.h"
#include "servo.h"
#include "rc_superv_logic.h"

// ************************ Global variables ************************ //
// Flags for Round Robin with interrupts
uint8_t UART1_Flag_TxReady = 0;
uint8_t UART1_Flag_RxReady = 0;
uint8_t UART1_Flag_Timer=0;
int ThrottleChannelID=-1;
uint8_t firstRecMsg=1;


// Periphery and communication protocol state variables
HAL_StatusTypeDef UART1_Status=HAL_OK;
uint8_t ecuStarted=0;
uint8_t validatedEngineState=0;
uint8_t engineSwitchWindow=0;
uint8_t waitCnt=0;
uint8_t doubleMsgPart=0;	// Reading or writing cycle
uint8_t firstMsg=1;
DeviceState jetEngState=TurnedOff;
DeviceState ecuState=TurnedOff;
EcuAnswer currentAnswer;	// Type of ECU answer
uint16_t numBytesReceived=0;


// Character arrays for commands and answers
char commandArray[50];
char answerArray[50];
int dummy=0;
// Byte buffers
uint8_t txBuffer[50];
uint8_t receivedByte;
uint8_t rxBuffer[50];
// Read out jet engine+ECU parameters, it serves future development
EcuHsAnswer jetEngParams;


// ****************** ECU command functions ********************** //
/* Brief Turn on/off commands via UART
 */
HAL_StatusTypeDef SendWSMPacket(uint8_t SerialCommandOn)
{
	if(SerialCommandOn==0)
		strcpy(commandArray,"1,WSM,0\r");
	else
		strcpy(commandArray,"1,WSM,1\r");
	ConvertCharToByte(8);
	UART1_Status=HAL_UART_Transmit_DMA(&huart1, txBuffer, 8);
	return UART1_Status;
}

/* Brief Turn on/off jet engine
 */
HAL_StatusTypeDef SendTCOPacket(uint8_t engineOn)
{
	if(engineOn==0)
		strcpy(commandArray,"1,TCO,0\r");
	else
		strcpy(commandArray,"1,TCO,1\r");
	ConvertCharToByte(8);
	UART1_Status=HAL_UART_Transmit_DMA(&huart1, txBuffer, 8);
	return UART1_Status;
}

/* Brief Query data from ECU
 */
HAL_StatusTypeDef SendRACPacket()
{
	strcpy(commandArray,"1,RAC,1\r");
	ConvertCharToByte(8);
	UART1_Status=HAL_UART_Transmit_DMA(&huart1, txBuffer, 8);
	return UART1_Status;
}

/* Brief Sets the RPM of jet engine
 * Param RPM: 32 bit integer of RPM
 */
HAL_StatusTypeDef SendWRPPacket(uint32_t RPM)
{
	// Gain digits of RPM value (max 106000 RPM) => maximum 6 digit
	char digits[7];
	ConvertNumToDigits(digits, RPM);

	// Copy command frame and RPM value into buffer
	strcpy(commandArray,"1,WRP,");
	uint16_t length=strlen(commandArray);
	for(int i=0;i<strlen(digits);i++)
		commandArray[length++]=digits[i];
	commandArray[length++]='\r';

	ConvertCharToByte(length);

	// Send of command
	UART1_Status=HAL_UART_Transmit_DMA(&huart1, txBuffer, length);
	return UART1_Status;
}

// ****************** Character array handler functions ********************** //
/* Brief Compares 2 char array
 * Retval 1 if the arrays are same, else 0
 */
uint8_t CompareBuffers(const char* buffer1, const char* buffer2)
{
	if(strlen(buffer1)!=strlen(buffer2))
		return 0;
	 for(int i=0;i<strlen(buffer1);i++)
		 if(buffer1[i]!=buffer2[i])
			 return 0;
	 return 1;
}

/* Brief Convert character command array to byte flow
 */
void ConvertCharToByte(int length)
{
	for(int i=0;i<length;i++)
		txBuffer[i]=commandArray[i];
}

/* Brief Copy received bytes into character array
 */
void ConvertByteToChar()
{
	int cnt=0;
	char fullMsg[50];
	while(rxBuffer[cnt]!='\r' && cnt<sizeof(rxBuffer))
	{
		fullMsg[cnt]=(char)rxBuffer[cnt];
		cnt++;
	}
	fullMsg[cnt]='\0';
	char *validMsgStart=strstr(fullMsg,"1,");
	if(validMsgStart!=NULL)
		strcpy(answerArray,validMsgStart);
}

/* Brief Convert character digits to double number
 * Param digits: character array of digits
 * Retval The calculated single number
 */
float ConvertDigitsToRealNum(char* digits)
{
	float realNum=0;
	int cnt=0;
	// Find the the border of whole and fraction parts
	while(digits[cnt]!='.' && cnt<strlen(digits))
		cnt++;

	// There were not point, it is a whole number
	if(cnt==strlen(digits))
	{
		int validDigits=strlen(digits);
		for(int i=0;i<validDigits;i++)
			realNum+=(digits[i]-'0')*pow(10, validDigits-1-i);
	}
	else
	{
		int cnt2=1;
		while((cnt+cnt2)<strlen(digits) || (cnt-cnt2)>=0)
		{
			// Fraction part
			if((cnt+cnt2)<strlen(digits))
				realNum+=(digits[cnt+cnt2]-'0')*pow(10, -1*cnt2);

			// Whole part
			if((cnt-cnt2)>=0)
				realNum+=(digits[cnt-cnt2]-'0')*pow(10, cnt2-1);

			cnt2++;
		}
	}
	return realNum;
}

/* Brief Convert 32 bit integer into digits
 * Param digits: character array of digits
 * Param realNum: 32 bit integer
 */
void ConvertNumToDigits(char* digits, uint32_t realNum)
{
	uint8_t currentDigit=0;
	int i=0;
	while(realNum!=0)
	{
		currentDigit=realNum%10;
		realNum/=10;
		digits[i]='0'+currentDigit;
		i++;
		digits[i]='\0';
	}

	// Reverse array, Big Endian on 0th element
	char temp;
	for(int i=0;i<strlen(digits)/2;i++)
	{
		temp=digits[i];
		digits[i]=digits[strlen(digits)-1-i];
		digits[strlen(digits)-1-i]=temp;
	}
}


// ****************** Communication protocol functions ********************** //
/* Brief Process received messages and handle ECU, jet engine state machines
 */
void ProcessReceivedMsg()
{
	ConvertByteToChar();
	char *command;
	char temp[50];
	strcpy(temp, answerArray);
	command = strtok(temp, ",");
	command = strtok(NULL, ",");
	if(CompareBuffers("WSM", command))
		currentAnswer=WSM;
	else if(CompareBuffers("TCO", command))
		currentAnswer=TCO;
	else if(CompareBuffers("RAC", command))
		currentAnswer=RAC;
	else if(CompareBuffers("WRP", command))
		currentAnswer=WRP;
	else if(CompareBuffers("HS", command))
	{
		switch(currentAnswer)
		{
			case WSM:
				if(errors.ecu==0)
				{
					if(ecuState==TurningOn)
						ecuState=TurnedOn;
					else if(ecuState==TurningOff)
						ecuState=TurnedOff;
					if(firstRecMsg)
					{
						firstRecMsg=0;
						ecuStarted=1;
					}
				}
				else
					errors.ecu=0;
				break;
			case TCO:
				if(errors.ecu==0)
				{
					if(jetEngState==TurningOn)
						jetEngState=TurnedOn;
					else if(jetEngState==TurningOff)
						jetEngState=TurnedOff;
				}
				else
					errors.ecu=0;
				break;
			case WRP:
				copy_ECU_To_SPI_Struct(0); // save requested RPM
				break;
			case RAC:
				copy_ECU_To_SPI_Struct(ENG_DATA_OFFSET);
				break;
			default:
				break;
		}
		SplitHsAnswer();
	}
}


/* Brief copy the currently received data in the SPI buffer
 */
void copy_ECU_To_SPI_Struct(int offset)
{
	// Flush buffer
	for(int i=0;i<sizeof(process_Buff.ECUvalues.aOtherData);i++)
		process_Buff.ECUvalues.aOtherData[i]=0;
	int cnt=0;
	if(offset==0)
	{
		// Copy actual data
		while(cnt<sizeof(process_Buff.ECUvalues.aOtherData) && commandArray[cnt]!='\r')
		{
			process_Buff.ECUvalues.aOtherData[cnt]=commandArray[cnt];
			cnt++;
		}
	}
	else
	{
		while(cnt<sizeof(process_Buff.ECUvalues.aOtherData) && (cnt+offset)<strlen(answerArray))
		{
			process_Buff.ECUvalues.aOtherData[cnt]=answerArray[cnt+offset];
			cnt++;
		}
	}
}

/* Brief Fill up ECU answer parameters according to received message
 */
void SplitHsAnswer()
{
	char *partOfMsg=strtok(answerArray, ",");
	int index=0;

	while( partOfMsg != NULL ) {
		switch(index)
		{
			case 0:
				if(CompareBuffers(partOfMsg, "1")!=1)
					errors.ecu=INVALID_FRAME;
				break;
			case 1:
				if(CompareBuffers(partOfMsg,"HS")!=1)
					errors.ecu=INVALID_FRAME;
				break;
			case 2:
				if(CompareBuffers(partOfMsg,"UC"))
					errors.ecu=UNKNOW_COMMAND;
				else if(CompareBuffers(partOfMsg,"PA"))
					errors.ecu=WRONG_PARAMETER_NUMBER;
				else if(CompareBuffers(partOfMsg,"NA"))
					errors.ecu=COMMAND_NOT_ALLOWED;
				else if(CompareBuffers(partOfMsg,"PR"))
					errors.ecu=WRONG_PARAMETER_NUMBER;
				else if(CompareBuffers(partOfMsg,"PL"))
					errors.ecu=WRONG_DATA_FORMAT;
				else if(CompareBuffers(partOfMsg,"DF"))
					errors.ecu=WRONG_DATA_FORMAT;
				break;
			case 3:
				jetEngParams.turbineRPM=(int)ConvertDigitsToRealNum(partOfMsg);
				break;
			case 4:
				jetEngParams.turbineEGT=(int)ConvertDigitsToRealNum(partOfMsg);
				break;
			case 5:
				jetEngParams.pumpVoltage=ConvertDigitsToRealNum(partOfMsg);
				break;
			case 6:
				jetEngParams.turbineState=(int)ConvertDigitsToRealNum(partOfMsg);
				break;
			case 7:
				jetEngParams.throttlePos=ConvertDigitsToRealNum(partOfMsg);
				break;
			default:
				break;
		}
		partOfMsg = strtok(NULL, ",");
		index++;
	}
}

/* Brief Restarting the timer, which is used for UART
 */
void RestartTimer()
{
	HAL_TIM_Base_Stop_IT(&htim9);
	htim2.Instance->CNT=0;
	HAL_TIM_Base_Start_IT(&htim9);
	UART1_Flag_Timer=0;
}


/* Brief handle the whole communication in steady state
 */
void ECUControl()
{
	switch(ecuState)
	{
		case TurnedOff:
			if(UART1_Flag_TxReady && UART1_Flag_Timer)
			{
				UART1_Flag_TxReady=0;
				RestartTimer();
				SendWSMPacket(1); // Turn on UART commands on ECU
				ecuState=TurningOn;
			}
			break;
		case TurningOff: // With RX-MUXv2 implementation we will never turn off UART commands
			break;
		case TurningOn:
			if(UART1_Flag_Timer && UART1_Flag_TxReady)
				ecuState=TurnedOff;
			break;
		case TurnedOn:
			switch(jetEngState)
			{
				case TurnedOff:
					if(UART1_Flag_TxReady && validatedEngineState && UART1_Flag_Timer)
					{
						UART1_Flag_Timer=0;
						UART1_Flag_TxReady=0;
						SendTCOPacket(1);
						jetEngState=TurningOn;
						RestartTimer();
					}
					else if(UART1_Flag_TxReady && UART1_Flag_Timer)
					{
						UART1_Flag_TxReady=0;
						UART1_Flag_Timer=0;
						SendRACPacket();
					}
					break;
				case TurningOff:
					if(UART1_Flag_Timer && UART1_Flag_TxReady)
						jetEngState=TurnedOn;
					break;
				case TurningOn:
					if(UART1_Flag_Timer && UART1_Flag_TxReady)
						jetEngState=TurnedOff;
					break;
				case TurnedOn:
					HandleTurnedOnECUandJetEng();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}


/* Brief manage the turned on ECU and jet engine state
 */
void HandleTurnedOnECUandJetEng()
{
	if(UART1_Flag_TxReady && !validatedEngineState && UART1_Flag_Timer)
	{
		UART1_Flag_TxReady=0;
		SendTCOPacket(0); // Turn off jet engine
		jetEngState=TurningOff;
		RestartTimer();
	}
	else if(UART1_Flag_TxReady && UART1_Flag_Timer)
	{
		UART1_Flag_TxReady=0;
		UART1_Flag_Timer=0;
		if(doubleMsgPart==0)
		{
			doubleMsgPart=1;
			SendWRPPacket(CalculateRPM()); // send 0th PPM channel (throttle) value
		}
		else
		{
			doubleMsgPart=0;
			SendRACPacket();
		}
	}
}


/* Brief convert RC PPM signal to RPM with linear interpolation
 * Retval current RPM value
 */
uint32_t CalculateRPM()
{
	uint32_t step=(RPM_MAX-RPM_MIN)/5000;
	uint32_t rpm=RPM_MIN+step*(Servo_Channels[ThrottleChannelID]->current_pwm_out-5000);
	return rpm;
}

/* Brief Start communication with ECU, both transmit and receive
 */
void StartCommunicationWithECU()
{
	// Start timer, transmit, receive
	HAL_TIM_Base_Start_IT(&htim9);
	UART1_Flag_Timer=0;
	SendWSMPacket(1);
	process_Buff.status1|=0x4;
	ecuState=TurningOn;
	UART1_Status=HAL_UART_Receive_DMA(&huart1, &receivedByte, 1);
}

void isECUforCurrentRXMUX()
{
	for(int cnt=0;cnt<NUM_OF_OUTPUT_CHANNELS;cnt++)
	{
		if(Servo_Channels[cnt]->PPM_in_CH==0 && Servo_Channels[cnt]->CH_ID>0)
		{
			process_Buff.header|=0x80000;
			ThrottleChannelID=cnt;
			return;
		}
	}
}
/* Brief Controls both ECU and jet engine and even checks answer and signal fault
 */
void ECUHandler()
{
	if(ThrottleChannelID!=-1)
	{
		if(ecuStarted && waitCnt<40 && UART1_Flag_Timer)
		{
			waitCnt++;
			UART1_Flag_Timer=0;
			ecuState=TurnedOff;
		}
		else
		{
			if(firstMsg)
			{
				StartCommunicationWithECU();
				firstMsg=0;
			}
			ECUControl();
			if(UART1_Flag_RxReady)
			{
				UART1_Flag_RxReady=0;
				ProcessReceivedMsg();
				process_Buff.status1|=0x8;
			}
			else if(huart1.RxState==HAL_UART_STATE_READY)
				UART1_Status=HAL_UART_Receive_DMA(&huart1, &receivedByte, 1);
		}
	}
}
