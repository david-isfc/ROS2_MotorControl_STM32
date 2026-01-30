/*
 * example_file.c
 *
 * Cheatsheet - Example of RTOS structure with threads and timers
 *
 * Author: david-isfc
 */

#include "cmsis_os2.h"
#include <stdint.h>
#include <stdio.h>

/* ---------------- Global Variables ---------------- */
osThreadId_t tid_exampleTask;   // Thread handle
osTimerId_t timer_example;      // Timer handle
#define FLAG_PERIODIC 0x01       // Thread flag

uint32_t counter = 0;            // Shared variable updated by task

/* ---------------- Function Prototypes ---------------- */
void ExampleTask(void *argument);
void TimerCallback(void *argument);
void System_Init(void);
void System_Loop(void);

/* ---------------- Application Setup ---------------- */
int main(void) {
    // Initialize hardware if needed
    System_Init();

    // Initialize CMSIS-RTOS kernel
    osKernelInitialize();

    // Create example thread
    const osThreadAttr_t example_attr = {
        .priority = osPriorityNormal,
        .name = "ExampleTask"
    };
    tid_exampleTask = osThreadNew(ExampleTask, NULL, &example_attr);

    // Create a periodic software timer (triggers every 1000 ms)
    timer_example = osTimerNew(TimerCallback, osTimerPeriodic, tid_exampleTask, NULL);
    osTimerStart(timer_example, 1000);  // period in ms

    // Start RTOS kernel
    osKernelStart();

    // Should never reach here
    while (1) {}
}

/* ---------------- System Initialization ---------------- */
void System_Init(void) {
    // Initialize hardware here if needed (GPIOs, UART, etc.)
    counter = 0;
}

/* ---------------- Main loop (idle) ---------------- */
void System_Loop(void) {
    // This can be used as a low-priority idle loop
    for (;;) {
        osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);
    }
}

/* ---------------- Example Task ---------------- */
void ExampleTask(void *argument) {
    for (;;) {
        // Wait for periodic signal from timer
        osThreadFlagsWait(FLAG_PERIODIC, osFlagsWaitAll, osWaitForever);

        // This code runs every time timer triggers
        counter++;
        printf("ExampleTask running! Counter = %lu\n", counter);
    }
}

/* ---------------- Timer Callback ---------------- */
void TimerCallback(void *argument) {
    osThreadId_t tid = (osThreadId_t) argument;

    // Signal the thread to run
    osThreadFlagsSet(tid, FLAG_PERIODIC);
}
