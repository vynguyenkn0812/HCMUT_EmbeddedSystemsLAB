#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOSConfig.h"


void vPrintStudentID(void* pvParameters){
    while (1)
    {
        printf("2012968");
    }
}
void vPrintEsp32(void* pvParameters){
    while (1)
    {
        vTaskSuspend(NULL);
        printf("ESP32");
    }
    
}