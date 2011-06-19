/*
 * zigbee_task.h
 *
 * Created: 4/29/2011 3:09:01 PM
 *  Author: mpoppe
 */ 


#ifndef ZIGBEE_TASK_H_
#define ZIGBEE_TASK_H_

#include "compiler.h"
#include "conf_debug.h"
#include "task_master.h"
#include "alarms_task.h"
#include "list.h"

#define report_packet(buf, len) zigbee_newPacket(buf, len)

enum zigbeeSubtask
{
	zigbeePacketQty = 0x01,
	zigbeePacketFirst = 0x02,
};

void zigbee_SubtaskHandler(packet_t *pkt);
void zigbee_packetFirst(void);

#ifdef DEBUG_SERVER

void zigbee_task_init(void);
void zigbee_packetQTY(void);
void zigbee_packetFirst(void);
#endif

void zigbee_newPacket(uint8_t *buf, uint8_t zlen);
#endif /* ZIGBEE_TASK_H_ */