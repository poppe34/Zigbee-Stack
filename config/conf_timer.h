/*
 * conf_timer.h
 *
 * Created: 4/21/2011 4:30:05 PM
 *  Author: mpoppe
 */ 


#ifndef CONF_TIMER_H_
#define CONF_TIMER_H_

#include "compiler.h"

#define ZIGBEE_TICK_TIMER	    &TCC0
#define ZIGBEE_TICK_RESOLUTION  62500UL

#define ZIGBEE_MS_OVERFLOW      &TCD1
#define ZIGBEE_MS_TIMER		    &TCD0
#define ZIGBEE_MS_RESOLUTION    1000000UL

#endif /* CONF_TIMER_H_ */