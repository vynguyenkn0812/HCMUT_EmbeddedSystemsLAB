#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOSConfig.h"


void vPrintStudentID(void* pvParameters){
    while (1)
    {
        TickType_t xWakeUpTime = xTaskGetTickCount();
        printf("2012968");
        xTaskDelayUntil(&wakeUpTime, 1000/)
    }
}
void vPrintEsp32(void* pvParameters){
    while (1)
    {
        vTaskSuspend(NULL);
        printf("ESP32");
    }
    
}