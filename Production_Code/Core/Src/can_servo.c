/*
 * can_servo.c
 *
 *  Created on: Jul 19, 2021
 *      Author: fbalazs
 *
 *  Code for handling CAN servos. Specifically "hitechnology MD950TW-CAN"
 *
 *  This code assumes that every connected servo is set to 1000 Kbps baudrate, has its CAN arbitration id set,
 *  is set to use CAN version 2.0A, is in servo_mode, and each servo already has its unique ID set
 *  (I mean the servo id used in it's own protocol, not he can arbitration id)
 *
 *  I designed a CUBE_HAL like structure. Each servo gets its own handle.
 *  This handle contains every parameter, setting, status, command, and diagnostic data relevant to a given servo.
 *  Every control function requires this handle, and gets all the necessary data from it.
 *
 *
 *	For adding a new register, see instructions in can_servo.h
 *
 *	The code assumes that every servo setting and parameter that is not set in the initialization, has already been configured in some other way.
 *	For registers that dont't need save&power rest to take effect (so most of the general settings), the servo works like this:
 *		If you modify the value it instantly takes effect. But if you don't use the save command (writing 0xff into register 0x70),
 *		the servo forgets the change when powered down.
 *		Example:
 *		servo is powered on -> max speed is 500 -> you change it to 1000 -> servo is powered down -> servo is powered on next -> max speed is 500
 *		vs
 *		servo is powered on -> max speed is 500 -> you change it to 1000 -> you save the settings by writing 0xff to 0x70 ->servo is powered down ->
 *		->servo is powered on next -> max speed is 1000
 *
 *	Based on this we decided that the best solution would be to setup all the parameters ahead of time
 *	(some setup is required anyway to set baudrate, CAN arb id, and servo id), change things that are servo specific (limits) during initialization,
 *	and THEN NOT SAVE IT!!!. This way if for some reason, a settings is changed accidently (which on CAN is highly unlikely), it returns to its default
 *	the next time the servo is powered on. Since we are already pushing the servos communications limit, we wouldn't be able to detect
 *	such an error during a flight anyway.
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "can_servo.h"
#include "fifo.h"
#include "can.h"
#include "servo.h"
#include "config.h"

/* Private variables ---------------------------------------------------------*/



uint8_t servoTX_CAN1_FLAG, servoTX_CAN2_FLAG;
uint8_t servoOnCAN1_FLAG = 0;
uint8_t servoOnCAN2_FLAG = 0;
uint8_t diagCounter = 0;

/* Number of CAN servo handles has to be the same as NUM_OF_OUTPUT_CANNELS */
CANServo_Handle hCANservo1;
CANServo_Handle hCANservo2;
CANServo_Handle hCANservo3;
CANServo_Handle hCANservo4;
CANServo_Handle hCANservo5;
CANServo_Handle hCANservo6;
CANServo_Handle hCANservo7;
CANServo_Handle hCANservo8;
CANServo_Handle hCANservo9;
CANServo_Handle hCANservo10;
CANServo_Handle hCANservo11;
CANServo_Handle hCANservo12;

CANServo_Handle* hCANservos[] = {&hCANservo1, &hCANservo2, &hCANservo3, &hCANservo4, &hCANservo5, &hCANservo6, &hCANservo7, &hCANservo8, &hCANservo9, &hCANservo10, &hCANservo11, &hCANservo12};

/* --------------- Private functions -------------- */

/* init functions */
HAL_StatusTypeDef CANServo_comms_check(CANServo_Handle* hservo);
HAL_StatusTypeDef CANServo_write_init_params(CANServo_Handle* hservo);
HAL_StatusTypeDef CANServo_check_init_params(CANServo_Handle* hservo);

/* CAN servo specific incoming message processors */
HAL_StatusTypeDef CANServo_process_incoming_msgs(CANServo_Handle* hservo, uint8_t* reg, uint16_t* data);

/* low level read and write functions */
HAL_StatusTypeDef CANServo_read_reg(CANServo_Handle* hservo, CANServo_reg_typedef reg, CanServoUseBroadcast_Enum broadcast);
HAL_StatusTypeDef CANServo_read_two_regs(CANServo_Handle* hservo, CANServo_reg_typedef reg1, CANServo_reg_typedef reg2, CanServoUseBroadcast_Enum broadcast);
HAL_StatusTypeDef CANServo_write_reg(CANServo_Handle* hservo, CANServo_reg_typedef reg, CanServoUseBroadcast_Enum broadcast);

/* low level crc and other ssupporting functions */
uint8_t Servo_protocol_CRC_5B_calc(uint8_t* array);
uint8_t Servo_protocol_CRC_7B_calc(uint8_t* array);
uint8_t Servo_protocol_CRC_7B_check(uint8_t* array);
//uint8_t CANServo_check_can_id(uint32_t StdId);



/* Copy default values to CANServo_Handle
 *
 * initializes all struct member variables to a default value
 * this function does not intiliazie the servo itself
 */
HAL_StatusTypeDef CANServo_copy_default_setup(CANServo_Handle* hservo)
{
	hservo->can_arb_id = 255;					/* has to be set manually !!!!!!!!!!!*/
	hservo->can_mode = 0;  						/* 0= "2.0A", 1= "2.0B" */
	hservo->status = Comms_Error; 				/* before initialization I check if i can communicate with id */
	hservo->id = 255; 							/* has to be set manually !!!!!!!!!!!*/
	hservo->run_mode = 1; 						/* 0: servo mode, 1: turn mode */
	hservo->init_struct.velocity_max = 4095;	/* min:0 max:4095, pos/100msec */  //512 kellemes
	hservo->init_struct.pos_max_limit = 16300; 	/* if exceeded, new_position command will not take effect. min:0 max:16383 (=0x3FFF) */
	hservo->init_struct.pos_min_limit = 84; 	/* if exceeded, new_position command will not take effect. min:0 max:16383 */
												/* Note for pos_max/min_limit: the 0 and 16383 are defined by the protocol, according to the
												 * data sheet of the MD950TW-CAN servo, travel is between -178° (reg_value = 84)
												 * 	and +178° (reg_value = 16300)
												 */

	hservo->init_struct.initCounter = 0;



	return HAL_OK;
}



/* control functions  --------------------------------------------------------*/

/*
 * Function for initializing a servo. Each servo has its status (hservo->status) set to Comms_Error by default,
 * the functions called in this function should change it to Uninitialized, than Servo_Normal
 * if everything is okay.
 */
HAL_StatusTypeDef CANServo_init(CANServo_Handle* hservo)
{
	HAL_StatusTypeDef status;

	/* check if we can communicate with servo */
	status = CANServo_comms_check(hservo);
	if (status != HAL_OK) 						/*status can be error or timeout */
	{
		return status;
	}

	/* write init data */
	if (CANServo_write_init_params(hservo) != HAL_OK) 		/*status can be error or timeout */
	{														/* writes all registers with 1 call*/
		return HAL_ERROR;
	}

	/*read back init data */
	status = CANServo_check_init_params(hservo);   	/* checks the registers 1-by-1 with each call, hence the while() */
													//ezen is lehet majd finomitani, errorok tekinteteben
	if (status!= HAL_OK)
	{
		return status;
	}


#ifdef not
	//debug egyszeri lekerdezes/iras-----------------------------------------

	//lekerdezes
	//CANServo_read_reg(&hCANservo1, curr_position_reg, own_id);
	//transmit_servo_msg_queue_CAN1();
	//CAN1_process_incoming_msgs();

	//iras

	/* custom message frame */
	CANServoTxMsg_Struct msg;

	/* Servo protocol frame, the data part  of the can frame */
	msg.data[0] = 0x96;			/* header*/
	msg.data[1] = 0x01;			/* servo id */
	msg.data[2] = 0x46;			/* register 1 */
	msg.data[3] = 0x02;   		/* length */

	/* select what data should be transmitted */
	//uint16_t data = hCANservo1.diagn_struct.current_pos - 10;


	/*make it little endian */
	msg.data[4] = 0;			//data & 0xff;
	msg.data[5] = 0b00000010; 	//(data>>8) & 0xff;

	msg.data[6] = Servo_protocol_CRC_7B_calc(msg.data);  /* calculate and write crc byte (txData[6]) */

	/*the rest of custom message, the CAN frame */
	msg.can_StdId = hservo->can_arb_id;
	msg.can_DLC = 7;

	/* end of custom message frame */

	/* add it to the queue */
	pushCANs(&CAN1_tx_msg_fifo, msg);

	/*set the falg to indicate that the tx msg fifo is not empty */
	servoTX_CAN1_FLAG = 1;
	transmit_servo_msg_queue_CAN1();

	HAL_Delay(100);
	//lekerdezes
	CANServo_read_reg(&hCANservo1, 0x48, own_id);

	transmit_servo_msg_queue_CAN1();

	//while(1);

	//------------------------------------------------------------------------
#endif

	return HAL_OK;
}

/*
 * Check if we can communicate with a servo.
 * This is done by checking servo id, and run mode
 * and of course the validity of the two message frames
 */
HAL_StatusTypeDef CANServo_comms_check(CANServo_Handle* hservo)
{
	/* Get tick for timeout*/
	uint32_t tickstart = HAL_GetTick();

	/* wait until we run into timeout (or until we confirmed comms)*/
	while( (HAL_GetTick() - tickstart) < servo_comms_check_timeout_value)
	{
		if (CANServo_read_reg(hservo, id_reg, own_id) == HAL_ERROR)
			return HAL_ERROR;
		if (CANServo_read_reg(hservo, run_mode_reg, own_id) == HAL_ERROR)
			return HAL_ERROR;

		/* transmit messages */
		/* can't use while() here, beacues if there is nothing on the bus to ack
		 * messages the mailbxes will never free up and the program halts */

		CANx_transmit_servo_msg_queue(&hcan1);
		CANx_transmit_servo_msg_queue(&hcan2);


		/* leave time for the servo to respond. */
		HAL_Delay(10);

		CANx_process_incoming_msgs(&hcan1);
		CANx_process_incoming_msgs(&hcan2);
		if(hservo->init_struct.initCounter >= 2)
		{
			hservo->status = Uninitialized;
			hservo->init_struct.initCounter = 0;
			return HAL_OK;
		}
	}

	return HAL_TIMEOUT;

}

/*
 * we write all the parameters to the servo,
 * with the next function we read them back
 * to make sure they are correct
 */
HAL_StatusTypeDef CANServo_write_init_params(CANServo_Handle* hservo)
{
	uint8_t counter = 0;
	while(counter <= 2)
	{
		CANServo_reg_typedef reg = 0;
		switch(counter)
		{
		case 0:
			reg = pos_max_limit_reg;
			break;

		case 1:
			reg = pos_min_limit_reg;
			break;

		case 2:
			reg = velocity_max_reg;
			break;

		}
		if(CANServo_write_reg(hservo, reg, own_id) != HAL_OK)
		{
			return HAL_ERROR;
		}
		counter++;
	}

	/* actually transmit messages */
	while (servoTX_CAN1_FLAG)
	{
		if (CANx_transmit_servo_msg_queue(&hcan1) == HAL_ERROR)  /*could be HAL_BUSY */
		{
			return HAL_ERROR;
		}
	}
	while (servoTX_CAN2_FLAG)
	{
		if (CANx_transmit_servo_msg_queue(&hcan2) == HAL_ERROR)  /*could be HAL_BUSY */
		{
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

/* we send out the all the parameters in CANServo_init()
 * after that we read out the parameters 1 by 1 (this function), and when they come back,
 * we check if it is actually the one we set and we increase the counter
 *  (this is done in CANServo_process_incoming_msgs())
 */
HAL_StatusTypeDef CANServo_check_init_params(CANServo_Handle* hservo)
{
	uint32_t tickstart = HAL_GetTick(); /* get tick for timeout */
	while(hservo->status == Uninitialized && (HAL_GetTick() - tickstart) < servo_inti_timeout_value)
	{
		if(hservo->status == Uninitialized)
		{
			CANServo_reg_typedef reg = 0;
			switch(hservo->init_struct.initCounter)
			{
			case 0:
				reg = pos_max_limit_reg;
				break;

			case 1:
				reg = pos_min_limit_reg;
				break;

			case 2:
				reg = velocity_max_reg; 	/*note: if you add more items to to initialisation you might have to increase "servo_inti_timeout_value" */
				break;

			/* if we get this far the servo is initialized */
			case 3:
				hservo->status = Servo_Normal;
				break;

			}

			/* if we selected a register, send out the request */
			if (reg)
			{
				if(CANServo_read_reg(hservo, reg, own_id) != HAL_OK)
				{
					return HAL_ERROR;
				}
			}

			/* transmit messages */
			while (servoTX_CAN1_FLAG)
			{
				if(CANx_transmit_servo_msg_queue(&hcan1) == HAL_ERROR)  	/*could be HAL_BUSY */
				{
					return HAL_ERROR;
				}
			}
			while (servoTX_CAN2_FLAG)
			{
				if (CANx_transmit_servo_msg_queue(&hcan2) == HAL_ERROR)  /*could be HAL_BUSY */
				{
					return HAL_ERROR;
				}
			}

			/* wait for the servo to respond, then process the response */
			HAL_Delay(5); 							/* if we create a system wide timing, this can be removed */
			CANx_process_incoming_msgs(&hcan1); 	/* if we create a system wide timing, this can be moved to a fixed period it/callback */
			CANx_process_incoming_msgs(&hcan2); 	/* if we create a system wide timing, this can be moved to a fixed period it/callback */
		}
	}

	/* if it timed out, set status */
	if (hservo->status == Uninitialized)
	{
		hservo->status = Error;
	}

	return HAL_OK;
}


/*
 * Function for sending out new position information to servo.
 * We have decided to use broadcast CAN id for all servos,
 * but servo commands should be still called individually.
 */
HAL_StatusTypeDef CANServo_cmd(CANServo_Handle* hservo)
{
	HAL_StatusTypeDef status;

	status = CANServo_write_reg(hservo, new_pos_reg, can_broadcast);
	if(status != HAL_OK)
	{
		return status;
	}

	/* ....
	status = CANServo_write_reg(hservo, hservo->cmd_struct.nex_item);
	if(status != HAL_OK)
	{
		return status;
	}*/

	return HAL_OK;
}


/*
 * Function for reading registers containing diagnostics data
 * The servos answer is interpreted in CANServo_process_incoming_msgs()
 *
 * With testing I determined the maximum rate at which we can both send commands, and receive data from servo reliably.
 * The maximum is 1 command and 1 double register read command, every 5ms (200Hz). (The servo protocol defines a "custom" format where,
 *  you can request data from 2 registers in 1 CAN message, and the servo returns the 2 values in another can message )
 * The servo-s built in "stream mode" (when it automatically sends back selected information, without the need to request it)
 * 	is unusable above ~10-15 Hz (while new position commands are going out at 200Hz)
 *
 * Based on this, my solution is that we request 2 values in each cycle.
 * One is always the current position, the other is alternating between voltage and MCU temperature. (Or any other register we add later)
 */
HAL_StatusTypeDef CANServo_diag()
{
	CANServo_reg_typedef reg1, reg2;
	FIFO_Status 		 status1 = FIFO_OK;
	FIFO_Status 		 status2 = FIFO_OK;

	/* set register */
	reg1 = curr_position_reg;

	if (diagCounter == 0){
		reg2 = voltage_reg;
	}
	if (diagCounter == 1){
		reg2 = mcu_temp_reg;
	}

	/* increase counter */
	diagCounter += 1;
	if (diagCounter == 2)
	{
		diagCounter = 0;
	}


	/* create CAN message */
	CANServoTxMsg_Struct msg;

	/* Servo protocol frame, the data part  of the can frame */
	msg.data[0] = 0x52;			/* header, for double read*/
	msg.data[1] = 0x00;		/* broadcast servo id */
	msg.data[2] = reg1;			/* register 1 */
	msg.data[3] = reg2;   		/* register 2 */

	/*rest of the CAN frame */
	msg.can_StdId = 0x0; 		/* broadcast CAN id */
	msg.can_DLC = 4;

	/* end of custom message frame */

	/* add it to CAN1 queue if needed */
	if (servoOnCAN1_FLAG)
	{
		status1 = pushCANs(&CAN1_tx_msg_fifo, msg);
		if (status1 == FIFO_OK ){
			/*set the flag to indicate that the tx msg fifo is not empty */
			servoTX_CAN1_FLAG = 1;
		}
	}

	/* add it to CAN2 queue if needed */
	if (servoOnCAN2_FLAG)
	{
		status2 = pushCANs(&CAN2_tx_msg_fifo, msg);
		if (status2 == FIFO_OK){
			/*set the flag to indicate that the tx msg fifo is not empty */
			servoTX_CAN2_FLAG = 1;
		}
	}

	if  ( status1 != FIFO_OK || status2 != FIFO_OK ){
		return HAL_ERROR;
	}


	return HAL_OK;

}

/*
 * Handles incoming CAN messages.
 * If it is a valid servo message, it forwards it to the addressed servo with CANServo_process_incoming_msgs().
 * This function anticipates two kinds of messages. "Normal Read response from servo" (data from 1 register)
 * or "Custom Read Response from servo (2 Address Data)" (data from 2 registers in one message)
 */
HAL_StatusTypeDef CANx_process_incoming_msgs(CAN_HandleTypeDef* hcan)
{
	uint8_t* pFlag;


	if(hcan->Instance == hcan1.Instance){
		pFlag = &CAN1_Flag_RxPending;
	}
	else if(hcan->Instance == hcan2.Instance){
		pFlag = &CAN2_Flag_RxPending;
	}
	else{
		return HAL_ERROR;
	}



	if(*pFlag)
	{
		while(HAL_CAN_GetRxFifoFillLevel(hcan,CAN_RX_FIFO0) > 0)
		{
			/* get the message */
			CAN_RxHeaderTypeDef rxHeader;
			uint8_t rxData[8];
			if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK)
			{
				/* Reception Error */
				//Error_Handler();
				return HAL_ERROR;
			}

			/* check if its a valid message from a servo */
			/*---------------------------- begin ------------------------------------------------- */

			uint8_t msg_type = 0;  /* 1= "custom read, 2 address Data", 2= "normal read" */
			uint16_t data1 = 0;
			uint16_t data2 = 0;

			/* we received a message containing data from 2 registers */
			if (rxHeader.DLC == 8 && /*CANServo_check_can_id(rxHeader.StdId) &&*/ rxData[0] == 0x56)
			{
				msg_type = 1;
				data1 = rxData[3] | rxData[4] << 8;
				data2 = rxData[6] | rxData[7] << 8;
			}

			/* we received a message containing data from 1 register */
			else if (rxHeader.DLC == 7 && /*CANServo_check_can_id(rxHeader.StdId) &&*/ rxData[0] == 0x69 && Servo_protocol_CRC_7B_check(rxData))
			{
				msg_type = 2;
				data1 = rxData[4] | rxData[5] << 8;
			}
			/* ---------------------------- end -------------------------------------------------- */



			/* if it was a valid servo msg */
			if (msg_type == 1 || msg_type == 2)
			{
				/* check which servo was it for */

				CANServo_Handle* hservo_local;
				for (uint8_t idx=0; idx < NUM_OF_OUTPUT_CHANNELS; idx++ )
				{
					if (rxData[1] == hCANservos[idx]->id)       /* servo1 */
					{
						hservo_local = hCANservos[idx];
					}
				}

				/*based on what msg we got, we have to process data from 1 or 2 registers */
				if (msg_type == 1)
				{
					CANServo_process_incoming_msgs(hservo_local, &rxData[2] ,&data1);
					CANServo_process_incoming_msgs(hservo_local, &rxData[5] ,&data2);

				}
				else  /* msg_type == 2 */
				{
					CANServo_process_incoming_msgs(hservo_local, &rxData[2] ,&data1);
				}
			}
		}

		/* deactivate CAN incoming msg flag, reactivate callback */
		*pFlag = 0;
		if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
		{
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}


HAL_StatusTypeDef CANServo_process_incoming_msgs(CANServo_Handle* hservo, uint8_t* reg, uint16_t* data)
{
	/*check each mode: normal(diagnostics), comms_check, init */

	/* if we are in normal mode the data coming back should be for diagnostics */
	if (hservo->status == Servo_Normal )
	{
		switch (*reg)
		{
		case mcu_temp_reg:
			hservo->diagn_struct.mcu_temp = *data;
			break;

		case voltage_reg:
			hservo->diagn_struct.voltage = *data;
			break;

		case curr_position_reg:
			hservo->diagn_struct.current_pos = *data;
			break;

		}

		return HAL_OK;
	}

	/* if we are in the initialization process, check if each parameter matches with the value we set */
	if (hservo->status == Uninitialized)
	{
		uint8_t match = 0;

		/* switch based on the register */
		switch (*reg)
		{
		case pos_max_limit_reg:
			if (hservo->init_struct.pos_max_limit == *data)
				match = 1;
			break;

		case pos_min_limit_reg:
			if (hservo->init_struct.pos_min_limit == *data)
				match = 1;
			break;


		case velocity_max_reg:
			if (hservo->init_struct.velocity_max == *data)
				match = 1;
			break;

		}
		/* if the received setting matches the one we wanted we step onto the next one */
		if (match)
		{
			hservo->init_struct.initCounter += 1;
		}

		return HAL_OK;
	}

	/* if we are in comms_chechk mode, we check if id and run_mode are correct
	 * (This part uses hservo->init_struct.initCounter but strictly speaking it shouldn't
	 * as this is not initialization by my terminology. I don't want to add another struct member tho)
	 */
	if (hservo->status == Comms_Error)
	{
		/* switch based on the register */
		switch (*reg)
		{
		case id_reg:
			if (hservo->id == *data && hservo->init_struct.initCounter == 0)
				hservo->init_struct.initCounter += 1;
			break;

		case run_mode_reg:
			if (hservo->run_mode == *data && hservo->init_struct.initCounter == 1)
				hservo->init_struct.initCounter += 1;
			break;
		}

		return HAL_OK;
	}

	/* we only get to here if the servo is in error state */
	return HAL_ERROR;
}


/*
 * This function transmits the address of the register that we want to read, than the
 * CANServo_process_incoming_msgs() function processes the answer
 */
HAL_StatusTypeDef CANServo_read_reg(CANServo_Handle* hservo, CANServo_reg_typedef reg, CanServoUseBroadcast_Enum broadcast)
{
	/* custom message frame */
	CANServoTxMsg_Struct msg;

	/* Servo protocol frame, aka the data part of the can frame */
	msg.data[0] = 0x96;			/* header */
	msg.data[1] = hservo->id;	/* servo id */
	msg.data[2] = reg;			/* register to adress */
	msg.data[3] = 0x00;   		/* length */
	msg.data[4] = Servo_protocol_CRC_5B_calc(msg.data);  /* calculate and write crc byte (data[4]) */

	/*rest of the CAN frame */
	msg.can_StdId = hservo->can_arb_id;
	msg.can_DLC = 5;

	/* If we want to send read with broadcast, change servo id */
	if (broadcast != own_id)
	{
		msg.can_StdId = 0x00;
		if (broadcast == can_and_servo_broadcast)
		{
			msg.data[1] = 0x00;	/* servo id */
		}
	}

	/* end of custom message frame */

	/* add it to the appropriate queue */
	if (hservo->assigned_can == 1)
	{
		if (pushCANs(&CAN1_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN1_FLAG = 1;
	}
	else if (hservo->assigned_can == 2)
	{
		if (pushCANs(&CAN2_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN2_FLAG = 1;
	}

	return HAL_OK;
}

/*
 * request two registers from servo in one can message
 * (same as previous function, slightly different servo frame)
 */
HAL_StatusTypeDef CANServo_read_two_regs(CANServo_Handle* hservo, CANServo_reg_typedef reg1, CANServo_reg_typedef reg2, CanServoUseBroadcast_Enum broadcast)
{

	/* custom message frame */
	CANServoTxMsg_Struct msg;

	/* Servo protocol frame, the data part  of the can frame */
	msg.data[0] = 0x52;			/* header, for double read*/
	msg.data[1] = hservo->id;	/* servo id */
	msg.data[2] = reg1;			/* register 1 */
	msg.data[3] = reg2;   		/* register 2 */

	/*rest of the CAN frame */
	msg.can_StdId = hservo->can_arb_id;
	msg.can_DLC = 4;

	/* If we want to send read with broadcast, change it */
	if (broadcast != own_id)
	{
		msg.can_StdId = 0x00;
		if (broadcast == can_and_servo_broadcast)
		{
			msg.data[1] = 0x00;	/* servo id */
		}
	}

	/* end of custom message frame */

	/* add it to the appropriate queue */
	if (hservo->assigned_can == 1)
	{
		if (pushCANs(&CAN1_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN1_FLAG = 1;
	}
	else if (hservo->assigned_can == 2)
	{
		if (pushCANs(&CAN2_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN2_FLAG = 1;
	}

	return HAL_OK;
}

HAL_StatusTypeDef CANServo_write_reg(CANServo_Handle* hservo, CANServo_reg_typedef reg, CanServoUseBroadcast_Enum broadcast)
{
	/* custom message frame */
	CANServoTxMsg_Struct msg;

	/* Servo protocol frame, the data part  of the can frame */
	msg.data[0] = 0x96;			/* header*/
	msg.data[1] = hservo->id;	/* servo id */
	msg.data[2] = reg;			/* register 1 */
	msg.data[3] = 0x02;   		/* length */

	/* select what data should be transmitted */
	uint16_t data;

	/* switch based on registers
	 * only R/W registers should be listed here
	 * for R and R/W +S registers use  CANServo_read_reg()
	 */
	switch (reg)
	{
	case pos_max_limit_reg:
		data = hservo->init_struct.pos_max_limit;
		break;

	case pos_min_limit_reg:
		data = hservo->init_struct.pos_min_limit;
		break;

	case velocity_max_reg:
		data = hservo->init_struct.velocity_max;
		break;

	case new_pos_reg:
		data = hservo->cmd_struct.new_pos;
		break;

	case power_config_reg:
		data = hservo->cmd_struct.e_stop;
		break;

	default:
		return HAL_ERROR;  /*if we try to address not writable register */
	}

	/*make it little endian */
	msg.data[4] = data & 0xff;
	msg.data[5] = (data>>8) & 0xff;

	msg.data[6] = Servo_protocol_CRC_7B_calc(msg.data);  /* calculate and write crc byte (txData[6]) */

	/*The rest of custom message, the CAN frame */
	msg.can_StdId = hservo->can_arb_id;
	msg.can_DLC = 7;

	/* If we want to send write with broadcast, change it */
	if (broadcast != own_id)
	{
		msg.can_StdId = 0x00;
		if (broadcast == can_and_servo_broadcast)
		{
			msg.data[1] = 0x00;	/* servo id */
		}
	}

	/* end of custom message frame */

	/* add it to the appropriate queue */
	if (hservo->assigned_can == 1)
	{
		if (pushCANs(&CAN1_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN1_FLAG = 1;
	}
	else if (hservo->assigned_can == 2)
	{
		if (pushCANs(&CAN2_tx_msg_fifo, msg) != FIFO_OK)
		{
			return HAL_ERROR;
		}

		/*set the flag to indicate that the tx msg fifo is not empty */
		servoTX_CAN2_FLAG = 1;
	}

	return HAL_OK;

}




/* low level transmit functions and crc functions functions --------------------------*/


/* Function to fill up all empty CAN txMailboxes (there are 3) with messages from the outgoing message FIFO
 *
 * Returns after the messages were put in the mailboxes,
 * even if there are more messages in the FIFO, so has to be
 * called repeatedly if you have more messages in the FIFO
 *
 */
HAL_StatusTypeDef CANx_transmit_servo_msg_queue(CAN_HandleTypeDef* hcan)
{
	//debug
	//HAL_GPIO_WritePin(user_gpio_GPIO_Port, user_gpio_Pin, GPIO_PIN_SET);

	uint8_t freeTxMalboxes = (uint8_t)HAL_CAN_GetTxMailboxesFreeLevel(hcan);  /* max return number is 3 so no need for 32bit */
	uint8_t msgs_to_send;

	/* if CAN TxMailboxes are already full, just leave */
	if(freeTxMalboxes == 0)
	{
		return HAL_BUSY;
	}

	/* get appropriate fifo */
	FIFO_CAN_S_MSG* fifo = NULL;
	uint8_t* pTXFlag = NULL;
	if(hcan->Instance == hcan1.Instance){
		fifo = &CAN1_tx_msg_fifo;
		pTXFlag = &servoTX_CAN1_FLAG;
	}
	else if(hcan->Instance == hcan2.Instance){
		fifo = &CAN2_tx_msg_fifo;
		pTXFlag = &servoTX_CAN2_FLAG;
	}
	else{
		return HAL_ERROR;
	}

	/* determine how many msgs to put in the mailboxes */
	if(fifoLenCANs(fifo) >= freeTxMalboxes)
	{
		msgs_to_send = freeTxMalboxes;
	}
	else
	{
		msgs_to_send = fifoLenCANs(fifo);
	}

	/* actually put the msgs in the mailboxes */
	for (uint8_t i=0; i<msgs_to_send;i++)
	{
		if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) > 0)
		{
			/* get message from fifo */
			CANServoTxMsg_Struct msg;
			popCANs(fifo, &msg);
			/*configure the CAN tx header */

			CAN_TxHeaderTypeDef txHeader;
			txHeader.DLC = msg.can_DLC;
			txHeader.StdId = msg.can_StdId;
			txHeader.IDE = CAN_ID_STD;
			txHeader.RTR = CAN_RTR_DATA;

			uint32_t TxMailbox;

			/* actually transmit the data */
			if(HAL_CAN_AddTxMessage(hcan, &txHeader, msg.data, &TxMailbox ) != HAL_OK)
			{
				return HAL_ERROR;
			}
		}
	}

	//debug
	//HAL_GPIO_WritePin(user_gpio_GPIO_Port, user_gpio_Pin, GPIO_PIN_RESET);

	if(fifoIsEmptyCANs(fifo))
	{
		*pTXFlag = 0;
	}
	return HAL_OK;
}


FORCE_INLINE uint8_t Servo_protocol_CRC_5B_calc(uint8_t* array)
{
	return (uint8_t)(array[1] +  array[2] + array[3]);

}

FORCE_INLINE uint8_t Servo_protocol_CRC_7B_calc(uint8_t* array)
{
	return (uint8_t)(array[1] +  array[2] + array[3] + array[4] + array[5]);

}

FORCE_INLINE uint8_t Servo_protocol_CRC_7B_check(uint8_t* array)
{
	if (array[6] == (uint8_t)(array[1] +  array[2] + array[3] + array[4] + array[5]))
	{
		return 1;
	}

	return 0;

}
