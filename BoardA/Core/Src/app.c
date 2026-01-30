/*
 * app.c
 *
 *  Created on: Jan 30, 2026
 *      Author: david-isfc
 */

#include "main.h"
#include "app.h"
#include "cmsis_os.h"

#define PERIOD_CTRL 10
#define PERIOD_COMM 15
#define FLAG_PERIODIC 0x01

extern TIM_HandleTypeDef htim3;

osThreadId_t motor_applyControlHandle; // Thread that controls the motor based on the received control
osThreadId_t motor_commHandle; // Thread that reads the speed, sends it over to board B to calculate the needed control

osTimerId_t timer_ctrl;
osTimerId_t timer_comm;

volatile uint32_t control = 0;
volatile uint32_t ms = 0;

void motor_commThreadFunc(void *argument){
	for(;;){
		osThreadFlagsWait(FLAG_PERIODIC, osFlagsWaitAll, osWaitForever);
		// communication
		uint32_t speed = motor_readSpeed(ms);
		motor_sendSpeed(speed);
		control = motor_getControl();
	}
}

void motor_applyControlFunc(void* argument){
	for(;;){
		osThreadFlagsWait(FLAG_PERIODIC, osFlagsWaitAll, osWaitForever);
		motor_applyControl(control);
	}
}

void TimerCallback(void *argument) {
    osThreadId_t tid = (osThreadId_t)argument;
    osThreadFlagsSet(tid, FLAG_PERIODIC);
}

void app_init(){

	control = 0;

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	// Initialize Threads
	const osThreadAttr_t comm_attr = { .priority = osPriorityAboveNormal };
	motor_commHandle = osThreadNew(motor_commThreadFunc, NULL, &comm_attr);

	const osThreadAttr_t ctrl_attr = { .priority = osPriorityNormal };
	motor_applyControlHandle = osThreadNew(motor_applyControlFunc, NULL, &ctrl_attr);

	// Initialize OsTimers
	timer_comm = osTimerNew(TimerCallback, osTimerPeriodic, (void*)motor_commHandle, NULL);
	osTimerStart(timer_comm, PERIOD_COMM);

	timer_ctrl = osTimerNew(TimerCallback, osTimerPeriodic, (void*)motor_applyControlHandle, NULL);
	osTimerStart(timer_ctrl, PERIOD_CTRL);

	motor_turnOn();

}

void app_loop(void){
	// Do nothing
	   osThreadFlagsWait(0x01, osFlagsWaitAll, osWaitForever);
}
