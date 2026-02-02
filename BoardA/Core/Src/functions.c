/*
 * functions.c
 *
 *  Created on: Jan 30, 2026
 *      Author: david-isfc
 */

#include "functions.h"
#include <stdlib.h>
#define RESOLUTION 2048 // motor pulses per revolution
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;
// Turns off the motor
void motor_turnOff(void){
	// Set PA5 and PA6 high → motor ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

// Turns on the motor
void motor_turnOn(void){
	// Set PA5 and PA6 high → motor ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
}

// Applies specific duty cycle to the motor
void motor_applyControl(int8_t cmd){

	// Clamp input 
	if (cmd > 100)  cmd = 100;
    if (cmd < -100) cmd = -100;
	
	uint32_t duty = 0;
	
    // Convert percentage to timer counts
	// cmd is transmitted via Ethernet over 8 bits, 1% precision
    if (cmd != 0) {
        duty = (uint32_t)((abs(cmd) * 65535UL) / 100UL);
    }
	
	if (cmd > 0) {
        // Forward
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
    }
    else if (cmd < 0) {
        // Reverse
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
    }
    else {
        // Stop
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
    }
}

// Reads the speed of the motor via the encoder
// Speed is sample at a fixed rate, called PERIOD_COMM_MS
int32_t motor_readSpeed(){
	static uint32_t prev_cnt = 0;

	uint32_t curr_cnt = __HAL_TIM_GET_COUNTER(&htim1);
	int32_t delta = (int32_t)(curr_cnt - prev_cnt);

	prev_cnt = curr_cnt;

	delta = (delta * 60000) / (4 * RESOLUTION * PERIOD_COMM_MS);
	return delta; //speed
}

// Sends the speed to BoardB via Ethernet Cable
void motor_sendSpeed(int32_t speed){

}

// Get Control from BoardB
int8_t motor_getControl(void){
	return 10;
}



