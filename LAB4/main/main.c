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

static const Data_t xStructToSend[2] =
{
    {eMotoSpeed, 10},
    {eSpeedSetPoint, 5},
};

static void vSenderTask(void *pvParameters);
static void vReceiverTask();

void app_main(void) {
    // Create the queue
    xQueue = xQueueCreate(QUEUE_SIZE, sizeof(Data_t)); 

    // Create the sender tasks
    xTaskCreate(vSenderTask, "Can Bus Task", 2048, (void*)&(xStructToSend[0]), 2, NULL);
    xTaskCreate(vSenderTask, "HMI Task", 2048, (void*)&(xStructToSend[1]), 2, NULL);

    // Create the receiver task
    xTaskCreate(vReceiverTask, "Receiver Task", 2048, NULL, 1, NULL);
}

static void vSenderTask(void *pvParameters)
{
    Data_t* pData = (Data_t*) pvParameters;

    while (1)
    {
        if (xQueueSendToBack(xQueue, pvParameters, QUEUE_SEND_WAITS) != pdTRUE)
        {
            printf("Failed to send %d to queue ! \n", pData->eDataID);
        }
        vTaskDelay(pdMS_TO_TICKS(QUEUE_SEND_DELAY));
    }
}

static void vReceiverTask()
{
    Data_t xReceivedStruct;

    while (1) 
    {
        if (xQueueReceive(xQueue, &xReceivedStruct, pdMS_TO_TICKS(QUEUE_WAITS)) == pdTRUE)
        {
            // receive new item
            if (xReceivedStruct.eDataID == eMotoSpeed)
            {
                printf("Received from CAN BUS Task data = %ld\n", xReceivedStruct.lDataValue);
            }
            else if (xReceivedStruct.eDataID == eSpeedSetPoint)
            {
                printf("Received from HMI Task data = %ld\n", xReceivedStruct.lDataValue);
            }
            else printf("Invalid data\n");
        }
    }
}