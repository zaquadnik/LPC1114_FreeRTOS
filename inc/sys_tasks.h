/*
 * sys_tasks.h
 *
 *  Created on: 19 cze 2023
 *      Author: Lenovo
 */

#ifndef SYS_TASKS_H_
#define SYS_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#define HEART_BEAT_TASK_PRIORITY  (tskIDLE_PRIORITY)
//#define mainFLASH_TASK_PRIORITY  (tskIDLE_PRIORITY + 1)
//#define mainLCD_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define HEART_BEAT_STACK_SIZE (configMINIMAL_STACK_SIZE)

typedef struct SysCtx_t* SysCtxHandle_t;

SysCtxHandle_t GetSysCtxHande(void);

void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);
void HeartBeatTask(void *pvParameters);


#endif /* SYS_TASKS_H_ */
