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

#include "data_types.h"

QueueHandle_t xQueue = NULL; 

static const Data_t xStructToSend[3] =
{
    {eMotoSpeed, 10, "CAN", 0},
    {eSpeedSetPoint, 12, "HMI", 0},
    {eOtherTask, 13, "Other", 0},
};

static void vSenderTask(void *pvParameters);
static void vReceiverTask(void *pvParameters);

void app_main(void) {
    // Create the queue
    xQueue = xQueueCreate(QUEUE_SIZE, sizeof(Data_t)); 

    // Create the sender tasks
    xTaskCreate(vSenderTask, "Can Bus Task", 2048, (void*)&(xStructToSend), 2, NULL);

    // Create the receiver task
    xTaskCreate(vReceiverTask, "Receiver Task", 2048, (void*)&(xStructToSend[0]), 2, NULL);
    xTaskCreate(vReceiverTask, "Receiver Task", 2048, (void*)&(xStructToSend[1]), 2, NULL);
    xTaskCreate(vReceiverTask, "Receiver Task", 2048, (void*)&(xStructToSend[2]), 2, NULL);

}


static void vSenderTask(void *pvParameters) {
    Data_t* pData = (Data_t*) pvParameters;

    while (1) {
        for (int i = 0; i < 3; i++) {
            if (xQueueSendToBack(xQueue, &pData[i], QUEUE_SEND_WAITS) != pdTRUE) {
                pData[i].lDataValue = (rand() % 100);
                printf("Failed to send %d to queue !\n", pData[i].eDataID);
            }
            vTaskDelay(pdMS_TO_TICKS(QUEUE_SEND_DELAY));
        }
    }
}

static void vReceiverTask(void *pvParameters) {
    while (1) {
        Data_t xReceivedStruct;
        Data_t* pData = (Data_t*) pvParameters;
        if (xQueueReceive(xQueue, &xReceivedStruct, pdMS_TO_TICKS(QUEUE_WAITS)) == pdTRUE) {
            // Receive new item
            if (xReceivedStruct.eDataID == pData->eDataID) 
            {
                printf("I'm %s --- Received from %s task, data = %ld\n", pData->ctaskName, xReceivedStruct.ctaskName, xReceivedStruct.lDataValue);
            } 
            else 
            {
                printf("I'm %s --- Received from %s task, but it's not my task\n", pData->ctaskName, xReceivedStruct.ctaskName);
                xReceivedStruct.rejectTimes++;
                xQueueSendToFront(xQueue, &xReceivedStruct, QUEUE_WAITS);

                if (xReceivedStruct.rejectTimes >= REJECTS_TIMES) {
                    printf("I'm %s ---  Task %s is rejected %d times, skiping the task\n", pData->ctaskName, xReceivedStruct.ctaskName, xReceivedStruct.rejectTimes);
                    Data_t deleteStruct;
                    xQueueReceive(xQueue, &deleteStruct, pdMS_TO_TICKS(QUEUE_WAITS));
                    xReceivedStruct.rejectTimes = 0;
                }
            }
        }
    }
}


