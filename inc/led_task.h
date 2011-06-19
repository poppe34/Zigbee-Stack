/*
 * conf_led.h
 *
 *  Created on: Feb 27, 2011
 *      Author: mattpoppe
 */

#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "compiler.h"
#include "task_master.h"

typedef enum ledOperation{
	led_off,
	led_on,
	led_toggle,
	led_status,
	led_report
}ledOperation_t;

void led_task(packet_t *pkt);
uint8_t led_pinNum(U8 num);

#endif /* CONF_LED_H_ */
