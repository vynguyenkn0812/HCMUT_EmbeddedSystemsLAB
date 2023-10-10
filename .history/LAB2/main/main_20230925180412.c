/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "FreeRTOSConfig.h"
#include <inttypes.h>
#include "esp_rom_gpio.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

// include user's libraries
#include "button.h"
#include "global.h"
#include "tasks.h"

// GPIO Values
#define OFF         0
#define ON          1

// GPIO Pins 
#define BUTTON_PIN  18

// enable interrupt service on pin 18
#define ESP_INTR_FLAG_DEFAULT 18


TaskHandle_t Button_ISR = NULL;
TaskHandle_t Print_ISR = NULL;

void IRAM_ATTR button_gpio_isr_handler(void* arg)
{
    if( is_button_pressed(int (arg)) ){
        
    }
}



void app_main(void){
    // Initialize GPIO pins =======
    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
    // ============================

    // Set GPIO directions ========
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // ============================

    // Set buttons mode ===========
    gpio_set_pull_mode (BUTTON_PIN, GPIO_PULLUP_ONLY) ;
    // ============================

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    //hook isr handler for specific gpio pin again
    gpio_isr_handler_add(BUTTON_PIN, button_gpio_isr_handler, (void*) BUTTON_PIN);


    // Create 2 tasks
    xTaskCreate(    
                    vPrintStudentID,        // function
                    "print Student ID",     // name to easily debug
                    2048,                   // stack allocate
                    NULL,                   // none parameter
                    1,                      // equal priority
                    &Print_ISR              // none taskHandle
                );

    xTaskCreate(    
                    vPrintEsp32,            // function
                    "print ESP32",          // name to easily debug
                    2048,                   // stack allocate
                    NULL,                   // none parameter
                    1,                      // equal priority
                    &Print_ISR              // none taskHandle
                );

    // Start Scheduler
    vTaskStartScheduler(void);
}