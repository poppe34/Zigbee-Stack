/*
 * alarms_task.h
 *
 * Created: 3/10/2011 10:24:59 AM
 *  Author: matt
 */ 


#ifndef ALARMS_TASK_H_
#define ALARMS_TASK_H_

/********************************************************************************
/*          INCLUDES
********************************************************************************/
#include "spi_task.h"
#include "task_master.h"

/********************************************************************************
/*          DEFINES
********************************************************************************/

#define VERBOSE_LEVEL   10
#define alarm(str)  alarm_new(5, str)
/********************************************************************************
/*          TYPEDEFS
********************************************************************************/
typedef struct alarm 
{
	struct alarm    *next;
	char            name[64];
	uint8_t         length;
	uint16_t        timestamp;
}alarm_t;

enum alarm_subTask
{
	alarm_qty = 1,
	alarm_first = 2,
	alarm_clear = 3,
};

/********************************************************************************
/*          PROTOTYPES
********************************************************************************/

void alarm_task_init(void);
void alarm_task(void);
void alarm_free(alarm_t *alrm);
void alarm_new(uint8_t lvl, char *str, ...);
void alarm_sendQty(void);
void alarm_subTaskHandler(packet_t *pkt);
void alarm_sendFirst(void);
alarm_t *alarm_newAlrm(void);

#endif /* ALARMS_TASK_H_ */