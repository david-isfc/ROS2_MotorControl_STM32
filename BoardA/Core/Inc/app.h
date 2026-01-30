/*
 * app.h
 *
 *  Created on: Jan 30, 2026
 *      Author: david-isfc
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include <stdint.h>
#include "functions.h"

// Initializes the RTOS threads, sets the priorities and configures peripherals
void app_init(void);

// The main app loop, just idling for the moment
void app_loop(void);

#endif /* INC_APP_H_ */
