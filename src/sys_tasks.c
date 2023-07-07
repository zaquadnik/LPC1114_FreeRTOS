/*
 * sys_tasks.c
 *
 *  Created on: 19 cze 2023
 *      Author: Lenovo
 */

#include "sys_tasks.h"
#include "lpc11xx.h"

struct SysCtx_t{
	uint32_t IdleCounter;
	uint32_t HeartBeatState : 1,
	         Reserved       : 31;
};

struct SysCtx_t SysCtx;

SysCtxHandle_t GetSysCtxHande(void)
{
	return &SysCtx;
}

void ResetIdleCnt(SysCtxHandle_t SysCtxHandle)
{
	SysCtxHandle->IdleCounter = 0;
}

void IncIdleCnt(SysCtxHandle_t SysCtxHandle)
{
	SysCtxHandle->IdleCounter++;
}

void vApplicationIdleHook(void)
{
	IncIdleCnt(GetSysCtxHande());
}

void vApplicationMallocFailedHook(void)
{
	uint32_t i;

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	LPC_GPIO3->DIR |= (1<<4) | (1<<5);
	LPC_GPIO3->DATA &= ~((1<<4) | (1<<5));

	while(1)
	{
    	LPC_GPIO3->DATA &= ~(1<<4);
    	LPC_GPIO3->DATA |= (1<<5);
    	for(i=1000000; i>0; i--);
    	LPC_GPIO3->DATA |= (1<<4);
    	LPC_GPIO3->DATA &= ~(1<<5);
    	for(i=1000000; i>0; i--);
	}
}

void HeartBeatTask(void *pvParameters)
{
	SysCtxHandle_t SysCtxHandle;
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	LPC_GPIO3->DIR |= (1<<4) | (1<<5);
	LPC_GPIO3->DATA &= ~((1<<4) | (1<<5));

	SysCtxHandle = GetSysCtxHande();
	SysCtxHandle->HeartBeatState = 0;

	while(1)
	{
		if(SysCtxHandle->HeartBeatState)
		{
			LPC_GPIO3->DATA |= (1<<4);
			SysCtxHandle->HeartBeatState = 0;
		}
		else
		{
			LPC_GPIO3->DATA &= ~(1<<4);
			SysCtxHandle->HeartBeatState = 1;
		}
		vTaskDelay(xDelay);
	}
}
