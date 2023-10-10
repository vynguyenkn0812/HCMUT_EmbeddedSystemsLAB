#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOSConfig.h"
#include "driver/gptimer.h"


void vPrintStudentID(void* pvParameters){
    while (1)
    {
        TickType_t xWakeUpTime = xTaskGetTickCount();
        printf("2012968");
        xTaskDelayUntil(&xWakeUpTime, 1000/portTICK_PERIOD_MS); 
    }
}

void vPrintEsp32(void* pvParameters){
    while (1)
    {
        vTaskSuspend(NULL);
        printf("ESP32");
    }
}