/*
 * error.c
 *
 *  Created on: Feb 27, 2011
 *      Author: mattpoppe
 */

#include "compiler.h"
#include "status_codes.h"
#include "errors.h"
#include "spi_master.h"
#include "spi_task.h"
#include "xplain.h"

status_code_t errors(char *buf)
{
	status_code_t errorCode = STATUS_OK;

	spi_send_alarm(buf);

	return errorCode;
}
