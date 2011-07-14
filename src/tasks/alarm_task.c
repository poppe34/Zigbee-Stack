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
#include "spi_task.h"

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
	packet_t *pkt;
	va_list arg;
	va_start(arg, str);
	

	
	if(lvl <= VERBOSE_LEVEL)
	{
	  if(*str)
	  {	
		pkt = TM_newPacket(YES);
	
		pkt->dir = to_usb;
		pkt->task = task_alarm;
		pkt->subTask = alarm_first;

			
            if(pkt)
			{
	            pkt->len = 0;
	            char *ptr = pkt->buf;
				
				//Allow for variables to be added to the alarm string
		        vsprintf((char *)pkt->buf, str, arg);							
		   		
				//establish the length of the Alarm String    
			    while(*ptr)
			    {
		            pkt->len++;
		            ptr++;
				}
			    //Make sure that the string ends in 0 and add and the length is adjusted
			    pkt->buf[(pkt->len)] = 0;
			    pkt->len++;
				
				// Add 3 for the header
				pkt->len += 3;
			}					
		}
		else
		{
			pkt->len = 200;
		}								
	    
	}

	va_end(arg);
}


keep_task_t alarm_subTaskHandler(packet_t *pkt)
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
				 if(spi_ready())
				 {
					spi_sendToDev(pkt);
					return retain_task;
				 }
				 else
				 {
					 return retain_task;
				 }				
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

	return release_task;
}



