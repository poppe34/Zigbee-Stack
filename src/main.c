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
#include "NWK/NWK_prototypes.h"
#include "NWK/NWK_command.h"
#include "MAC/mac_prototypes.h"
#include "MAC/MAC_mlme.h"
#include "MAC/MAC_command.h"

#include "RF230/RF230.h"

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

//	MAC_beaconReqCommand();//LOOKS GOOD
//	if((MAC_isPanCoord()) == 0)
	{
		
	nwk_leaveCmdOptionField_t temp;
	temp.removeChild = YES;
	
	NWK_cmd_linkStatus();
	
/*	_delay_ms(500);
	MAC_mlme_assocReq(&destShortTemp, 0x00000000, 11, 0x8e, &sec);


	_delay_ms(5000);
	mac_mlme_disassocReq(DEV_WISHES_TO_LEAVE);
	*/
	}	
//	MAC_assocRequestCommand(&destShortTemp);//LOOKS GOOD
//	MAC_assocResponceCommand(mlme_assoc_t *assoc);
//	MAC_disassocCommand(&destShortTemp);//LOOKS GOOD
//	MAC_dataRequestCommand(&destShortTemp);//LOOKS GOOD
//	MAC_panIDConflictCommand();//LOOKS GOOD
//	MAC_orphanCommand();//LOOKS GOOD
//	MAC_beaconReqCommand();
//	MAC_commandCoordRealign(&destShortTemp, &sec);

	scheduler();
	

    return 0;
}

	
	void debug_test(void)
	{
		LED_On(LED3_GPIO);
	}	