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
#include "NWK/NWK_nlme_join.h"


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
		nf.scanChannels = 0x00008000;
		nf.scanDuration = 0x2;
		nf.superframeOrder = 0xf;
		NWK_nlme_formNetworkReq(&nf);

	}
else{		
	nwk_join_t join;
	join.extedPANid = 0x0000222388894343;
	join.capabilityInfo.altPanCoord = NO;
	join.capabilityInfo.powerSource = 0;
	join.capabilityInfo.devType = 0;
	join.capabilityInfo.reserved2 = 0;
	join.capabilityInfo.secEnabled = 0;
	join.capabilityInfo.allocAddr = 0x01;
	join.duration = 2;
	join.scanChannels = 0x00000800;
	join.securityEnabled = NO;
	join.rejoinNetwork = JOINED_THRU_ASSOC;
	
	addr_t dest;
	dest.shortAddr = 0x0000;
	dest.PANid = 0x3ac6;
	dest.mode = 0x02;
	MAC_mlme_assocReq(&dest, DEFAULT_CHANNELPAGE, DEFAULT_CHANNEL, *((uint8_t *)&join.capabilityInfo), &sec);
}

	scheduler();
	

    return 0;
}

	
	void debug_test(void)
	{
		LED_On(LED3_GPIO);
	}	