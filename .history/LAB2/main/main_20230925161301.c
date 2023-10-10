/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "esp_rom_gpio.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"


// GPIO Values
#define OFF         0
#define ON          1


// GPIO Pins 
#define LED_PIN     15
#define BUTTON_PIN 17




void app_main(void){
    // Initialize GPIO pins =======
    gpio_pad_select_gpio(LED_PIN);
    gpio_pad_select_gpio(BUTTON_PIN);
    // ============================

    // Set GPIO directions ========
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // ============================

    // Set buttons mode ===========
    gpio_set_pull_mode (BUTTON_PIN, GPIO_PULLUP_ONLY ) ;
    // ============================
}