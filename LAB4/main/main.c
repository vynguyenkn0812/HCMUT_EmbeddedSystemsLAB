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
#include <string.h>
#include <time.h>

#include "data_types.h"

static uint8_t TaskCount = 0;

QueueHandle_t xQueue = NULL; 

struct TaskType CAN = {.cTaskName = "CAN", .eDataID = 0};
struct TaskType HMI = {.cTaskName = "HMI", .eDataID = 1};
struct TaskType SPI = {.cTaskName = "SPI", .eDataID = 2};

void vSenderTask(void * pvParameter) {
    time_t t;
    srand((unsigned) time(&t));

    while (1) {
        int ranTask = (rand() % 4);

        struct QueueData *xData = malloc(sizeof(struct QueueData));

        // Create task based on random number
        if (xData != NULL) {
            switch(ranTask) {
                case eMotoSpeed:
                    xData->eRequestID = eMotoSpeed;
                    strcpy(xData->cMessage, "CAN");
                    xData->rejectTimes = 0;
                    xData->lDataValue = rand() % 100;
                break;
                case eSpeedSetPoint:
                    xData->eRequestID = eSpeedSetPoint;
                    strcpy(xData->cMessage, "HMI");
                    xData->rejectTimes = 0;
                    xData->lDataValue = rand() % 100;
                break;
                case eSPISetMode:
                    xData->eRequestID = eSPISetMode;
                    strcpy(xData->cMessage, "SPI");
                    xData->rejectTimes = 0;
                    xData->lDataValue = rand() % 100;
                break;
                case Other:
                    xData->eRequestID = 99;
                    strcpy(xData->cMessage, "DUNNO");
                    xData->rejectTimes = 0;
                    xData->lDataValue = rand() % 100;
                break;
            }

            // Send this random task to the queue
            if (xQueueSendToBack(xQueue, (void *)&xData, QUEUE_SEND_WAITS) != pdTRUE) {
                printf("Failed to send %s to queue !\n", xData->cMessage);
            }
        } else {
            printf("Allocated queue failed !");
        }
        vTaskDelay(pdMS_TO_TICKS(QUEUE_SEND_DELAY));
    }
    vTaskDelete(NULL);
}

void vReceiverTask(void* pvParameter) {
    TaskCount++;
    for (; ;) {
        struct TaskType *pData  = (struct TaskType *)pvParameter;
        struct QueueData *xReceivedStruct;
        
        if (xQueue != NULL) {
            // Check if there are any items in the queue. If yes, handle them; otherwise, increase the reject variable by 1.
            // If the reject variable reaches its maximum, skip this task.
            if (xQueueReceive(xQueue, &xReceivedStruct, (TickType_t)QUEUE_WAITS) == pdPASS) {
                if (xReceivedStruct->eRequestID == pData->eDataID) {
                    printf("SUCCEEDED -- I'm %s --- Received from %s task, data = %ld\n", pData->cTaskName, xReceivedStruct->cMessage, xReceivedStruct->lDataValue);

                    free(xReceivedStruct);
                } else {
                    printf("WARNING -- I'm %s: Received from %s, but it's not my task\n",pData->cTaskName, xReceivedStruct->cMessage);
                    if (xReceivedStruct->rejectTimes < TaskCount - 1) {
                        xReceivedStruct->rejectTimes++;
                        xQueueSendToFront(xQueue, (void *)&xReceivedStruct, (TickType_t)10);
                    } else {
                        printf("REJECTED -- This task %s is rejected %d times, skiping the task\n", xReceivedStruct->cMessage, (xReceivedStruct->rejectTimes + 1));
                        free(xReceivedStruct);
                    }
                }
            } else {
                // Handle empty queue
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    xQueue = xQueueCreate(QUEUE_SIZE, sizeof(struct QueueData *));

    // create sender task
    xTaskCreate(&vSenderTask, "Sender Task", 2048, NULL, 2, NULL);

    // create functional task
    xTaskCreate(&vReceiverTask, "CAN Task", 2048, (void *)&CAN, 2, NULL);
    xTaskCreate(&vReceiverTask, "HMI Task", 2048, (void *)&HMI, 2, NULL);
    xTaskCreate(&vReceiverTask, "SPI Task", 2048, (void *)&SPI, 2, NULL);
}