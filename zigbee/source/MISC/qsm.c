/*
 * qsm.c
 *	Que Stack Managment
 *  Created on: Sep 17, 2010
 *      Author: mpoppe
 */
#include <stdint.h>
#include "avr/io.h"
#include <frame.h>
#include <misc/qsm.h>
#include <conf_zigbee.h>
#include "MAC/mac.h"

#include "tc.h"
#include "conf_timer.h"
/*
 * Currently the qsm stack is done using an arrary... I did this because i wanted to declare all the static memory
 * locations at the begining... When I create a custome memory malloc and partitions then I will change this to
 * a linked list that asks for new memory when a new item is added to the stack
 */
uint8_t temp;
//Declarations for the size and dimensions of the stack
qsm_t qsm_stack[qsmTYPE][qsmMAXSIZE];
uint8_t num_inStack[qsmTYPE];
uint8_t qsm_end_point[qsmTYPE];

//startup the stack
uint8_t qsm_init(void){
	qsm_status_t status = QSM_SUCCESS;

	tc_set_cca_interrupt_callback(ZIGBEE_MS_TIMER, &qsm_time_interrupt_handler);
	tc_set_cca_interrupt_callback(ZIGBEE_MS_OVERFLOW, &qsm_longTime_interrupt_handler);
	return status;
}

//stop the stack
uint8_t qsm_deinit(void){

	;
}
//Reset the stack and clear it out
void clear_qsm(void){
	qsm_t *qsm;
	for(uint8_t y=0; y<qsmTYPE; y++){
		for(uint8_t x=0; x<qsmMAXSIZE; x++){
			qsm = &qsm_stack[y][x];
			qsm->fp = null;
			qsm->arg = null;
			qsm->time = null;
		}//end for
	}//end for
}//end clear_qsm


void remove_qsm(qsm_type_t type, uint8_t point){
	qsm_shift_left(point, type);

	num_inStack[type]--;
	qsm_end_point[type]--;
}//end remove_qsm




//	TODO:	I want to make change this function in the future.... I would like for it to be called then it returns
//			the next qsm in the stack then the other function will populate the variables then calls the function
//			to add the timer and orgainze the time.
qsm_status_t add_to_time_qsm(void *func, void *argument, uint32_t time){
	qsm_status_t stat = MAC_INIT;
	qsm_t new;
	uint8_t x;
	uint32_t current_time;

	current_time = get_Time();

	new.fp = func;
	new.arg = argument;

	new.time = (current_time + time);



//	TODO: 	I need to add logic to add delay function points both short and long..
//			It needs to also add it in the order it should be executed...

// Check if there is room in the stack then add the function pointer
	if((qsm_roomAvail(QSM_TIME))){

		if(num_inStack[QSM_TIME]>0){

			for(x = 0; x<(num_inStack[QSM_TIME]); x++){
				if(qsm_stack[QSM_TIME][x].time > new.time){
					qsm_shift_right(x, QSM_TIME);
					qsm_stack[QSM_TIME][x] = new;
					if(x == qsmFIRST){
						qsm_time_setup(&new);

					}//end if
					goto jump;
				}//end if

			}//end for
			qsm_stack[QSM_TIME][num_inStack[QSM_TIME]] = new;

		}//end if
		else{
			qsm_stack[QSM_TIME][qsmFIRST] = new;
			qsm_time_setup(&new);

			goto jump;
		}//end else
		jump:

		stat = QSM_SUCCESS;
		num_inStack[QSM_TIME]++;
		//(qsm_stack[QSM_TIME][qsmFIRST].fp)(qsm_stack[QSM_TIME][qsmFIRST].arg);

	}//end if

	else{
		stat = QSM_STACKFULL;
	}

	return stat;
}
qsm_status_t add_to_instant_qsm(void *func, void *argument){
	qsm_status_t stat;
	qsm_t new;

	new.fp = func;
	new.arg = argument;

//	TODO: 	I need to add logic to add delay function points both short and long..
//			It needs to also add it in the order it should be executed...

// Check if there is room in the stack then add the function pointer
	if((qsm_roomAvail(QSM_INSTANT))){

		qsm_stack[QSM_INSTANT][num_inStack[QSM_INSTANT]] = new;
		stat = QSM_SUCCESS;
		num_inStack[QSM_INSTANT]++;
	}

	else{
		stat = QSM_STACKFULL;
	}


	return stat;
}

//Check to see if there is room in the stack for one more
uint8_t qsm_roomAvail(qsm_type_t type){

	if(num_inStack[type] < qsmMAXSIZE){
		return yes;
	}
	else{

		return no;

#ifdef debug
		error("stack is full")
#endif
	}
}// end qsm_roomAvail

/* This function will move all the values in the stack up in the stack after they are dispatched or
 * deleted.
 * Arguments:
 * 	Front: 	is the starting point in the stack you want to move from.
 * 	Back: 	Is the final point in the stack you want to move up.  If the final value in the stack is before the "back"
 * 			it will stop at the end of the stack.
 *
 * Return: nothing
 */

void qsm_shift_left(uint8_t front, qsm_type_t type){
	for(uint8_t x = front; x<qsmMAXSIZE; x++){
		qsm_stack[type][x] = qsm_stack[type][x+1];
	}
}

void qsm_shift_right(uint8_t front, qsm_type_t type){

	for(uint8_t x = num_inStack[type]; x>front; x--){
			qsm_stack[type][x] = qsm_stack[type][x-1];
	}
}
void qsm_dispatch(void){
	bool ready = false;

	for(qsm_type_t x=0; x<qsmTYPE; x++){
		if(num_inStack[x]){
			qsm_t qsm = qsm_stack[x][qsmFIRST];

			switch(x){

			case(QSM_INSTANT):
				ready == true;
			break;

			case(QSM_TIME):
	//			ready = compare_small_tick(qsm.tc);
			break;
			}//EndSwitch

			if(ready){
				(qsm.fp)(qsm.arg);
				remove_qsm(x, qsmFIRST);

			}//EndIf


		}// EndIf
	}//EndFor
}// end qsm_dispatch

void qsm_time_setup(qsm_t *qsm){
	uint16_t long_time;
	uint16_t short_time;
	uint32_t current_time;

	// Longest time delay capable is 4294.967 secs. or 1.19 hrs
	current_time = get_Time();

	short_time = ((uint16_t)(qsm->time));
	long_time = (uint16_t)((qsm->time)>>16);
//	led_on_byte((uint8_t)(short_time));

	TCD0.CCA = short_time;
	TCD1.CCA = long_time;

	if(((uint16_t)(current_time>>16))>= long_time){
		tc_set_cca_interrupt_level(ZIGBEE_MS_TIMER, PMIC_LVL_LOW);

	}//end if
	else{
		tc_set_cca_interrupt_level(ZIGBEE_MS_OVERFLOW, PMIC_LVL_LOW);

	}//end else
}//end qsm_time_setup

void qsm_longTime_interrupt_handler(void)
{
	tc_set_cca_interrupt_level(ZIGBEE_MS_OVERFLOW, 0x00);
	
	qsm_t *temp_qsm = &qsm_stack[QSM_TIME][qsmFIRST];
	TCD0.CCA = ((uint16_t)temp_qsm->time);
	
	tc_set_cca_interrupt_level(ZIGBEE_MS_TIMER, PMIC_LVL_LOW);
}

void qsm_time_interrupt_handler(void){

	tc_set_cca_interrupt_level(ZIGBEE_MS_TIMER, 0x00);
	qsm_t temp_qsm = qsm_stack[QSM_TIME][qsmFIRST];

	remove_qsm(QSM_TIME, qsmFIRST);

	if(num_inStack[QSM_TIME]>0){
//		led_on_bit(0x06);
		qsm_time_setup(&qsm_stack[QSM_TIME][qsmFIRST]);
	}//end if
//	led_on_bit(temp);
//	temp++;

	(temp_qsm.fp)(temp_qsm.arg);

	//else{led_on_bit(0x07);}
}//end qsm_time_interrupt_handler
