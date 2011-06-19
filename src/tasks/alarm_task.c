/*
 * alarm_task.c
 *
 * Created: 3/10/2011 9:43:45 AM
 *  Author: matt
 */ 
#include "list.h"
#include "alarms_task.h"
#include "stdio.h"
#include "stdarg.h"
#include "task_master.h"

/*********************************************************
/*              Variable Declarations
/********************************************************/


/************************************************************************/
/* Function:    alarm_task_init

/* Description: Initializes the alarmLog

/* Arguments:   None

/* Return:      None                     
/************************************************************************/
void alarm_task_init(void)
{
	
	alarm("This is just a device Test Alarm");
}

/************************************************************************/
/* Function:    alarm_new

/* Description: Takes an alarm string in and allocates memory for the alarm.
                Then the alarm is added to the alarmLog list 
				
/* Arguments:   alarm string

/* Return:      nothing                      
/************************************************************************/
void alarm_new(uint8_t lvl, char *str, ...)
{
	
	va_list arg;
	va_start(arg, str);
	
	packet_t *pkt = TM_newPacket();
	
	pkt->dir = to_usb;
	pkt->task = task_alarm;
	pkt->subTask = alarm_first;
	
	if(lvl <= VERBOSE_LEVEL)
	{
	  if(*str)
		{
			
            if(pkt)
			{
	            pkt->len = 0;
	            char *ptr = pkt->buf;
				
		        vsprintf((char *)pkt->buf, str, arg);							
		   		    
			    while(*ptr)
			    {
		            pkt->len++;
		            ptr++;
				}
			
			    pkt->buf[(pkt->len)] = 0;
			    pkt->len++;
			}					
		}					
	    
	}

	va_end(arg);
}


void alarm_subTaskHandler(packet_t *pkt)
{
	switch (pkt->subTask)
	{
		case alarm_qty:
		    switch(pkt->dir)
			{
				case to_device:
				
				break;
			    case from_device:
			    
				break;
				case from_usb:
				break;
				case to_usb:
				
				break;
			}				
			
			
		break;
		case alarm_first:
		    switch(pkt->dir)
			{
				case to_device:
				
				break;
			    case from_device:
			       
				break;
				case from_usb:
				break;
				case to_usb:
				 spi_sendToDev(pkt);
				break;
			}			
		break;
		case alarm_clear:
		    alarm_new(5, "Request for unclear is not implemented");
		break;
		default:
		alarm_new(5, "Unknown Alarm Sub Task");
		break;
	}

}



