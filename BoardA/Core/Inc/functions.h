/*
 * functions.h
 *
 *  Created on: Jan 30, 2026
 *      Author: david-isfc
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"

// Turns off the motor
void motor_turnOff(void);

// Turns on the motor
void motor_turnOn(void);

// Applies specific duty cycle to the motor
void motor_applyControl(uint32_t control);

// Reads the speed of the motor via the encoder
// ms is the time
uint32_t motor_readSpeed(uint32_t ms);

// Sends the speed to BoardB via Ethernet Cable
void motor_sendSpeed(uint32_t speed);

// Get Control from BoardB
uint32_t motor_getControl(void);


#endif /* INC_FUNCTIONS_H_ */
