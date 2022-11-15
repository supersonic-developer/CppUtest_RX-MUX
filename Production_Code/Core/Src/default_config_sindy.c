/*
 * default_config.c
 *
 *
 *	Ezt eles konfig elott nagyon at kene nezni majd, meg frissiteni
 *
 *  Created on: Oct 4, 2021
 *      Author: fbala
 */

#include "default_config.h"

#if (manual_config_select == 2)

//#include "servo.h"
#include "app.h"
#include "config.h"



void default_config()
{

/*ch1 RXM-1*/
	servoData[0].CH_ID = 1;
	servoData[0].Mode = RXMUX1;
	servoData[0].PPM_in_CH = 10;
	servoData[0].AP_in_CH = 0;
	servoData[0].PWM_LUT_values[0] = 5000;
	servoData[0].PWM_LUT_values[1] = 7500;
	servoData[0].PWM_LUT_values[2] = 10000;
	servoData[0].PWM_CH = 1;
	servoData[0].CAN_LUT_values[0] = 10000;
	servoData[0].CAN_LUT_values[1] = 12000;
	servoData[0].CAN_LUT_values[2] = 14000;
	servoData[0].CAN_ID = 0xff;


/*ch2 RXM-1*/
	servoData[1].CH_ID = 2;
	servoData[1].Mode = RXMUX1;
	servoData[1].PPM_in_CH = 0;
	servoData[1].AP_in_CH = 1;
	servoData[1].PWM_LUT_values[0] = 8901;
	servoData[1].PWM_LUT_values[1] = 7000;
	servoData[1].PWM_LUT_values[2] = 5998;
	servoData[1].PWM_CH = 2;
	servoData[1].CAN_LUT_values[0] = 10000;
	servoData[1].CAN_LUT_values[1] = 12000;
	servoData[1].CAN_LUT_values[2] = 14000;
	servoData[1].CAN_ID = 0xff;


/*ch3 RXM-1*/
	servoData[2].CH_ID = 3;
	servoData[2].Mode = RXMUX1;
	servoData[2].PPM_in_CH = 11;
	servoData[2].AP_in_CH = 2;
	servoData[2].PWM_LUT_values[0] = 9340;
	servoData[2].PWM_LUT_values[1] = 7690;
	servoData[2].PWM_LUT_values[2] = 6064;
	servoData[2].PWM_CH = 3;
	servoData[2].CAN_LUT_values[0] = 10000;
	servoData[2].CAN_LUT_values[1] = 12000;
	servoData[2].CAN_LUT_values[2] = 14000;
	servoData[2].CAN_ID = 0xff;


/*ch4 RXM-1*/
	servoData[3].CH_ID = 4;
	servoData[3].Mode = RXMUX1;
	servoData[3].PPM_in_CH = 12;
	servoData[3].AP_in_CH = 3;
	servoData[3].PWM_LUT_values[0] = 6416;
	servoData[3].PWM_LUT_values[1] = 7700;
	servoData[3].PWM_LUT_values[2] = 9000;
	servoData[3].PWM_CH = 4;
	servoData[3].CAN_LUT_values[0] = 10000;
	servoData[3].CAN_LUT_values[1] = 12000;
	servoData[3].CAN_LUT_values[2] = 14000;
	servoData[3].CAN_ID = 0xff;


/*ch5 RXM-1*/
	servoData[4].CH_ID = 5;
	servoData[4].Mode = RXMUX1;
	servoData[4].PPM_in_CH = 9;
	servoData[4].AP_in_CH = 4;
	servoData[4].PWM_LUT_values[0] = 5632;
	servoData[4].PWM_LUT_values[1] = 7425;
	servoData[4].PWM_LUT_values[2] = 8878;
	servoData[4].PWM_CH = 5;
	servoData[4].CAN_LUT_values[0] = 10000;
	servoData[4].CAN_LUT_values[1] = 12000;
	servoData[4].CAN_LUT_values[2] = 14000;
	servoData[4].CAN_ID = 0xff;


/*ch6 RXM-1*/
	servoData[5].CH_ID = 6;
	servoData[5].Mode = RXMUX1;
	servoData[5].PPM_in_CH = 8;
	servoData[5].AP_in_CH = 5;
	servoData[5].PWM_LUT_values[0] = 5450;
	servoData[5].PWM_LUT_values[1] = 6750;
	servoData[5].PWM_LUT_values[2] = 8404;
	servoData[5].PWM_CH = 6;
	servoData[5].CAN_LUT_values[0] = 10000;
	servoData[5].CAN_LUT_values[1] = 12000;
	servoData[5].CAN_LUT_values[2] = 14000;
	servoData[5].CAN_ID = 0xff;


/*ch7 RXM-1*/  //-not used
	servoData[6].CH_ID = 7;
	servoData[6].Mode = RXMUX1;
	servoData[6].PPM_in_CH = 0xff;
	servoData[6].AP_in_CH = 0xff;
	servoData[6].PWM_LUT_values[0] = 5000;
	servoData[6].PWM_LUT_values[1] = 7500;
	servoData[6].PWM_LUT_values[2] = 7500;
	servoData[6].PWM_CH = 0xff;
	servoData[6].CAN_LUT_values[0] = 10000;
	servoData[6].CAN_LUT_values[1] = 12000;
	servoData[6].CAN_LUT_values[2] = 14000;
	servoData[6].CAN_ID = 0xff;


/*ch8 RXM-2 */
	servoData[7].CH_ID = 8;
	servoData[7].Mode = RXMUX2;
	servoData[7].PPM_in_CH = 10;
	servoData[7].AP_in_CH = 7;
	servoData[7].PWM_LUT_values[0] = 5000;
	servoData[7].PWM_LUT_values[1] = 7500;
	servoData[7].PWM_LUT_values[2] = 10000;
	servoData[7].PWM_CH = 1;
	servoData[7].CAN_LUT_values[0] = 10000;
	servoData[7].CAN_LUT_values[1] = 12000;
	servoData[7].CAN_LUT_values[2] = 14000;
	servoData[7].CAN_ID = 0xff;


/*ch9 RXM-2 */
	servoData[8].CH_ID = 9;
	servoData[8].Mode = RXMUX2;
	servoData[8].PPM_in_CH = 0;
	servoData[8].AP_in_CH = 8;
	servoData[8].PWM_LUT_values[0] = 9056;
	servoData[8].PWM_LUT_values[1] = 7198;
	servoData[8].PWM_LUT_values[2] = 5750;
	servoData[8].PWM_CH = 2;
	servoData[8].CAN_LUT_values[0] = 10000;
	servoData[8].CAN_LUT_values[1] = 12000;
	servoData[8].CAN_LUT_values[2] = 14000;
	servoData[8].CAN_ID = 0xff;


/*ch10 RXM-2 */
	servoData[9].CH_ID = 10;
	servoData[9].Mode = RXMUX2;
	servoData[9].PPM_in_CH = 11;
	servoData[9].AP_in_CH = 9;
	servoData[9].PWM_LUT_values[0] = 5748;
	servoData[9].PWM_LUT_values[1] = 7880;
	servoData[9].PWM_LUT_values[2] = 9530;
	servoData[9].PWM_CH = 3;
	servoData[9].CAN_LUT_values[0] = 10000;
	servoData[9].CAN_LUT_values[1] = 12000;
	servoData[9].CAN_LUT_values[2] = 14000;
	servoData[9].CAN_ID = 0xff;


/*ch11 RXM-2 */
	servoData[10].CH_ID = 11;
	servoData[10].Mode = RXMUX2;
	servoData[10].PPM_in_CH = 12;
	servoData[10].AP_in_CH = 10;
	servoData[10].PWM_LUT_values[0] = 8900;
	servoData[10].PWM_LUT_values[1] = 7750;
	servoData[10].PWM_LUT_values[2] = 6498;
	servoData[10].PWM_CH = 4;
	servoData[10].CAN_LUT_values[0] = 10000;
	servoData[10].CAN_LUT_values[1] = 12000;
	servoData[10].CAN_LUT_values[2] = 14000;
	servoData[10].CAN_ID = 0xff;


/*ch12 RXM-2 */
	servoData[11].CH_ID = 12;
	servoData[11].Mode = RXMUX2;
	servoData[11].PPM_in_CH = 9;
	servoData[11].AP_in_CH = 11;
	servoData[11].PWM_LUT_values[0] = 6151;
	servoData[11].PWM_LUT_values[1] = 7625;
	servoData[11].PWM_LUT_values[2] = 9750;
	servoData[11].PWM_CH = 5;
	servoData[11].CAN_LUT_values[0] = 10000;
	servoData[11].CAN_LUT_values[1] = 12000;
	servoData[11].CAN_LUT_values[2] = 14000;
	servoData[11].CAN_ID = 0xff;


/*ch13 RXM-2 */
	servoData[12].CH_ID = 13;
	servoData[12].Mode = RXMUX2;
	servoData[12].PPM_in_CH = 8;
	servoData[12].AP_in_CH = 12;
	servoData[12].PWM_LUT_values[0] = 8905;
	servoData[12].PWM_LUT_values[1] = 7650;
	servoData[12].PWM_LUT_values[2] = 5836;
	servoData[12].PWM_CH = 6;
	servoData[12].CAN_LUT_values[0] = 10000;
	servoData[12].CAN_LUT_values[1] = 12000;
	servoData[12].CAN_LUT_values[2] = 14000;
	servoData[12].CAN_ID = 0xff;

	/* ----------------------------------   Unused channels ---------------------------------------------- */

/*ch14 RXM-2 */
	servoData[13].CH_ID = 14;
	servoData[13].Mode = RXMUX2;
	servoData[13].PPM_in_CH = 0xff;
	servoData[13].AP_in_CH = 0xff;
	servoData[13].PWM_LUT_values[0] = 5000;
	servoData[13].PWM_LUT_values[1] = 7500;
	servoData[13].PWM_LUT_values[2] = 7500;
	servoData[13].PWM_CH = 0xff;
	servoData[13].CAN_LUT_values[0] = 10000;
	servoData[13].CAN_LUT_values[1] = 12000;
	servoData[13].CAN_LUT_values[2] = 14000;
	servoData[13].CAN_ID = 0xff;




/*ch15 RXM-1*/
	servoData[14].CH_ID = 0xff;
	servoData[14].Mode = RXMUX1;
	servoData[14].PPM_in_CH = 0xff;
	servoData[14].AP_in_CH = 0xff;
	servoData[14].PWM_LUT_values[0] = 5875;
	servoData[14].PWM_LUT_values[1] = 9075;
	servoData[14].PWM_LUT_values[2] = 9345;
	servoData[14].PWM_CH = 0xff;
	servoData[14].CAN_LUT_values[0] = 10000;
	servoData[14].CAN_LUT_values[1] = 12000;
	servoData[14].CAN_LUT_values[2] = 14000;
	servoData[14].CAN_ID = 0xff;


/*ch16 RXM-1*/
	servoData[15].CH_ID = 0xff;
	servoData[15].Mode = RXMUX1;
	servoData[15].PPM_in_CH = 0xff;
	servoData[15].AP_in_CH = 0xff;
	servoData[15].PWM_LUT_values[0] = 5390;
	servoData[15].PWM_LUT_values[1] = 5700;
	servoData[15].PWM_LUT_values[2] = 8800;
	servoData[15].PWM_CH = 0xff;
	servoData[15].CAN_LUT_values[0] = 10000;
	servoData[15].CAN_LUT_values[1] = 12000;
	servoData[15].CAN_LUT_values[2] = 14000;
	servoData[15].CAN_ID = 0xff;


/*ch17 RXM-2 */
	servoData[16].CH_ID = 0xff;
	servoData[16].Mode = RXMUX2;
	servoData[16].PPM_in_CH = 0xff;
	servoData[16].AP_in_CH = 0xff;
	servoData[16].PWM_LUT_values[0] = 5755;
	servoData[16].PWM_LUT_values[1] = 6875;
	servoData[16].PWM_LUT_values[2] = 8280;
	servoData[16].PWM_CH = 0xff;
	servoData[16].CAN_LUT_values[0] = 10000;
	servoData[16].CAN_LUT_values[1] = 12000;
	servoData[16].CAN_LUT_values[2] = 14000;
	servoData[16].CAN_ID = 0xff;


/*ch18 RXM-2 */
	servoData[17].CH_ID = 0xff;
	servoData[17].Mode = RXMUX2;
	servoData[17].PPM_in_CH = 0xff;
	servoData[17].AP_in_CH = 0xff;
	servoData[17].PWM_LUT_values[0] = 6405;
	servoData[17].PWM_LUT_values[1] = 7790;
	servoData[17].PWM_LUT_values[2] = 9010;
	servoData[17].PWM_CH = 0xff;
	servoData[17].CAN_LUT_values[0] = 10000;
	servoData[17].CAN_LUT_values[1] = 12000;
	servoData[17].CAN_LUT_values[2] = 14000;
	servoData[17].CAN_ID = 0xff;


/*ch19 RXM-1*/
	servoData[18].CH_ID = 0xff;
	servoData[18].Mode = RXMUX1;
	servoData[18].PPM_in_CH = 0xff;
	servoData[18].AP_in_CH = 0xff;
	servoData[18].PWM_LUT_values[0] = 5000;
	servoData[18].PWM_LUT_values[1] = 7500;
	servoData[18].PWM_LUT_values[2] = 10000;
	servoData[18].PWM_CH = 0xff;
	servoData[18].CAN_LUT_values[0] = 10000;
	servoData[18].CAN_LUT_values[1] = 12000;
	servoData[18].CAN_LUT_values[2] = 14000;
	servoData[18].CAN_ID = 0xff;





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
	servoData[19].Mode = RXMUX1;


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
	servoData[20].Mode = RXMUX1;


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
	servoData[21].Mode = RXMUX2;

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
	servoData[22].Mode = RXMUX2;


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
	servoData[23].Mode = RXMUX2;

}

#endif
