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
void motor_applyControl(uint32_t control){

	control = 1<<30;
	if(control > 65535) control = 65535;

	uint8_t reverse = 0;
	if(reverse){
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, control);
	} else {
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, control);
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



