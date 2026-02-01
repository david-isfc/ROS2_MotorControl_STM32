/*
 * functions.c
 *
 *  Created on: Jan 30, 2026
 *      Author: david-isfc
 */

#include "functions.h"
extern TIM_HandleTypeDef htim3;
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
	// cmd is transmitted via Ethernet over 8 bits, 1% precision given
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
// ms is the time
uint32_t motor_readSpeed(uint32_t ms){
	return 0;
}

// Sends the speed to BoardB via Ethernet Cable
void motor_sendSpeed(uint32_t speed){

}

// Get Control from BoardB
uint32_t motor_getControl(void){
	return 65535;
}



