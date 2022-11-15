/*
 * dd_config.c
 *
 * This file contains the parameters wwe wish to set at every DD initialization.
 *
 *  Created on: Jan 27, 2022
 *      Author: fbalazs
 */


#include "dd.h"

DD_config_t DD_config = {
		.counter = 0,
		/* normal parameters */
		.param_set[0]  = {0x6083, 0x00 , 0x001E8480},   /* acceleration profile 	*/
		.param_set[1]  = {0x6084, 0x00 , 0x001E8480}, 	/* deceleration profile 	*/
		.param_set[2]  = {0x6081, 0x00 , 0x02625A00},	/* profile velocity 		*/
		.param_set[3]  = {0x607F, 0x00 , 0x02625A00},	/* max profile velocity 	*/

		/* TPDO2 mapping */
		.param_set[4]  = {0x1801, 0x01 , 0x800002FE},   /* 1. Disable TPDO2, COBID 0x2FE (0x280+node ID) 	*/
		.param_set[5]  = {0x1A01, 0x00 , 0x00000000},	/* 2. Clear mapping TPDO2							*/
		.param_set[6]  = {0x1A01, 0x01 , 0x60780010},	/* 3. Set Current actual value, object 0x6078, 16 bit length in sub index 1 of TPDO2 	*/
		.param_set[7]  = {0x1A01, 0x02 , 0x22A30110},	/* 4. Set Temper. actual value, object 0x22A3/1, 16 bit length in sub index 2 of TPDO2 	*/
		.param_set[8]  = {0x1A01, 0x03 , 0x60640020},	/* 5. Set actual position, object 0x6064, 32 bit length in sub index 3 of TPDO2 		*/
		.param_set[9]  = {0x1A01, 0x00 , 0x00000003},	/* 6. Set 2 objects are mapped 						*/
		.param_set[10] = {0x1801, 0x02 , 0x00000001},	/* 7. Set transmission type event specific			*/
		.param_set[11] = {0x1801, 0x01 , 0x000002FE},	/* 8. Enable TPDO2 									*/


		.param_set[12] = {0x0000, 0x00 , 0x00000000},
		.param_set[13] = {0x0000, 0x00 , 0x00000000},
		.param_set[14] = {0x0000, 0x00 , 0x00000000},
		.param_set[15] = {0x0000, 0x00 , 0x00000000},
		.param_set[16] = {0x0000, 0x00 , 0x00000000},
		.param_set[17] = {0x0000, 0x00 , 0x00000000},
		.param_set[18] = {0x0000, 0x00 , 0x00000000},
		.param_set[19] = {0x0000, 0x00 , 0x00000000},
};
