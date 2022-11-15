/*
 * dd.h
 *
 *  Created on: Jan 17, 2022
 *      Author: fbalazs
 */

#ifndef INC_DD_H_
#define INC_DD_H_

#include "CANopen.h"
#include "main.h"

/* real part ---------------------------------------------------- */

//#define DD_CANopen_node_ID 						0x7E
#define RXMUX_CANopen_node_ID 					0x0A

/* DD state machine and object.
 *
 * This is separate from CANopen stuff this is for controlling the DD.
 * The state machine will use the CANopenNode functions to communicate with the DD
 * */

typedef enum __DD_states_t{
	DD_Not_used,
	DD_Offline,
	DD_Not_ready_to_switch_on,
	DD_Switch_on_disabled,
	DD_Switched_on,			/* Official name is "ready to switch on" */
	DD_Motor_on,			/* Official name is "operation enabled" */
	DD_Fault,
}DD_states_t;

typedef struct __DD_config_param_t{
	uint16_t index;
	uint8_t subindex;
	uint32_t value;
}DD_config_param_t;

#define DD_num_of_init_params  20

typedef struct __DD_config_t{
	uint8_t counter;
	DD_config_param_t param_set[DD_num_of_init_params];
}DD_config_t;

/* used to keep track of SDO is up- or downloading. Only used during operation (motor_on state) */
typedef enum __SDO_status_t{
	SDO_download_initiated      = -1,
	SDO_idle 					=  0,
	SDO_upload_initiated		=  1,

}SDO_status_t;

/* enum to keep track of setpoint states when operating with SDO */
typedef enum __New_pos_status_t{
	POS_requested,
	POS_prev_sp_cleared,
	POS_sent,
	POS_idle,
}New_pos_status_t;

/* errors listed here are the ones the code can DEAL with (except unknown) */
typedef enum __DD_erros_t{
	DD_err_none,	/* don't put anything before this */

	DD_err_low_voltage,
	DD_err_failed_to_start_motor,

	DD_err_unknown, /* don't put anything after this */
}DD_erros_t;

typedef struct __DD_object_t {
	DD_states_t 		current_state;
	uint8_t 			state_change_occurred;
	uint8_t				CO_node_ID;
	DD_config_t* 		p_DD_config;

	uint16_t* 			p_DD_status_word;
	int16_t* 			p_DD_actual_current;
	int16_t* 			p_DD_actual_tempr;
	int32_t* 			p_DD_actual_pos;
	float32_t*			p_DD_actual_voltage;

	int32_t 			new_relative_pos;
	New_pos_status_t 	new_pos_wanted;

	uint8_t 			voltage_wanted; 	/* used to keep track of SDO upload every 5ms (can't map PDO to voltage for some reason) */

	SDO_status_t    	SDO_status_own;
	uint8_t 			wait_for_SW;
	uint32_t			timer_value;        /* used for custom timeouts */

	DD_erros_t			last_error;
}DD_object_t;

extern DD_config_t DD_config;
extern DD_object_t DD_object;


CO_ReturnError_t DD_init (void);
void DD_handler(void);
void DD_periodic_handler(void);


FORCE_INLINE uint8_t DD_check_SW(uint16_t mask, uint16_t condition){
	return ((*(DD_object.p_DD_status_word) & mask) == condition);
}


#endif /* INC_DD_H_ */
