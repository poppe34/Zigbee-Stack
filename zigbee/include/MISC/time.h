/*
 * time.h
 *
 * Created: 4/19/2011 2:31:51 PM
 *  Author: mpoppe
 */ 


#ifndef TIME_H_
#define TIME_H_

#include "compiler.h"
#include "tc.h"

#include "conf_zigbee.h"
#include "conf_timer.h"


void time_init(void);
void delay_us(uint16_t);
void start_short_time(void);
void start_long_time(void);
void start_ticks(void);
uint32_t get_Time(void);
uint16_t get_Ticks(void);
void timer_irqHandler(void);
uint32_t Symbols_to_Time(uint32_t symbols);

#endif /* TIME_H_ */