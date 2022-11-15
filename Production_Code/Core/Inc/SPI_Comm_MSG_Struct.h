/*
 * SPI_comm_struct.h
 *  Created on: 2021. febr. 16.
 *  Author: Novoz�nszki Zsombor
 */

#define NUM_OF_AP_PWM_CHANNELS (19)
typedef struct T_PPM_DATA
 {
 	union{
 		struct{
 			uint16_t PPM_channel_1;
 			uint16_t PPM_channel_2;
 			uint16_t PPM_channel_3;
 			uint16_t PPM_channel_4;
 			uint16_t PPM_channel_5;
 			uint16_t PPM_channel_6;
 			uint16_t PPM_channel_7;
 			uint16_t PPM_channel_8;
 			uint16_t PPM_channel_9;
 			uint16_t PPM_channel_10;
 			uint16_t PPM_channel_11;
 			uint16_t PPM_channel_12;
 			uint16_t PPM_channel_13;
 			uint16_t PPM_channel_14;
 			uint16_t PPM_channel_15;
 			uint16_t PPM_channel_16;
 		};
 		uint16_t aPPMData[16];
 		uint8_t rawPPMData[32];
 	};
 }S_PPM_DATA;

 typedef struct T_BATT_DATA
 {
 	union{
 		uint16_t battery;
 		uint8_t rawBatt[2];
 	};
 }S_BATT_DATA;

 typedef struct T_PWM_DATA_RXMv2
 {
 	union
 	{
 		struct
 		{
 			uint16_t PWM_channel_1;
 			uint16_t PWM_channel_2;
 			uint16_t PWM_channel_3;
 			uint16_t PWM_channel_4;
 			uint16_t PWM_channel_5;
 			uint16_t PWM_channel_6;
 			uint16_t PWM_channel_7;
 			uint16_t PWM_channel_8;
 			uint16_t PWM_channel_9;
 			uint16_t PWM_channel_10;
 			uint16_t PWM_channel_11;
 			uint16_t PWM_channel_12;
 			uint16_t PWM_channel_13;
 			uint16_t PWM_channel_14;
 			uint16_t PWM_channel_15;
 			uint16_t PWM_channel_16;
 			uint16_t PWM_channel_17;
 			uint16_t PWM_channel_18;
 			uint16_t PWM_channel_19;
 		};
 		uint16_t aPWMData[19];
 		uint8_t rawPWMData[38];
 	};
 } S_PWM_DATA_RXMv2;

 // Descriptor field for the autopilot data.
 typedef struct T_SERVO_DATA
 {
     union{
         struct{
         	S_PPM_DATA PPM_data;
         	S_BATT_DATA battery_data;
         	S_PWM_DATA_RXMv2 PWM_data;
         };
         uint16_t aServoData[36];
         uint8_t rawServoData[72];
     };
 }S_SERVO_DATA_RXMv2;

 typedef struct T_DD_PARAMETERS
 {
 	union{
 		struct{
 			uint16_t position;
 			uint16_t current;
 			uint16_t voltage;
 			uint16_t aOtherData[3];
 		};
 		uint16_t aData[6];
 		uint8_t rawDDParData[12];
 	};
 }S_DD_PARAMETERS;

 typedef struct T_DD_DATA
 {
 	union{
 		struct{
 			S_DD_PARAMETERS DD1;
 			S_DD_PARAMETERS DD2;
 		};
 		uint16_t aData[12];
 		uint8_t rawDDData[24];
 	};
 } S_DD_DATA;

 /*
 typedef struct T_ECU_DATA
  {
  	union{
  		struct{
  			int RPM; //4
  			int temperature;	//4
  			float pumpVoltage; //4
  			int turbineState;	//4
  			float throttlePos;	//4
  		};
  		uint8_t rawECUData[20];
  	};
  }S_ECU_DATA;
  */


 typedef struct T_ECU_DATA
 {
 	union{
 		struct{
 			uint16_t fuel;
 			uint8_t aOtherData[24];
 		};
 		uint8_t rawECUData[26];
 	};
 }S_ECU_DATA;

 //Descriptor field for the FlightHAT message
 typedef struct SPI_FH_MSG
 {
 	union{
 		struct{
 			uint32_t header; //19PWM(0-18bit)+ECU(19.bit)+DD(20.bit)=21
 			union{
 				struct{
 					S_SERVO_DATA_RXMv2 servoValues;
 					S_ECU_DATA ECUvalues;
 					S_DD_DATA DDvalues;
 				};
 				uint16_t aData[61];
 				uint8_t rawData[122];
 			};
 			uint16_t status1;
 			uint16_t status2;
 			uint16_t checksum;
 		};
 		uint16_t rawU16[66];
 		uint8_t rawU8[132];
 		};
 }SPI_FH_MSG;
