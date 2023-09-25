#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#define NUM_TIMERS 3

extern uint32_t g_timestamp;

typedef enum {
    eTimestamp,
    eTimer1,
    eTimer2
} TimerID_t;


#endif