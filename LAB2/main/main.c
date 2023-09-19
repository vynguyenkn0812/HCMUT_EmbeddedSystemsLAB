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

TaskHandle_t ISR = NULL;

static void vPrintId()
{
    while (1)
    {
        printf("%s", "2014725\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void IRAM_ATTR button_isr_handler(void *arg)
{
    xTaskResumeFromISR(ISR);
}

void vButtonIsr(void *arg)
{
    while (1)
    {
        vTaskSuspend(NULL);
        printf("ESP32\n");
    }
}

void app_main(void)
{
    esp_rom_gpio_pad_select_gpio(CONFIG_BUTTON_PIN);

    // set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

    // enable interrupt on falling (1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);

    // Install the driver’s GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
    // install ISR service with default configuration
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);

    xTaskCreate(vPrintId, "print id", 4096, NULL, 1, NULL);
    xTaskCreate(vButtonIsr, "button isr", 4096, NULL, 1, &ISR);
}