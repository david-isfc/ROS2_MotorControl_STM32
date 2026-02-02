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
#include "app.h"

// Turns off the motor
void motor_turnOff(void);

// Turns on the motor
void motor_turnOn(void);

// Applies specific duty cycle to the motor
void motor_applyControl(int8_t cmd);

// Reads the speed of the motor via the encoder
// ms is the time
int32_t motor_readSpeed();

// Sends the speed to BoardB via Ethernet Cable
void motor_sendSpeed(int32_t speed);

// Get Control from BoardB
int8_t motor_getControl(void);


#endif /* INC_FUNCTIONS_H_ */
