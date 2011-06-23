/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * AVR Software Framework (ASF).
 */
#define F_CPU   16000000UL
#include <asf.h>
#include "led.h"
#include "gpio.h"
#include "util/delay.h"
#include "scheduler.h"
#include "alarms_task.h"
#include "zigbee.h"
#include "zigbee_task.h"
#include "spi_task.h"

#include "RF230/RF230.h"

#include "MAC/mac_prototypes.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_command.h"


#include "NWK/NWK_prototypes.h"
#include "NWK/NWK_command.h"
#include "NWK/NWK_neighborTable.h"
#include "NWK/NWK_nlme.h"
#include "NWK/NWK_nlde.h"


void debug_test(void);

int main(void)
{

	board_init();
    uint16_t count;
	// Insert application code here, after the board has been initialized.
	
	sysclk_init();
	spi_task_init();
	pmic_init();
	alarm_task_init();
	scheduler_init();
	alarm("Device Restarted");
    zigbee_init();

    PORTC.INT0MASK |= PIN3_bm;
	PORTC.INTCTRL |= PORT_INT0LVL_LO_gc;
	PORTC.PIN3CTRL |= (PORT_ISC1_bm);
	//PORTC.PIN3CTRL |= (PORT_ISC1_bm | PORT_ISC2_bm);
	
	sei();
	

	
	addr_t destShortTemp, destLongTemp;

	destShortTemp.PANid = 0xBABE;
	destShortTemp.shortAddr = 0x0000;
	destShortTemp.mode = MAC_SHORT_ADDRESS;
	
	destLongTemp.PANid = 0x1122;
	destLongTemp.extAddr = 0x9999999999999999;
	destLongTemp.mode = MAC_LONG_ADDRESS;
	
	security_t sec;

	

if(ioport_pin_is_high(ZIGBEE_COORD_GPIO))
	{
		nwk_nlme_nf_t nf;
		nf.beaconOrder = 0xf;
		nf.BatteryLifeExt = NO;
		nf.scanChannels = 0x00000800;
		nf.scanDuration = 0x2;
		nf.superframeOrder = 0xf;
		NWK_nlme_formNetworkReq(&nf);

	}	


	scheduler();
	

    return 0;
}

	
	void debug_test(void)
	{
		LED_On(LED3_GPIO);
	}	