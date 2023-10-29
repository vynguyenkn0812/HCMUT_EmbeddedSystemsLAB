/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"


char msg[] = "This is our text to testing LAB3";

TaskHandle_t task1 = NULL;
TaskHandle_t task2 = NULL;

void task1(){
    int len = strlen(msg);
    while(true){
        for(int i=0; i < len; i+=1){
            printf("%c",msg[i]);
        }
        printf("\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2(){
    while(true){
        printf("*");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    xTaskCreate(task1, "task1", 2048, NULL, 1, &task1);
    xTaskCreate(task2, "task2", 2048, NULL, 2, &task2);


}
