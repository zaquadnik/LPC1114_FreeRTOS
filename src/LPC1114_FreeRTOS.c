/*
===============================================================================
 Name        : LPC1114_FreeRTOS.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>
#include "sys_tasks.h"
#include "system_LPC11xx.h"
#include "lpc11xx.h"

int main(void) {

	TaskHandle_t HtBtHandle = NULL;

	xTaskCreate(HeartBeatTask,
	            "HeartBeat",
				HEART_BEAT_STACK_SIZE,
	            NULL,
				HEART_BEAT_TASK_PRIORITY,
	            &HtBtHandle);

	vTaskStartScheduler();

    return 0 ;
}


