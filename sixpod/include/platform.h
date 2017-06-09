/*
 * config.h
 *
 *  Created on: May 2, 2017
 *      Author: mosas
 */

#ifndef SRC_PLATFORM_PLATFORM_H_
#define SRC_PLATFORM_PLATFORM_H_

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
#include "xstatus.h"
#include "xgpio.h"
/* lwIP includes.*/
#include "netif/xadapter.h"
#include "lwip/sockets.h"
#include "lwipopts.h"
/* fat file system includes.*/
#include "xsdps.h"		/* SD device driver */
#include "ff.h"
#include "xil_cache.h"


#define THREAD_STACKSIZE 1024

#endif /* SRC_PLATFORM_PLATFORM_H_ */
