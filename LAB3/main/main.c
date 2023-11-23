// /*
//  * Created by Nhom 6
// */

// #include <stdio.h>
// #include <inttypes.h>
// #include "sdkconfig.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_chip_info.h"
// #include "esp_flash.h"
// #include "esp_system.h"
// #include "esp_timer.h"
// #include <string.h>
// #include "FreeRTOSConfig.h"
// #include "freertos/semphr.h"

// #include "global_define.h"

// #define MONITOR_PERIOD_TASK1 (1000 / portTICK_PERIOD_MS) // delay for task 1
// #define MONITOR_PERIOD_TASK2 (100 / portTICK_PERIOD_MS) // delay for task 2

// /* Global variable for idle task tick of each core */
// volatile uint64_t ulIdleTicksCore0 = 0;
// volatile uint64_t ulIdleTicksCore1 = 0;

// volatile TickType_t xPrevTickCore0 = 0;
// volatile TickType_t xPrevTickCore1 = 0;

// static uint8_t ucFirstTimeTask1 = 1;
// static uint8_t ucFirstTimeTask2 = 1;

// char pcMsg[] = "This is our text to testing LAB3";

// /* Do nothing for specific milliseconds*/
// void vBusyWaitMs(int iMilliseconds) {
//     int64_t lStart = esp_timer_get_time();
//     int64_t lEnd = lStart + iMilliseconds * 1000;
//     while (esp_timer_get_time() < lEnd) {
//         ; // Do nothing
//     }
// }

// void vTask1(void* pvParameters){
//     int iLen = strlen(pcMsg);
//     while(true){
//         vBusyWaitMs(200);
//         taskYIELD();
//         vTaskDelay(MONITOR_PERIOD_TASK1);
//     }
// }

// void vTask2(void* pvParameters){
//     while(true){
//         vBusyWaitMs(50);
//         taskYIELD();
//         vTaskDelay(MONITOR_PERIOD_TASK2);
//     }
// }

// void vApplicationIdleHook()
// {
//     if (xPortGetCoreID() == 0) {
//         ulIdleTicksCore0++;
//     } else {
//         ulIdleTicksCore1++;
//     }
// }

// /* Monitor task for both core */
// static void vMonitorCore1(void* arg) {
//     while (1) {
//         vTaskDelay(MONITOR_PERIOD_TASK1);

//         TickType_t currentTick = xTaskGetTickCount();
//         TickType_t elapsedTicks = currentTick - xPrevTickCore0;

//         float cpu0Utilization = 100.0 - ((float)ulIdleTicksCore0 * 100.0 / elapsedTicks);

//         if (!ucFirstTimeTask1) printf("CPU0 Utilization: %.2f%%\n", cpu0Utilization);
//         else ucFirstTimeTask1 = 0;

//         // Reset the idle ticks and update the previous tick count
//         ulIdleTicksCore0 = 0;
//         xPrevTickCore0 = currentTick;
//     }
// }

// static void vMonitorCore2(void* arg) {
//     while (1) {
//         vTaskDelay(MONITOR_PERIOD_TASK2);

//         TickType_t currentTick = xTaskGetTickCount();
//         TickType_t elapsedTicks = currentTick - xPrevTickCore1;

//         float cpu1Utilization = 100.0 - ((float)ulIdleTicksCore1 * 100.0 / elapsedTicks);

//         if (!ucFirstTimeTask2) printf("CPU1 Utilization: %.2f%%\n", cpu1Utilization);
//         else ucFirstTimeTask2 = 0;

//         // Reset the idle ticks and update the previous tick count
//         ulIdleTicksCore1 = 0;
//         xPrevTickCore1 = currentTick;
//     }
// }

// void app_main(void) {
//     xTaskCreate(vTask1, "Task1", 2048, NULL, 1, NULL);
//     xTaskCreate(vTask2, "Task2", 2048, NULL, 2, NULL);
//     // xTaskCreate(vMonitorCore1, "Monitor Core1", 2048, NULL, 3, NULL);
//     // xTaskCreate(vMonitorCore2, "Monitor Core2", 2048, NULL, 4, NULL);
// }



/*
 * Created by Nhom 6
*/

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"
#include <string.h>
#include "FreeRTOSConfig.h"
#include "freertos/semphr.h"

#include "global_define.h"

#define MONITOR_PERIOD_TASK1 (1000 / portTICK_PERIOD_MS) // delay for task 1
#define MONITOR_PERIOD_TASK2 (100 / portTICK_PERIOD_MS) // delay for task 2

/* Global variable for idle task tick of each core */
volatile uint64_t ulIdleTicksCore0 = 0;
volatile uint64_t ulIdleTicksCore1 = 0;

volatile TickType_t xPrevTickCore0 = 0;
volatile TickType_t xPrevTickCore1 = 0;

static uint8_t ucFirstTimeTask1 = 1;
static uint8_t ucFirstTimeTask2 = 1;

char pcMsg[] = "This is our text to testing LAB3";

/* Do nothing for specific milliseconds*/
void vBusyWaitMs(int iMilliseconds) {
    int64_t lStart = esp_timer_get_time();
    int64_t lEnd = lStart + iMilliseconds * 1000;
    while (esp_timer_get_time() < lEnd) {
        ; // Do nothing
    }
}

void vTask1(void* pvParameters){
    int iLen = strlen(pcMsg);
    while(true){
        for(int i=0; i < iLen; i++){
            printf("%c", pcMsg[i]);
            vBusyWaitMs(50);
        }
        printf("\n");
        vBusyWaitMs(200);
        taskYIELD();
        vTaskDelay(MONITOR_PERIOD_TASK1);
    }
}

void vTask2(void* pvParameters){
    while(true){
        printf("*");
        vBusyWaitMs(50);
        taskYIELD();
        vTaskDelay(MONITOR_PERIOD_TASK2);
    }
}

void vApplicationIdleHook()
{
    if (xPortGetCoreID() == 0) {
        ulIdleTicksCore0++;
    } else {
        ulIdleTicksCore1++;
    }
}

/* Monitor task for both core */
static void vMonitorCore1(void* arg) {
    while (1) {
        vTaskDelay(MONITOR_PERIOD_TASK1);

        TickType_t currentTick = xTaskGetTickCount();
        TickType_t elapsedTicks = currentTick - xPrevTickCore0;

        float cpu0Utilization = 100.0 - ((float)ulIdleTicksCore0 * 100.0 / elapsedTicks);

        if (!ucFirstTimeTask1) printf("CPU0 Utilization: %.2f%%\n", cpu0Utilization);
        else ucFirstTimeTask1 = 0;

        // Reset the idle ticks and update the previous tick count
        ulIdleTicksCore0 = 0;
        xPrevTickCore0 = currentTick;
    }
}

static void vMonitorCore2(void* arg) {
    while (1) {
        vTaskDelay(MONITOR_PERIOD_TASK2);

        TickType_t currentTick = xTaskGetTickCount();
        TickType_t elapsedTicks = currentTick - xPrevTickCore1;

        float cpu1Utilization = 100.0 - ((float)ulIdleTicksCore1 * 100.0 / elapsedTicks);

        if (!ucFirstTimeTask2) printf("CPU1 Utilization: %.2f%%\n", cpu1Utilization);
        else ucFirstTimeTask2 = 0;

        // Reset the idle ticks and update the previous tick count
        ulIdleTicksCore1 = 0;
        xPrevTickCore1 = currentTick;
    }
}

void app_main(void) {
    xTaskCreate(vTask1, "Task1", 2048, NULL, 2, NULL);
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL);
    // xTaskCreate(vMonitorCore1, "Monitor Core1", 2048, NULL, 3, NULL);
    // xTaskCreate(vMonitorCore2, "Monitor Core2", 2048, NULL, 4, NULL);
}