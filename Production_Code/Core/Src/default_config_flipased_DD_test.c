/*
 * default_config.c
 *
 *
 *	Ezt eles konfig elott nagyon at kene nezni majd, meg frissiteni
 *
 *  Created on: Oct 4, 2021
 *      Author: fbalazs
 */

#include "default_config.h"

#if (manual_config_select == 4)


#include "app.h"
#include "config.h"

void default_config()
{

/*ch1 RXM-1*/
	servoData[0].CH_ID = 1;
	servoData[0].assigned_RX_MUX = RXMUX1;
	servoData[0].PPM_in_CH = 2;
	servoData[0].AP_in_CH = 0;
	servoData[0].PWM_LUT_values[0] = 5590;
	servoData[0].PWM_LUT_values[1] = 7490;
	servoData[0].PWM_LUT_values[2] = 9205;
	servoData[0].PWM_CH = 1;
	servoData[0].CAN_LUT_values[0] = 10000;
	servoData[0].CAN_LUT_values[1] = 12000;
	servoData[0].CAN_LUT_values[2] = 14000;
	servoData[0].CAN_ID = 0x01;


/*ch2 RXM-1*/
	servoData[1].CH_ID = 2;
	servoData[1].assigned_RX_MUX = RXMUX1;
	servoData[1].PPM_in_CH = 3;
	servoData[1].AP_in_CH = 1;
	servoData[1].PWM_LUT_values[0] = 6030;
	servoData[1].PWM_LUT_values[1] = 7655;
	servoData[1].PWM_LUT_values[2] = 9540;
	servoData[1].PWM_CH = 2;
	servoData[1].CAN_LUT_values[0] = 10000;
	servoData[1].CAN_LUT_values[1] = 12000;
	servoData[1].CAN_LUT_values[2] = 14000;
	servoData[1].CAN_ID = 0x02;


/*ch3 RXM-1*/
	servoData[2].CH_ID = 3;
	servoData[2].assigned_RX_MUX = RXMUX1;
	servoData[2].PPM_in_CH = 11;
	servoData[2].AP_in_CH = 2;
	servoData[2].PWM_LUT_values[0] = 6425;
	servoData[2].PWM_LUT_values[1] = 7645;
	servoData[2].PWM_LUT_values[2] = 9635;
	servoData[2].PWM_CH = 3;
	servoData[2].CAN_LUT_values[0] = 10000;
	servoData[2].CAN_LUT_values[1] = 12000;
	servoData[2].CAN_LUT_values[2] = 14000;
	servoData[2].CAN_ID = 0x03;


/*ch4 RXM-1*/
	servoData[3].CH_ID = 4;
	servoData[3].assigned_RX_MUX = RXMUX1;
	servoData[3].PPM_in_CH = 10;
	servoData[3].AP_in_CH = 3;
	servoData[3].PWM_LUT_values[0] = 6040;
	servoData[3].PWM_LUT_values[1] = 7890;
	servoData[3].PWM_LUT_values[2] = 9130;
	servoData[3].PWM_CH = 4;
	servoData[3].CAN_LUT_values[0] = 10000;
	servoData[3].CAN_LUT_values[1] = 12000;
	servoData[3].CAN_LUT_values[2] = 14000;
	servoData[3].CAN_ID = 0x04;


/*ch5 RXM-1*/
	servoData[4].CH_ID = 5;
	servoData[4].assigned_RX_MUX = RXMUX1;
	servoData[4].PPM_in_CH = 12;
	servoData[4].AP_in_CH = 4;
	servoData[4].PWM_LUT_values[0] = 5550; // itt az rxmux1-ben nem 5-7.5-10 a lut x tngelye
	servoData[4].PWM_LUT_values[1] = 7800;
	servoData[4].PWM_LUT_values[2] = 9900;
	servoData[4].PWM_CH = 5;
	servoData[4].CAN_LUT_values[0] = 10000;
	servoData[4].CAN_LUT_values[1] = 12000;
	servoData[4].CAN_LUT_values[2] = 14000;
	servoData[4].CAN_ID = 0x05;


/*ch6 RXM-1*/
	servoData[5].CH_ID = 6;
	servoData[5].assigned_RX_MUX = RXMUX1;
	servoData[5].PPM_in_CH = 14;
	servoData[5].AP_in_CH = 5;
	servoData[5].PWM_LUT_values[0] = 10000;
	servoData[5].PWM_LUT_values[1] = 7500;
	servoData[5].PWM_LUT_values[2] = 5000;
	servoData[5].PWM_CH = 6;
	servoData[5].CAN_LUT_values[0] = 10000;
	servoData[5].CAN_LUT_values[1] = 12000;
	servoData[5].CAN_LUT_values[2] = 14000;
	servoData[5].CAN_ID = 0x06;


/*ch7 RXM-1*/
	servoData[6].CH_ID = 7;
	servoData[6].assigned_RX_MUX = RXMUX1;
	servoData[6].PPM_in_CH = 12;
	servoData[6].AP_in_CH = 6;
	servoData[6].PWM_LUT_values[0] = 10237;
	servoData[6].PWM_LUT_values[1] = 10237;
	servoData[6].PWM_LUT_values[2] = 6265;
	servoData[6].PWM_CH = 7;
	servoData[6].CAN_LUT_values[0] = 10000;
	servoData[6].CAN_LUT_values[1] = 12000;
	servoData[6].CAN_LUT_values[2] = 14000;
	servoData[6].CAN_ID = 0x07;


/*ch8 RXM-2 */
	servoData[7].CH_ID = 8;
	servoData[7].assigned_RX_MUX = RXMUX2;
	servoData[7].PPM_in_CH = 3;
	servoData[7].AP_in_CH = 7;
	servoData[7].PWM_LUT_values[0] = 6395;
	servoData[7].PWM_LUT_values[1] = 7770;
	servoData[7].PWM_LUT_values[2] = 9435;
	servoData[7].PWM_CH = 1;
	servoData[7].CAN_LUT_values[0] = 10000;
	servoData[7].CAN_LUT_values[1] = 12000;
	servoData[7].CAN_LUT_values[2] = 14000;
	servoData[7].CAN_ID = 0x08;


/*ch9 RXM-2 */
	servoData[8].CH_ID = 9;
	servoData[8].assigned_RX_MUX = RXMUX2;
	servoData[8].PPM_in_CH = 2;
	servoData[8].AP_in_CH = 8;
	servoData[8].PWM_LUT_values[0] = 5765;
	servoData[8].PWM_LUT_values[1] = 7460;
	servoData[8].PWM_LUT_values[2] = 8820;
	servoData[8].PWM_CH = 2;
	servoData[8].CAN_LUT_values[0] = 10000;
	servoData[8].CAN_LUT_values[1] = 12000;
	servoData[8].CAN_LUT_values[2] = 14000;
	servoData[8].CAN_ID = 0x09;


/*ch10 RXM-2 */
	servoData[9].CH_ID = 10;
	servoData[9].assigned_RX_MUX = RXMUX2;
	servoData[9].PPM_in_CH = 6;
	servoData[9].AP_in_CH = 9;
	servoData[9].PWM_LUT_values[0] = 5560;
	servoData[9].PWM_LUT_values[1] = 7020;
	servoData[9].PWM_LUT_values[2] = 9150;
	servoData[9].PWM_CH = 3;
	servoData[9].CAN_LUT_values[0] = 10000;
	servoData[9].CAN_LUT_values[1] = 12000;
	servoData[9].CAN_LUT_values[2] = 14000;
	servoData[9].CAN_ID = 0x10;


/*ch11 RXM-2 */
	servoData[10].CH_ID = 11;
	servoData[10].assigned_RX_MUX = RXMUX2;
	servoData[10].PPM_in_CH = 5;
	servoData[10].AP_in_CH = 10;
	servoData[10].PWM_LUT_values[0] = 5570;
	servoData[10].PWM_LUT_values[1] = 7660;
	servoData[10].PWM_LUT_values[2] = 9250;
	servoData[10].PWM_CH = 4;
	servoData[10].CAN_LUT_values[0] = 10000;
	servoData[10].CAN_LUT_values[1] = 12000;
	servoData[10].CAN_LUT_values[2] = 14000;
	servoData[10].CAN_ID = 0x11;


/*ch12 RXM-2 */
	servoData[11].CH_ID = 12;
	servoData[11].assigned_RX_MUX = RXMUX2;
	servoData[11].PPM_in_CH = 12;
	servoData[11].AP_in_CH = 11;
	servoData[11].PWM_LUT_values[0] = 4459;
	servoData[11].PWM_LUT_values[1] = 4459;
	servoData[11].PWM_LUT_values[2] = 8437;
	servoData[11].PWM_CH = 5;
	servoData[11].CAN_LUT_values[0] = 10000;
	servoData[11].CAN_LUT_values[1] = 12000;
	servoData[11].CAN_LUT_values[2] = 14000;
	servoData[11].CAN_ID = 0x12;


/*ch13 RXM-2 */
	servoData[12].CH_ID = 13;
	servoData[12].assigned_RX_MUX = RXMUX2;
	servoData[12].PPM_in_CH = 14;
	servoData[12].AP_in_CH = 12;
	servoData[12].PWM_LUT_values[0] = 10000;
	servoData[12].PWM_LUT_values[1] = 7500;
	servoData[12].PWM_LUT_values[2] = 5000;
	servoData[12].PWM_CH = 6;
	servoData[12].CAN_LUT_values[0] = 10000;
	servoData[12].CAN_LUT_values[1] = 12000;
	servoData[12].CAN_LUT_values[2] = 14000;
	servoData[12].CAN_ID = 0x13;


/*ch14 RXM-2 */
	servoData[13].CH_ID = 14;
	servoData[13].assigned_RX_MUX = RXMUX2;
	servoData[13].PPM_in_CH = 12;
	servoData[13].AP_in_CH = 13;
	servoData[13].PWM_LUT_values[0] = 10000;  //itt az rxmux1-ben nem 5-7.5-10 a lut x tngelye
	servoData[13].PWM_LUT_values[1] = 7500;
	servoData[13].PWM_LUT_values[2] = 5000;
	servoData[13].PWM_CH = 7;
	servoData[13].CAN_LUT_values[0] = 10000;
	servoData[13].CAN_LUT_values[1] = 12000;
	servoData[13].CAN_LUT_values[2] = 14000;
	servoData[13].CAN_ID = 0x14;



/*ch15 RXM-1*/
	servoData[14].CH_ID = 15;
	servoData[14].assigned_RX_MUX = RXMUX1;
	servoData[14].PPM_in_CH = 9;
	servoData[14].AP_in_CH = 14;
	servoData[14].PWM_LUT_values[0] = 5875;
	servoData[14].PWM_LUT_values[1] = 9075;
	servoData[14].PWM_LUT_values[2] = 9345;
	servoData[14].PWM_CH = 8;
	servoData[14].CAN_LUT_values[0] = 10000;
	servoData[14].CAN_LUT_values[1] = 12000;
	servoData[14].CAN_LUT_values[2] = 14000;
	servoData[14].CAN_ID = 0x15;


/*ch16 RXM-1*/
	servoData[15].CH_ID = 16;
	servoData[15].assigned_RX_MUX = RXMUX1;
	servoData[15].PPM_in_CH = 8;
	servoData[15].AP_in_CH = 15;
	servoData[15].PWM_LUT_values[0] = 5390;
	servoData[15].PWM_LUT_values[1] = 5700;
	servoData[15].PWM_LUT_values[2] = 8800;
	servoData[15].PWM_CH = 9;
	servoData[15].CAN_LUT_values[0] = 10000;
	servoData[15].CAN_LUT_values[1] = 12000;
	servoData[15].CAN_LUT_values[2] = 14000;
	servoData[15].CAN_ID = 0x16;


/*ch17 RXM-2 */
	servoData[16].CH_ID = 17;
	servoData[16].assigned_RX_MUX = RXMUX2;
	servoData[16].PPM_in_CH = 4;
	servoData[16].AP_in_CH = 16;
	servoData[16].PWM_LUT_values[0] = 5755;
	servoData[16].PWM_LUT_values[1] = 6875;
	servoData[16].PWM_LUT_values[2] = 8280;
	servoData[16].PWM_CH = 0xFF;
	servoData[16].CAN_LUT_values[0] = 5000;
	servoData[16].CAN_LUT_values[1] = 7500;
	servoData[16].CAN_LUT_values[2] = 10000;
	servoData[16].CAN_ID = 0x7E;				//		<---------------------- DD on WingR_4-------------


/*ch18 RXM-2 */
	servoData[17].CH_ID = 18;
	servoData[17].assigned_RX_MUX = RXMUX2;
	servoData[17].PPM_in_CH = 1;
	servoData[17].AP_in_CH = 17;
	servoData[17].PWM_LUT_values[0] = 6405;
	servoData[17].PWM_LUT_values[1] = 7790;
	servoData[17].PWM_LUT_values[2] = 9010;
	servoData[17].PWM_CH = 9;
	servoData[17].CAN_LUT_values[0] = 10000;
	servoData[17].CAN_LUT_values[1] = 12000;
	servoData[17].CAN_LUT_values[2] = 14000;
	servoData[17].CAN_ID = 0x18;


/*ch19 RXM-1*/
	servoData[18].CH_ID = 19;
	servoData[18].assigned_RX_MUX = RXMUX1;
	servoData[18].PPM_in_CH = 0;
	servoData[18].AP_in_CH = 18;
	servoData[18].PWM_LUT_values[0] = 5000;
	servoData[18].PWM_LUT_values[1] = 7500;
	servoData[18].PWM_LUT_values[2] = 10000;
	servoData[18].PWM_CH = 10;
	servoData[18].CAN_LUT_values[0] = 10000;
	servoData[18].CAN_LUT_values[1] = 12000;
	servoData[18].CAN_LUT_values[2] = 14000;
	servoData[18].CAN_ID = 0x19;


/* Unused channels */


/*chxx RXM-1 not used */
	servoData[19].CH_ID = 0xFF;
	servoData[19].PPM_in_CH = 0xFF;
	servoData[19].AP_in_CH = 0xFF;
	servoData[19].PWM_LUT_values[0] = 5000;
	servoData[19].PWM_LUT_values[1] = 7500;
	servoData[19].PWM_LUT_values[2] = 10000;
	servoData[19].PWM_CH = 0xFF;
	servoData[19].CAN_LUT_values[0] = 10000;
	servoData[19].CAN_LUT_values[1] = 12000;
	servoData[19].CAN_LUT_values[2] = 14000;
	servoData[19].CAN_ID = 0xFF;
	servoData[19].assigned_RX_MUX = RXMUX1;


/*chxx RXM-1 not used */
	servoData[20].CH_ID = 0xFF;
	servoData[20].PPM_in_CH = 0xFF;
	servoData[20].AP_in_CH = 0xFF;
	servoData[20].PWM_LUT_values[0] = 5000;
	servoData[20].PWM_LUT_values[1] = 7500;
	servoData[20].PWM_LUT_values[2] = 10000;
	servoData[20].PWM_CH = 0xFF;
	servoData[20].CAN_LUT_values[0] = 10000;
	servoData[20].CAN_LUT_values[1] = 12000;
	servoData[20].CAN_LUT_values[2] = 14000;
	servoData[20].CAN_ID = 0xFF;
	servoData[20].assigned_RX_MUX = RXMUX1;


/*chxx RXM-2 not used*/
	servoData[21].CH_ID = 0xFF;
	servoData[21].PPM_in_CH = 0xFF;
	servoData[21].AP_in_CH = 0xFF;
	servoData[21].PWM_LUT_values[0] = 5000;
	servoData[21].PWM_LUT_values[1] = 7500;
	servoData[21].PWM_LUT_values[2] = 10000;
	servoData[21].PWM_CH = 0xFF;
	servoData[21].CAN_LUT_values[0] = 10000;
	servoData[21].CAN_LUT_values[1] = 12000;
	servoData[21].CAN_LUT_values[2] = 14000;
	servoData[21].CAN_ID = 0xFF;
	servoData[21].assigned_RX_MUX = RXMUX2;

/*chxx RXM-2 not used*/
	servoData[22].CH_ID = 0xFF;
	servoData[22].PPM_in_CH = 0xFF;
	servoData[22].AP_in_CH = 0xFF;
	servoData[22].PWM_LUT_values[0] = 5000;
	servoData[22].PWM_LUT_values[1] = 7500;
	servoData[22].PWM_LUT_values[2] = 10000;
	servoData[22].PWM_CH = 0xFF;
	servoData[22].CAN_LUT_values[0] = 10000;
	servoData[22].CAN_LUT_values[1] = 12000;
	servoData[22].CAN_LUT_values[2] = 14000;
	servoData[22].CAN_ID = 0xFF;
	servoData[22].assigned_RX_MUX = RXMUX2;


/*chxx RXM-2 not used*/
	servoData[23].CH_ID = 0xFF;
	servoData[23].PPM_in_CH = 0xFF;
	servoData[23].AP_in_CH = 0xFF;
	servoData[23].PWM_LUT_values[0] = 5000;
	servoData[23].PWM_LUT_values[1] = 7500;
	servoData[23].PWM_LUT_values[2] = 10000;
	servoData[23].PWM_CH = 0xFF;
	servoData[23].CAN_LUT_values[0] = 10000;
	servoData[23].CAN_LUT_values[1] = 12000;
	servoData[23].CAN_LUT_values[2] = 14000;
	servoData[23].CAN_ID = 0xFF;
	servoData[23].assigned_RX_MUX = RXMUX2;

}
#endif
