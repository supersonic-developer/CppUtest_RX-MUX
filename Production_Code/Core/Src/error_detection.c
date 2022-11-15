/*
 * error_detection.c
 *
 *  Created on: 22 Jul 2021
 *      Author: novoz
 */

#include "error_detection.h"
//delete #include "spi.h"

Errors errors;


void DeleteErrorFlag ()
{
	for(int i=0;i<ERROR_Length;i++)
		errors.rawErrorData[i]=0;
}
