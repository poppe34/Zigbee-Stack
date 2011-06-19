/*
 * xmega_time.c
 *
 *  Created on: Nov 10, 2010
 *      Author: mpoppe
 */

#include <frame.h>

#include <conf_zigbee.h>
#include "conf_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include "misc/time.h"
#include "misc/qsm.h"
#ifdef	XMEGA
uint8_t temp;

uint16_t get_Ticks(void);
	volatile uint16_t long_time = 0x0000;

void time_init(void){

	//osc_cal();
	qsm_init();
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_EVSYS);
	start_short_time();
	start_long_time();
	start_ticks();

}
// This function will caibrate the Internal RC Oscillator to 8 MHz using the 32.678 kHz external oscillator
/*
void osc_cal(void){
	uint16_t cal_min = 62187;
	uint16_t cal_max = 62812;

	volatile uint16_t timer;
	uint8_t cal_run = no;
	uint8_t cal_count = 255;

	PRR0 &= ~(_BV(PRTIM1) | _BV(PRTIM2));
	ASSR |= _BV(EXCLK);
	ASSR |= _BV(AS2);

// Check if the timers are ready... When the AS2 is set values can become corrupt
	while(ASSR & (_BV(TCN2UB)| _BV(TCR2AUB) | _BV(TCR2BUB))){;}

/*	Start the timers and compare the output to make sure that it is within tolerence... If it is outside
 * 	If the timers are out of tolerence reset the registers and run them again until timer2 hits its overflow
 * 	compare the output again and make sure it is within tolerance.  Do this until it is within tolerence or it
 * 	has failed 256 times.
 *//*
	uint8_t original_cal = OSCCAL;
	OSCCAL = 0x95;

//	Is not working the board that i have uses a 32kHz oscillator that has a know issue of running to fast
// 	so my program will never calibrate correctly I and using 0x95 and just acting as if that is correct (that is what the STK calibrates to)
	while((cal_run == yes) && (cal_count != 0)){


//	Reset both timers
		TCNT2 = 0x00;
		TCNT1 = 0x0000;
		TIFR2 = 0xff;

//	Start the two timers...
		TCCR2B |= _BV(CS20);
		TCCR1B |= _BV(CS10);

//	Wait for timer2 to overfill
		while((TIFR2 & _BV(TOV2)) != _BV(TOV2)){;}

// Stop the two timers
			TCCR2B & ~_BV(CS20);
			TCCR1B = 0;

// Check if timer1 is withing tolerence
			timer = TCNT1;

			if(timer < cal_min){
				OSCCAL++;
			}//endif

			if(timer > cal_max){
				OSCCAL--;
			}//endElseif

			if((cal_min<timer) && (timer<cal_max)){
				cal_run = NO;
			}//endif

				cal_count--;
				if(cal_count == 0){
				OSCCAL = original_cal;
				}//endif
#ifdef debug
				if(cal_count == 0){
					error("CALIBRATION FAILED");
				}//endif
#endif

	}//End while

}//osc_cal
*/
void delay_us(uint16_t length){
	uint16_t timer;

	if(length >10){
		timer = tc_read_count(ZIGBEE_MS_TIMER);
		timer += length;
		timer += length;

    /* INIT loop to instigate timer */
		do{
			timer = tc_read_count(ZIGBEE_MS_TIMER);
		}while(length> timer);
	}
}
void start_short_time(void){
//setup event0
	EVSYS_CH0MUX = EVSYS_CHMUX_TCD0_OVF_gc;  //TODO: I need to do something with this statement to make it generic
// clear any power reduction on counter
	tc_enable(ZIGBEE_MS_TIMER);
    tc_set_direction(ZIGBEE_MS_TIMER, TC_UP);
    tc_write_count(ZIGBEE_MS_TIMER, 0x0000); //Reset Counter
// clear any interrupt flags
	tc_clear_all_interrupts(ZIGBEE_MS_TIMER);

//	Starting Timer1 with a prescale of 8... This will give me a 2MHz signal and will count every 1us...
    tc_set_resolution(ZIGBEE_MS_TIMER, ZIGBEE_MS_RESOLUTION);

	// Setup the interrupt
	tc_set_overflow_interrupt_level(ZIGBEE_MS_TIMER, PMIC_LVL_MEDIUM);
    
}

void start_long_time(void)
{
    tc_enable(ZIGBEE_MS_OVERFLOW);
    tc_clear_all_interrupts(ZIGBEE_MS_OVERFLOW);
//	Reset timer to 0
	tc_write_count(ZIGBEE_MS_OVERFLOW, 0x0000); //Reset Counter

//	Starting Timer3 looking at the event 0... I will have this connected to nothing and only driven by the software
// 	to act purley as a software counter.
	tc_write_clock_source(ZIGBEE_MS_OVERFLOW, TC_CLKSEL_EVCH0_gc);
    }
/*
 * This function returns the total of ticks at the current time
 */

void start_ticks(void)
{
	tc_enable(ZIGBEE_TICK_TIMER);
	tc_set_resolution(ZIGBEE_TICK_TIMER, ZIGBEE_TICK_RESOLUTION);
}
uint32_t get_Time(void){
	uint16_t current_long_time;
	uint32_t total_time = 0x00000000;
	uint16_t timer;

	do{
//	Get the long ticks
		current_long_time = tc_read_count(ZIGBEE_MS_OVERFLOW);
		total_time |= (uint32_t)current_long_time;

		total_time = (total_time<<16);
// Get and the short ticks
//		led_on_byte((uint8_t)(total_time>>16));
		timer = tc_read_count(ZIGBEE_MS_TIMER);// I had to add this statement to get the timer correctly... I am not sure why
		total_time |= ((uint32_t)timer);

		long_time = tc_read_count(ZIGBEE_MS_OVERFLOW);
	}while(current_long_time != long_time);// this ensures that the data is correct and that an interrupt didn't occur while getting the data
//	led_on_byte((uint8_t)(total_time>>16));
	return (total_time);

}
uint16_t get_Ticks(void){
// Get the long time timer value... This value is the number of times Timer1 has overflowed.
	uint16_t ticks;
	ticks = tc_read_count(ZIGBEE_TICK_TIMER);
	return ticks;
}
void timer_irqHandler(void){
// Toggle pin T3 to add one to timer3 for the overflow of Timer1
    EVSYS.STROBE |= 0x01;
}
//This function takes in the number of symbols are needed and converts them to how much time it takes to execute those symbols
uint32_t Symbols_to_Time(uint32_t symbols){
	return(symbols<<SYMBOLS_PER_US);
}
#endif
