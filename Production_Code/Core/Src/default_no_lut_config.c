/*
 * default_config.c
 *
 *
 *	This is only for testing purposes!!!
 *
 *  Created on: Oct 4, 2021
 *      Author: fbala
 */

#include "default_config.h"

#if (manual_config_select == 0 )

#warning "default config is set to: NO LUT. This should be only used for testing! "

#include "app.h"
#include "config.h"

void default_config()
{

/*ch1 RXM-1*/
	servoData[0].CH_ID = 1;
	servoData[0].PPM_in_CH = 2;
	servoData[0].AP_in_CH = 0;
	servoData[0].PWM_LUT_values[0] = 5000;
	servoData[0].PWM_LUT_values[1] = 7500;
	servoData[0].PWM_LUT_values[2] = 10000;
	servoData[0].PWM_CH = 1;
	servoData[0].CAN_LUT_values[0] = 10000;
	servoData[0].CAN_LUT_values[1] = 12000;
	servoData[0].CAN_LUT_values[2] = 14000;
	servoData[0].CAN_ID = 0x01;
	servoData[0].assigned_RX_MUX = RXMUX1;

/*ch2 RXM-1*/
	servoData[1].CH_ID = 2;
	servoData[1].PPM_in_CH = 3;
	servoData[1].AP_in_CH = 1;
	servoData[1].PWM_LUT_values[0] = 5000;
	servoData[1].PWM_LUT_values[1] = 7500;
	servoData[1].PWM_LUT_values[2] = 10000;
	servoData[1].PWM_CH = 2;
	servoData[1].CAN_LUT_values[0] = 10000;
	servoData[1].CAN_LUT_values[1] = 12000;
	servoData[1].CAN_LUT_values[2] = 14000;
	servoData[1].CAN_ID = 0x02;
	servoData[1].assigned_RX_MUX = RXMUX1;

/*ch3 RXM-1*/
	servoData[2].CH_ID = 3;
	servoData[2].PPM_in_CH = 11;
	servoData[2].AP_in_CH = 2;
	servoData[2].PWM_LUT_values[0] = 5000;
	servoData[2].PWM_LUT_values[1] = 7500;
	servoData[2].PWM_LUT_values[2] = 10000;
	servoData[2].PWM_CH = 3;
	servoData[2].CAN_LUT_values[0] = 10000;
	servoData[2].CAN_LUT_values[1] = 12000;
	servoData[2].CAN_LUT_values[2] = 14000;
	servoData[2].CAN_ID = 0x03;
	servoData[2].assigned_RX_MUX = RXMUX1;

/*ch4 RXM-1*/
	servoData[3].CH_ID = 4;
	servoData[3].PPM_in_CH = 10;
	servoData[3].AP_in_CH = 3;
	servoData[3].PWM_LUT_values[0] = 5000;
	servoData[3].PWM_LUT_values[1] = 7500;
	servoData[3].PWM_LUT_values[2] = 10000;
	servoData[3].PWM_CH = 4;
	servoData[3].CAN_LUT_values[0] = 10000;
	servoData[3].CAN_LUT_values[1] = 12000;
	servoData[3].CAN_LUT_values[2] = 14000;
	servoData[3].CAN_ID = 0x04;
	servoData[3].assigned_RX_MUX = RXMUX1;

/*ch5 RXM-1*/
	servoData[4].CH_ID = 5;
	servoData[4].PPM_in_CH = 12;
	servoData[4].AP_in_CH = 4;
	servoData[4].PWM_LUT_values[0] = 5000;
	servoData[4].PWM_LUT_values[1] = 7500;
	servoData[4].PWM_LUT_values[2] = 10000;
	servoData[4].PWM_CH = 5;
	servoData[4].CAN_LUT_values[0] = 10000;
	servoData[4].CAN_LUT_values[1] = 12000;
	servoData[4].CAN_LUT_values[2] = 14000;
	servoData[4].CAN_ID = 0x05;
	servoData[4].assigned_RX_MUX = RXMUX1;

/*ch6 RXM-1*/
	servoData[5].CH_ID = 6;
	servoData[5].PPM_in_CH = 14;
	servoData[5].AP_in_CH = 5;
	servoData[5].PWM_LUT_values[0] = 5000;
	servoData[5].PWM_LUT_values[1] = 7500;
	servoData[5].PWM_LUT_values[2] = 10000;
	servoData[5].PWM_CH = 6;
	servoData[5].CAN_LUT_values[0] = 10000;
	servoData[5].CAN_LUT_values[1] = 12000;
	servoData[5].CAN_LUT_values[2] = 14000;
	servoData[5].CAN_ID = 0x06;
	servoData[5].assigned_RX_MUX = RXMUX1;

/*ch7 RXM-1*/
	servoData[6].CH_ID = 7;
	servoData[6].PPM_in_CH = 12;
	servoData[6].AP_in_CH = 6;
	servoData[6].PWM_LUT_values[0] = 5000;
	servoData[6].PWM_LUT_values[1] = 7500;
	servoData[6].PWM_LUT_values[2] = 10000;
	servoData[6].PWM_CH = 7;
	servoData[6].CAN_LUT_values[0] = 10000;
	servoData[6].CAN_LUT_values[1] = 12000;
	servoData[6].CAN_LUT_values[2] = 14000;
	servoData[6].CAN_ID = 0x07;
	servoData[6].assigned_RX_MUX = RXMUX1;

/*ch8 RXM-1 */
	servoData[7].CH_ID = 8;
	servoData[7].PPM_in_CH = 3;
	servoData[7].AP_in_CH = 7;
	servoData[7].PWM_LUT_values[0] = 5000;
	servoData[7].PWM_LUT_values[1] = 7500;
	servoData[7].PWM_LUT_values[2] = 10000;
	servoData[7].PWM_CH = 8;
	servoData[7].CAN_LUT_values[0] = 10000;
	servoData[7].CAN_LUT_values[1] = 12000;
	servoData[7].CAN_LUT_values[2] = 14000;
	servoData[7].CAN_ID = 0x08;
	servoData[7].assigned_RX_MUX = RXMUX1;

/*ch9 RXM-1 */
	servoData[8].CH_ID = 9;
	servoData[8].PPM_in_CH = 2;
	servoData[8].AP_in_CH = 8;
	servoData[8].PWM_LUT_values[0] = 5000;
	servoData[8].PWM_LUT_values[1] = 7500;
	servoData[8].PWM_LUT_values[2] = 10000;
	servoData[8].PWM_CH = 9;
	servoData[8].CAN_LUT_values[0] = 10000;
	servoData[8].CAN_LUT_values[1] = 12000;
	servoData[8].CAN_LUT_values[2] = 14000;
	servoData[8].CAN_ID = 0x09;
	servoData[8].assigned_RX_MUX = RXMUX1;

/*ch10 RXM-1 */
	servoData[9].CH_ID = 10;
	servoData[9].PPM_in_CH = 6;
	servoData[9].AP_in_CH = 9;
	servoData[9].PWM_LUT_values[0] = 5000;
	servoData[9].PWM_LUT_values[1] = 7500;
	servoData[9].PWM_LUT_values[2] = 10000;
	servoData[9].PWM_CH = 10;
	servoData[9].CAN_LUT_values[0] = 10000;
	servoData[9].CAN_LUT_values[1] = 12000;
	servoData[9].CAN_LUT_values[2] = 14000;
	servoData[9].CAN_ID = 0x0A;
	servoData[9].assigned_RX_MUX = RXMUX1;

/*ch11 RXM-1 */
	servoData[10].CH_ID = 11;
	servoData[10].PPM_in_CH = 5;
	servoData[10].AP_in_CH = 10;
	servoData[10].PWM_LUT_values[0] = 5000;
	servoData[10].PWM_LUT_values[1] = 7500;
	servoData[10].PWM_LUT_values[2] = 10000;
	servoData[10].PWM_CH = 11;
	servoData[10].CAN_LUT_values[0] = 10000;
	servoData[10].CAN_LUT_values[1] = 12000;
	servoData[10].CAN_LUT_values[2] = 14000;
	servoData[10].CAN_ID = 0x0B;
	servoData[10].assigned_RX_MUX = RXMUX1;

/*ch12 RXM-2 */
	servoData[11].CH_ID = 12;
	servoData[11].PPM_in_CH = 12;
	servoData[11].AP_in_CH = 11;
	servoData[11].PWM_LUT_values[0] = 5000;
	servoData[11].PWM_LUT_values[1] = 7500;
	servoData[11].PWM_LUT_values[2] = 10000;
	servoData[11].PWM_CH = 12;
	servoData[11].CAN_LUT_values[0] = 10000;
	servoData[11].CAN_LUT_values[1] = 12000;
	servoData[11].CAN_LUT_values[2] = 14000;
	servoData[11].CAN_ID = 0x0C;
	servoData[11].assigned_RX_MUX = RXMUX1;

/*ch13 RXM-2 */
	servoData[12].CH_ID = 13;
	servoData[12].PPM_in_CH = 14;
	servoData[12].AP_in_CH = 12;
	servoData[12].PWM_LUT_values[0] = 5000;
	servoData[12].PWM_LUT_values[1] = 7500;
	servoData[12].PWM_LUT_values[2] = 10000;
	servoData[12].PWM_CH = 1;
	servoData[12].CAN_LUT_values[0] = 10000;
	servoData[12].CAN_LUT_values[1] = 12000;
	servoData[12].CAN_LUT_values[2] = 14000;
	servoData[12].CAN_ID = 0x0D;
	servoData[12].assigned_RX_MUX = RXMUX2;

/*ch14 RXM-2 */
	servoData[13].CH_ID = 14;
	servoData[13].PPM_in_CH = 12;
	servoData[13].AP_in_CH = 13;
	servoData[13].PWM_LUT_values[0] = 5000;
	servoData[13].PWM_LUT_values[1] = 7500;
	servoData[13].PWM_LUT_values[2] = 10000;
	servoData[13].PWM_CH = 2;
	servoData[13].CAN_LUT_values[0] = 10000;
	servoData[13].CAN_LUT_values[1] = 12000;
	servoData[13].CAN_LUT_values[2] = 14000;
	servoData[13].CAN_ID = 0x0E;
	servoData[13].assigned_RX_MUX = RXMUX2;


/*ch15 RXM-2*/
	servoData[14].CH_ID = 15;
	servoData[14].PPM_in_CH = 9;
	servoData[14].AP_in_CH = 14;
	servoData[14].PWM_LUT_values[0] = 5000;
	servoData[14].PWM_LUT_values[1] = 7500;
	servoData[14].PWM_LUT_values[2] = 10000;
	servoData[14].PWM_CH = 3;
	servoData[14].CAN_LUT_values[0] = 10000;
	servoData[14].CAN_LUT_values[1] = 12000;
	servoData[14].CAN_LUT_values[2] = 14000;
	servoData[14].CAN_ID = 0x0F;
	servoData[14].assigned_RX_MUX = RXMUX2;

/*ch16 RXM-2*/
	servoData[15].CH_ID = 16;
	servoData[15].PPM_in_CH = 8;
	servoData[15].AP_in_CH = 15;
	servoData[15].PWM_LUT_values[0] = 5000;
	servoData[15].PWM_LUT_values[1] = 7500;
	servoData[15].PWM_LUT_values[2] = 10000;
	servoData[15].PWM_CH = 4;
	servoData[15].CAN_LUT_values[0] = 10000;
	servoData[15].CAN_LUT_values[1] = 12000;
	servoData[15].CAN_LUT_values[2] = 14000;
	servoData[15].CAN_ID = 0x10;
	servoData[15].assigned_RX_MUX = RXMUX2;

/*ch17 RXM-2 */
	servoData[16].CH_ID = 17;
	servoData[16].PPM_in_CH = 4;
	servoData[16].AP_in_CH = 16;
	servoData[16].PWM_LUT_values[0] = 5000;
	servoData[16].PWM_LUT_values[1] = 7500;
	servoData[16].PWM_LUT_values[2] = 10000;
	servoData[16].PWM_CH = 5;
	servoData[16].CAN_LUT_values[0] = 10000;
	servoData[16].CAN_LUT_values[1] = 12000;
	servoData[16].CAN_LUT_values[2] = 14000;
	servoData[16].CAN_ID = 0x11;
	servoData[16].assigned_RX_MUX = RXMUX2;

/*ch18 RXM-2 */
	servoData[17].CH_ID = 18;
	servoData[17].PPM_in_CH = 1;
	servoData[17].AP_in_CH = 17;
	servoData[17].PWM_LUT_values[0] = 5000;
	servoData[17].PWM_LUT_values[1] = 7500;
	servoData[17].PWM_LUT_values[2] = 10000;
	servoData[17].PWM_CH = 6;
	servoData[17].CAN_LUT_values[0] = 10000;
	servoData[17].CAN_LUT_values[1] = 12000;
	servoData[17].CAN_LUT_values[2] = 14000;
	servoData[17].CAN_ID = 0x12;
	servoData[17].assigned_RX_MUX = RXMUX2;

/*ch19 RXM-2*/
	servoData[18].CH_ID = 19;
	servoData[18].PPM_in_CH = 0;
	servoData[18].AP_in_CH = 18;
	servoData[18].PWM_LUT_values[0] = 5000;
	servoData[18].PWM_LUT_values[1] = 7500;
	servoData[18].PWM_LUT_values[2] = 10000;
	servoData[18].PWM_CH = 7;
	servoData[18].CAN_LUT_values[0] = 10000;
	servoData[18].CAN_LUT_values[1] = 12000;
	servoData[18].CAN_LUT_values[2] = 14000;
	servoData[18].CAN_ID = 0x13;
	servoData[18].assigned_RX_MUX = RXMUX2;

/*ch20 RXM-2*/
	servoData[19].CH_ID = 20;
	servoData[19].PPM_in_CH = 12;
	servoData[19].AP_in_CH = 16;
	servoData[19].PWM_LUT_values[0] = 5000;
	servoData[19].PWM_LUT_values[1] = 7500;
	servoData[19].PWM_LUT_values[2] = 10000;
	servoData[19].PWM_CH = 8;
	servoData[19].CAN_LUT_values[0] = 10000;
	servoData[19].CAN_LUT_values[1] = 12000;
	servoData[19].CAN_LUT_values[2] = 14000;
	servoData[19].CAN_ID = 0x14;
	servoData[19].assigned_RX_MUX = RXMUX2;


/*ch21 RXM-2*/
	servoData[20].CH_ID = 21;
	servoData[20].PPM_in_CH = 12;
	servoData[20].AP_in_CH = 16;
	servoData[20].PWM_LUT_values[0] = 5000;
	servoData[20].PWM_LUT_values[1] = 7500;
	servoData[20].PWM_LUT_values[2] = 10000;
	servoData[20].PWM_CH = 9;
	servoData[20].CAN_LUT_values[0] = 10000;
	servoData[20].CAN_LUT_values[1] = 12000;
	servoData[20].CAN_LUT_values[2] = 14000;
	servoData[20].CAN_ID = 0x15;
	servoData[20].assigned_RX_MUX = RXMUX2;


/*ch22 RXM-2*/
	servoData[21].CH_ID = 22;
	servoData[21].PPM_in_CH = 12;
	servoData[21].AP_in_CH = 16;
	servoData[21].PWM_LUT_values[0] = 5000;
	servoData[21].PWM_LUT_values[1] = 7500;
	servoData[21].PWM_LUT_values[2] = 10000;
	servoData[21].PWM_CH = 10;
	servoData[21].CAN_LUT_values[0] = 10000;
	servoData[21].CAN_LUT_values[1] = 12000;
	servoData[21].CAN_LUT_values[2] = 14000;
	servoData[21].CAN_ID = 0x16;
	servoData[21].assigned_RX_MUX = RXMUX2;

/*ch23 RXM-2*/
	servoData[22].CH_ID = 23;
	servoData[22].PPM_in_CH = 12;
	servoData[22].AP_in_CH = 16;
	servoData[22].PWM_LUT_values[0] = 5000;
	servoData[22].PWM_LUT_values[1] = 7500;
	servoData[22].PWM_LUT_values[2] = 10000;
	servoData[22].PWM_CH = 11;
	servoData[22].CAN_LUT_values[0] = 10000;
	servoData[22].CAN_LUT_values[1] = 12000;
	servoData[22].CAN_LUT_values[2] = 14000;
	servoData[22].CAN_ID = 0x17;
	servoData[22].assigned_RX_MUX = RXMUX2;


/*ch24 RXM-2*/
	servoData[23].CH_ID = 24;
	servoData[23].PPM_in_CH = 12;
	servoData[23].AP_in_CH = 16;
	servoData[23].PWM_LUT_values[0] = 5000;
	servoData[23].PWM_LUT_values[1] = 7500;
	servoData[23].PWM_LUT_values[2] = 10000;
	servoData[23].PWM_CH = 12;
	servoData[23].CAN_LUT_values[0] = 10000;
	servoData[23].CAN_LUT_values[1] = 12000;
	servoData[23].CAN_LUT_values[2] = 14000;
	servoData[23].CAN_ID = 0x18;
	servoData[23].assigned_RX_MUX = RXMUX2;

}

#endif
