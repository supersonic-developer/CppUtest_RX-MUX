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

#if (manual_config_select == 1)


#include "app.h"
#include "config.h"
#include "servo.h"

void default_config()
{

/*ch1 RXM-1*/
	servoData[0].CH_ID = 1;
	servoData[0].Mode = RX1_PWM;
	servoData[0].PPM_in_CH = 2;
	servoData[0].AP_in_CH = 0;
	servoData[0].PWM_LUT_values[0] = 5588;
	servoData[0].PWM_LUT_values[1] = 7490;
	servoData[0].PWM_LUT_values[2] = 9206;
	servoData[0].PWM_CH = 1;
	servoData[0].CAN_LUT_values[0] = 10000;
	servoData[0].CAN_LUT_values[1] = 12000;
	servoData[0].CAN_LUT_values[2] = 14000;
	servoData[0].CAN_ID = 0xFF;


/*ch2 RXM-1*/
	servoData[1].CH_ID = 2;
	servoData[1].Mode = RX1_PWM;
	servoData[1].PPM_in_CH = 3;
	servoData[1].AP_in_CH = 1;
	servoData[1].PWM_LUT_values[0] = 6030;
	servoData[1].PWM_LUT_values[1] = 7655;
	servoData[1].PWM_LUT_values[2] = 9544;
	servoData[1].PWM_CH = 2;
	servoData[1].CAN_LUT_values[0] = 10000;
	servoData[1].CAN_LUT_values[1] = 12000;
	servoData[1].CAN_LUT_values[2] = 14000;
	servoData[1].CAN_ID = 0xFF;


/*ch3 RXM-1*/
	servoData[2].CH_ID = 3;
	servoData[2].Mode = RX1_PWM;
	servoData[2].PPM_in_CH = 11;
	servoData[2].AP_in_CH = 2;
	servoData[2].PWM_LUT_values[0] = 6423;
	servoData[2].PWM_LUT_values[1] = 7645;
	servoData[2].PWM_LUT_values[2] = 9635;
	servoData[2].PWM_CH = 3;
	servoData[2].CAN_LUT_values[0] = 10000;
	servoData[2].CAN_LUT_values[1] = 12000;
	servoData[2].CAN_LUT_values[2] = 14000;
	servoData[2].CAN_ID = 0xFF;


/*ch4 RXM-1*/
	servoData[3].CH_ID = 4;
	servoData[3].Mode = RX1_PWM;
	servoData[3].PPM_in_CH = 10;
	servoData[3].AP_in_CH = 3;
	servoData[3].PWM_LUT_values[0] = 6041;
	servoData[3].PWM_LUT_values[1] = 7890;
	servoData[3].PWM_LUT_values[2] = 9130;
	servoData[3].PWM_CH = 4;
	servoData[3].CAN_LUT_values[0] = 10000;
	servoData[3].CAN_LUT_values[1] = 12000;
	servoData[3].CAN_LUT_values[2] = 14000;
	servoData[3].CAN_ID = 0xFF;


/*ch5 RXM-1*/
	servoData[4].CH_ID = 5;
	servoData[4].Mode = RX1_PWM;
	servoData[4].PPM_in_CH = 14;
	servoData[4].AP_in_CH = 5;
	servoData[4].PWM_LUT_values[0] = 10000; // itt az rxmux1-ben nem 5-7.5-10 a lut x tngelye
	servoData[4].PWM_LUT_values[1] = 7500;
	servoData[4].PWM_LUT_values[2] = 5000;
	servoData[4].PWM_CH = 5;
	servoData[4].CAN_LUT_values[0] = 10000;
	servoData[4].CAN_LUT_values[1] = 12000;
	servoData[4].CAN_LUT_values[2] = 14000;
	servoData[4].CAN_ID = 0xFF;


/*ch6 RXM-1*/
	servoData[5].CH_ID = 6;
	servoData[5].Mode = RX1_PWM;
	servoData[5].PPM_in_CH = 12;
	servoData[5].AP_in_CH = 6;
	servoData[5].PWM_LUT_values[0] = 10237;
	servoData[5].PWM_LUT_values[1] = 8612;
	servoData[5].PWM_LUT_values[2] = 6265;
	servoData[5].PWM_CH = 6;
	servoData[5].CAN_LUT_values[0] = 10000;
	servoData[5].CAN_LUT_values[1] = 12000;
	servoData[5].CAN_LUT_values[2] = 14000;
	servoData[5].CAN_ID = 0xFF;


/*ch7 RXM-1*/
	servoData[6].CH_ID = 7;
	servoData[6].Mode = RX1_PWM;
	servoData[6].PPM_in_CH = 9;
	servoData[6].AP_in_CH = 14;
	servoData[6].PWM_LUT_values[0] = 5875;
	servoData[6].PWM_LUT_values[1] = 9075;
	servoData[6].PWM_LUT_values[2] = 9345;
	servoData[6].PWM_CH = 7;
	servoData[6].CAN_LUT_values[0] = 10000;
	servoData[6].CAN_LUT_values[1] = 12000;
	servoData[6].CAN_LUT_values[2] = 14000;
	servoData[6].CAN_ID = 0xFF;


/*ch8 RXM-2 */
	servoData[7].CH_ID = 8;
	servoData[7].Mode = RX1_PWM;
	servoData[7].PPM_in_CH = 8;
	servoData[7].AP_in_CH = 15;
	servoData[7].PWM_LUT_values[0] = 5391;
	servoData[7].PWM_LUT_values[1] = 5700;
	servoData[7].PWM_LUT_values[2] = 8801;
	servoData[7].PWM_CH = 8;
	servoData[7].CAN_LUT_values[0] = 10000;
	servoData[7].CAN_LUT_values[1] = 12000;
	servoData[7].CAN_LUT_values[2] = 14000;
	servoData[7].CAN_ID = 0xFF;


/*ch9 RXM-2 */
	servoData[8].CH_ID = 9;
	servoData[8].Mode = RX1_PWM;
	servoData[8].PPM_in_CH = 3;
	servoData[8].AP_in_CH = 0xFF;
	servoData[8].PWM_LUT_values[0] = 5900;
	servoData[8].PWM_LUT_values[1] = 7900;
	servoData[8].PWM_LUT_values[2] = 9900;
	servoData[8].PWM_CH = 9;
	servoData[8].CAN_LUT_values[0] = 10000;
	servoData[8].CAN_LUT_values[1] = 12000;
	servoData[8].CAN_LUT_values[2] = 14000;
	servoData[8].CAN_ID = 0xFF;


/*ch10 RXM-2 */
	servoData[9].CH_ID = 10;
	servoData[9].Mode = RX2_PWM;
	servoData[9].PPM_in_CH = 3;
	servoData[9].AP_in_CH = 7;
	servoData[9].PWM_LUT_values[0] = 6395;
	servoData[9].PWM_LUT_values[1] = 7770;
	servoData[9].PWM_LUT_values[2] = 9436;
	servoData[9].PWM_CH = 1;
	servoData[9].CAN_LUT_values[0] = 10000;
	servoData[9].CAN_LUT_values[1] = 12000;
	servoData[9].CAN_LUT_values[2] = 14000;
	servoData[9].CAN_ID = 0xFF;


/*ch11 RXM-2 */
	servoData[10].CH_ID = 11;
	servoData[10].Mode = RX2_PWM;
	servoData[10].PPM_in_CH = 2;
	servoData[10].AP_in_CH = 8;
	servoData[10].PWM_LUT_values[0] = 5765;
	servoData[10].PWM_LUT_values[1] = 7460;
	servoData[10].PWM_LUT_values[2] = 8818;
	servoData[10].PWM_CH = 2;
	servoData[10].CAN_LUT_values[0] = 10000;
	servoData[10].CAN_LUT_values[1] = 12000;
	servoData[10].CAN_LUT_values[2] = 14000;
	servoData[10].CAN_ID = 0xFF;


/*ch12 RXM-2 */
	servoData[11].CH_ID = 12;
	servoData[11].Mode = RX2_PWM;
	servoData[11].PPM_in_CH = 6;
	servoData[11].AP_in_CH = 9;
	servoData[11].PWM_LUT_values[0] = 5561;
	servoData[11].PWM_LUT_values[1] = 7020;
	servoData[11].PWM_LUT_values[2] = 9152;
	servoData[11].PWM_CH = 3;
	servoData[11].CAN_LUT_values[0] = 10000;
	servoData[11].CAN_LUT_values[1] = 12000;
	servoData[11].CAN_LUT_values[2] = 14000;
	servoData[11].CAN_ID = 0xFF;


/*ch13 RXM-2 */
	servoData[12].CH_ID = 13;
	servoData[12].Mode = RX2_PWM;
	servoData[12].PPM_in_CH = 5;
	servoData[12].AP_in_CH = 10;
	servoData[12].PWM_LUT_values[0] = 5570;
	servoData[12].PWM_LUT_values[1] = 7680;
	servoData[12].PWM_LUT_values[2] = 9249;
	servoData[12].PWM_CH = 4;
	servoData[12].CAN_LUT_values[0] = 10000;
	servoData[12].CAN_LUT_values[1] = 12000;
	servoData[12].CAN_LUT_values[2] = 14000;
	servoData[12].CAN_ID = 0xFF;


/*ch14 RXM-2 */
	servoData[13].CH_ID = 14;
	servoData[13].Mode = RX2_PWM;
	servoData[13].PPM_in_CH = 12;
	servoData[13].AP_in_CH = 11;
	servoData[13].PWM_LUT_values[0] = 4459;  //itt az rxmux1-ben nem 5-7.5-10 a lut x tngelye
	servoData[13].PWM_LUT_values[1] = 6087;
	servoData[13].PWM_LUT_values[2] = 8437;
	servoData[13].PWM_CH = 5;
	servoData[13].CAN_LUT_values[0] = 10000;
	servoData[13].CAN_LUT_values[1] = 12000;
	servoData[13].CAN_LUT_values[2] = 14000;
	servoData[13].CAN_ID = 0xFF;



/*ch15 RXM-1*/
	servoData[14].CH_ID = 15;
	servoData[14].Mode = RX2_PWM;
	servoData[14].PPM_in_CH = 14;
	servoData[14].AP_in_CH = 12;
	servoData[14].PWM_LUT_values[0] = 10000;
	servoData[14].PWM_LUT_values[1] = 7500;
	servoData[14].PWM_LUT_values[2] = 5000;
	servoData[14].PWM_CH = 6;
	servoData[14].CAN_LUT_values[0] = 10000;
	servoData[14].CAN_LUT_values[1] = 12000;
	servoData[14].CAN_LUT_values[2] = 14000;
	servoData[14].CAN_ID = 0xFF;


/*ch16 RXM-1*/
	servoData[15].CH_ID = 16;
	servoData[15].Mode = RX2_PWM;
	servoData[15].PPM_in_CH = 12;
	servoData[15].AP_in_CH = 13;
	servoData[15].PWM_LUT_values[0] = 5550;
	servoData[15].PWM_LUT_values[1] = 9900;
	servoData[15].PWM_LUT_values[2] = 9900;
	servoData[15].PWM_CH = 10;
	servoData[15].CAN_LUT_values[0] = 10000;
	servoData[15].CAN_LUT_values[1] = 12000;
	servoData[15].CAN_LUT_values[2] = 14000;
	servoData[15].CAN_ID = 0xFF;


/*ch17 RXM-2 */
	servoData[16].CH_ID = 17;
	servoData[16].Mode = RX2_PWM;
	servoData[16].PPM_in_CH = 4;
	servoData[16].AP_in_CH = 16;
	servoData[16].PWM_LUT_values[0] = 5754;
	servoData[16].PWM_LUT_values[1] = 6875;
	servoData[16].PWM_LUT_values[2] = 8280;
	servoData[16].PWM_CH = 8;
	servoData[16].CAN_LUT_values[0] = 10000;
	servoData[16].CAN_LUT_values[1] = 12000;
	servoData[16].CAN_LUT_values[2] = 14000;
	servoData[16].CAN_ID = 0xFF;


/*ch18 RXM-2 */
	servoData[17].CH_ID = 18;
	servoData[17].Mode = RX2_PWM;
	servoData[17].PPM_in_CH = 1;
	servoData[17].AP_in_CH = 17;
	servoData[17].PWM_LUT_values[0] = 6406;
	servoData[17].PWM_LUT_values[1] = 7790;
	servoData[17].PWM_LUT_values[2] = 9012;
	servoData[17].PWM_CH = 9;
	servoData[17].CAN_LUT_values[0] = 10000;
	servoData[17].CAN_LUT_values[1] = 12000;
	servoData[17].CAN_LUT_values[2] = 14000;
	servoData[17].CAN_ID = 0xFF;


/*ch19 RXM-1*/
	servoData[18].CH_ID = 19;
	servoData[18].Mode = RX2_PWM;
	servoData[18].PPM_in_CH = 0;
	servoData[18].AP_in_CH = 18;
	servoData[18].PWM_LUT_values[0] = 5000;
	servoData[18].PWM_LUT_values[1] = 7500;
	servoData[18].PWM_LUT_values[2] = 10000;
	servoData[18].PWM_CH = 12;
	servoData[18].CAN_LUT_values[0] = 10000;
	servoData[18].CAN_LUT_values[1] = 12000;
	servoData[18].CAN_LUT_values[2] = 14000;
	servoData[18].CAN_ID = 0xFF;


/* Unused channels */


/*chxx RXM-1 not used */
	servoData[19].CH_ID = 20;
	servoData[19].Mode = 0xFF;
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


/*chxx RXM-1 not used */
	servoData[20].CH_ID = 21;
	servoData[20].Mode = 0xFF;
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


/*chxx RXM-2 not used*/
	servoData[21].CH_ID = 22;
	servoData[21].Mode = 0xFF;
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

/*chxx RXM-2 not used*/
	servoData[22].CH_ID = 23;
	servoData[22].Mode = 0xFF;
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


/*chxx RXM-2 not used*/
	servoData[23].CH_ID = 24;
	servoData[23].Mode = 0xFF;
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

}
#endif
