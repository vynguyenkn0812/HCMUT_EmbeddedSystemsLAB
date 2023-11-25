/*
 * Created by Nhom 6
*/

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "FreeRTOSConfig.h"

#include "software_timer.h"

TimerHandle_t xTimers[ NUM_TIMERS ];

TimerID_t xTimerID[NUM_TIMERS] = {eTimestamp, eTimer1, eTimer2};

const TickType_t xTimerPeriodInTicks[NUM_TIMERS] = {pdMS_TO_TICKS(10), pdMS_TO_TICKS(2000), pdMS_TO_TICKS(3000)};
const uint8_t uMaxExpiryCountBeforeStopping[NUM_TIMERS] = {0, 10, 5};

void vTimerCallback(TimerHandle_t xTimer) {
    BaseType_t timerID = (BaseType_t) pvTimerGetTimerID(xTimer);
    static uint32_t timer1Count = 0;
    static uint32_t timer2Count = 0;

    switch (timerID) {
        case eTimestamp:
            g_timestamp++;  // Increment global timestamp variable
            break;

        case eTimer1:
            printf("ahihi callback at timestamp = %lds\n", g_timestamp / pdMS_TO_TICKS(1000));
            timer1Count++;
            
            if (timer1Count >= uMaxExpiryCountBeforeStopping[eTimer1]) {
                if (xTimerStop(xTimer, 0) == pdPASS)
                {
                    printf("Reached %ld times, Stop timer ahihi successfully\n", timer1Count);
                }
                else 
                {
                    printf("Stop timer ahihi failed\n");
                }
            }
            break;
        
        case eTimer2:
            printf("ihaha callback at timestamp = %lds\n", g_timestamp / pdMS_TO_TICKS(1000));
            timer2Count++;
            
            if (timer2Count >= uMaxExpiryCountBeforeStopping[eTimer2]) {
                if (xTimerStop(xTimer, 0) == pdPASS)
                {
                    printf("Reached %ld times, Stop timer ihaha successfully\n", timer2Count);
                }
                else 
                {
                    printf("Stop timer ihaha failed\n");
                }
            }
            break;

        default:
            printf("Invalid Timer ID\n");
            break;
    }
}

void app_main(void) {
    // Create the timer
    for( int x = 0; x < NUM_TIMERS; x++ )
    {
        xTimers[x] = xTimerCreate(
                        "Timer",
                        xTimerPeriodInTicks[x],
                        pdTRUE,
                        (void*)xTimerID[x],
                        vTimerCallback
                     );

        if( xTimers[x] == NULL ) // check if the timer is created
        {
            printf("xTimerCreate() API failed !\n");
        }
        else // check if the timer is started
        {
            if( xTimerStart(xTimers[x], 0) != pdPASS )
            {
                printf("The Timer started failed !\n");
            }
            else 
            {
                printf("Initialized timer %d successfully \n", x);
            }
        }
        
    }
}