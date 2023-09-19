/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#define CONFIG_LED_PIN 2
#define ESP_INTR_FLAG_DEFAULT 0
#define CONFIG_BUTTON_PIN 0

static StaticTask_t xCheckTask;

static StackType_t ucTaskStack[ configMINIMAL_STACK_SIZE * sizeof( StackType_t ) ];

TaskHandle_t ISR = NULL;

void vPrintId() 
{
    printf("%s", "2014725");
    vTaskDelay(1000);
}

void IRAM_ATTR button_isr_handler(void* arg) {
    xTaskResumeFromISR(ISR);
}

void vButtonIsr(void *arg)
{
    bool led_status = false;
    while(1){  
        vTaskSuspend(NULL);
        led_status = !led_status;
        gpio_set_level(CONFIG_LED_PIN, led_status);
        printf("Button pressed!!!\n");
    }
}

void app_main(void)
{
    esp_rom_gpio_pad_select_gpio(CONFIG_BUTTON_PIN);
    esp_rom_gpio_pad_select_gpio(CONFIG_LED_PIN);

    // set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(CONFIG_LED_PIN, GPIO_MODE_OUTPUT);

    // enable interrupt on falling (1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);


    // Install the driver’s GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
    // install ISR service with default configuration
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);

    xTaskCreateStatic(vPrintId, "print id", configMINIMAL_STACK_SIZE, NULL, 1, ucTaskStack, &xCheckTask);
    xTaskCreate( vButtonIsr, "button_task", configMINIMAL_STACK_SIZE, NULL , 10, &ISR );
    esp_restart();
}
