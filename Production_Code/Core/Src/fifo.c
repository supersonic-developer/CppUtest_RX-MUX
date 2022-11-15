/*
 * fifo.c
 *
 *  Created on: Sep 25, 2020
 *      Author: andkovac
 *
 *      As of commit 0a538540, 8bit fifos are not used in the project at all, 32bit fifo is used
 *      in PPM handle (but PPM handle is not called at all) (I've checked all 3 branches)
 *      FIFO_CAN_S_MSG type fifos are freshly added. The implementation was copied from 8bit fifo, that was already in the project.
 *
 *      Be aware that this implementation only works with SIZEs that are POWERS OF 2.
 *      The setup I found IGNORED it, and used 20 and 80 for length. I've tried to use 20 for the CAN messages fifo,
 *      but it worked in a seemingly random way.
 */
#include "fifo.h"

/*------------------------32 bit---------------------------*/

uint8_t fifoIsEmpty32(FIFO32 * fifo)
{
     return fifo->in == fifo->out;
}

uint8_t fifoIsFull32(FIFO32 * fifo)
{
     return (fifo->in - fifo->out) > fifo->mask;
}

FIFO_Status push32(FIFO32 * fifo, uint32_t data) {

	if(fifoIsFull32(fifo)) {
		return FIFO_FULL;
	}
	else {
		fifo->data[fifo->in & fifo->mask] = data;
		fifo->in++;
		return FIFO_OK;
	}
}

FIFO_Status pop32(FIFO32 * fifo, uint32_t * data)
{
		if(fifoIsEmpty32(fifo)) {
			return FIFO_EMPTY;
		} else {
			*data = fifo->data[fifo->out & fifo->mask];
			fifo->out++;
			return FIFO_OK;
		}
}

/*------------------------8 bit (currently not used)------------------*/
uint8_t fifoIsEmpty8(FIFO8 * fifo)
{
     return fifo->in == fifo->out;
}

uint8_t fifoIsFull8(FIFO8 * fifo)
{
     return (fifo->in - fifo->out) > fifo->mask;
}

FIFO_Status push8(FIFO8 * fifo, uint8_t data) {

	if(fifoIsFull8(fifo)) {
		return FIFO_FULL;
	}
	else {
		fifo->data[fifo->in & fifo->mask] = data;
		fifo->in++;
		return FIFO_OK;
	}
}

FIFO_Status pop8(FIFO8 * fifo, uint8_t * data)
{
		if(fifoIsEmpty8(fifo)) {
			return FIFO_EMPTY;
		} else {
			*data = fifo->data[fifo->out & fifo->mask];
			fifo->out++;
			return FIFO_OK;
		}
}

uint8_t fifoUnused8(FIFO8* fifo)
{
	return (fifo->mask + 1) - (fifo->in - fifo->out);
}

uint8_t fifoLen8(FIFO8* fifo)
{
	return (fifo->in - fifo->out);
}

/*------------------------CAN servo msg---------------------------*/

uint8_t fifoIsEmptyCANs(FIFO_CAN_S_MSG * fifo)
{
     return fifo->in == fifo->out;
}

uint8_t fifoIsFullCANs(FIFO_CAN_S_MSG * fifo)
{
     return (fifo->in - fifo->out) > fifo->mask;
}

FIFO_Status pushCANs(FIFO_CAN_S_MSG* fifo, CANServoTxMsg_Struct data)
{

	if(fifoIsFullCANs(fifo)) {
		return FIFO_FULL;
	}
	else {
		fifo->data[fifo->in & fifo->mask] = data;
		fifo->in++;
		return FIFO_OK;
	}
}

FIFO_Status popCANs(FIFO_CAN_S_MSG* fifo, CANServoTxMsg_Struct* data)
{
		if(fifoIsEmptyCANs(fifo)) {
			return FIFO_EMPTY;
		} else {
			*data = fifo->data[fifo->out & fifo->mask];
			fifo->out++;
			return FIFO_OK;
		}
}

uint8_t fifoUnusedCANs(FIFO_CAN_S_MSG* fifo)
{
	return (fifo->mask + 1) - (fifo->in - fifo->out);
}

uint8_t fifoLenCANs(FIFO_CAN_S_MSG* fifo)
{
	return (fifo->in - fifo->out);
}


/*------------------------FIFO instances (currently only RC1 and RC2 might be used)--------------------------*/

FIFO32 fifo1;
FIFO32 fifo2;
FIFO8 fifo3;

void FIFO_Init() {

	fifo1.in = 0;
	fifo1.out = 0;
	fifo1.mask = MAX_FIFO_SIZE_U32 - 1;

	fifo2.in = 0;
	fifo2.out = 0;
	fifo2.mask = MAX_FIFO_SIZE_U32 - 1;

	fifo3.in = 0;
	fifo3.out = 0;
	fifo3.mask = MAX_FIFO_SIZE_U8 - 1;

}

FIFO_Status FIFO_Push32(FIFO_Id id, uint32_t data) {
	switch(id) {
		case FIFO_RC1:
			return (push32(&fifo1,data));
		case FIFO_RC2:
			return (push32(&fifo2,data));
		case FIFO_EXBUS:
			return FIFO_ERROR;
	}
	return FIFO_ERROR;
}

FIFO_Status FIFO_Pop32(FIFO_Id id, uint32_t* data) {
	switch(id) {
		case FIFO_RC1:
			return (pop32(&fifo1,data));
		case FIFO_RC2:
			return (pop32(&fifo2,data));
		case FIFO_EXBUS:
			return FIFO_ERROR;
	}
	return FIFO_ERROR;
}

FIFO_Status FIFO_Push8(FIFO_Id id, uint8_t data) {
	switch(id) {
		case FIFO_RC1:
			return FIFO_ERROR;
		case FIFO_RC2:
			return FIFO_ERROR;
		case FIFO_EXBUS:
			return (push8(&fifo3,data));
	}
	return FIFO_ERROR;
}

FIFO_Status FIFO_Pop8(FIFO_Id id, uint8_t* data) {
	switch(id) {
		case FIFO_RC1:
			return FIFO_ERROR;
		case FIFO_RC2:
			return FIFO_ERROR;
		case FIFO_EXBUS:
			return (pop8(&fifo3,data));
	}
	return FIFO_ERROR;
}


