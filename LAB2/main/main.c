/*
 * Created by Nhom 6
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
<<<<<<< HEAD

// include user's libraries
#include "button.h"
#include "global.h"
#include "tasks.h"
=======
#include "FreeRTOSConfig.h"
#include "button.h"
>>>>>>> origin/master

// GPIO Values
#define OFF         0
#define ON          1

<<<<<<< HEAD
// GPIO Pins 
#define BUTTON_PIN  18

// enable interrupt service on pin 18
#define ESP_INTR_FLAG_DEFAULT 18


TaskHandle_t Button_ISR = NULL;
TaskHandle_t Print_ISR = NULL;

void IRAM_ATTR button_gpio_isr_handler(void* arg)
{
    if( is_button_pressed() ){
        xTaskResumeFromISR(vPrintEsp32);
    }
}

=======
void vPrintId()
{
    while (1)
    {
        // Get tick count at wakeup time
        TickType_t xLastWakeupTime = xTaskGetTickCount();

        printf("%s", "Student ID: 2014725\r\n");
        xTaskDelayUntil(&xLastWakeupTime, 1000 / portTICK_PERIOD_MS);
    }
}

void IRAM_ATTR button_isr_handler(void *arg)
{
    if (is_button_pressed()) xTaskResumeFromISR(ISR);
}
>>>>>>> origin/master


void app_main(void){
    // Initialize GPIO pins =======
    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
    // ============================

<<<<<<< HEAD
    // Set GPIO directions ========
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // ============================

    // Set buttons mode ===========
    gpio_set_pull_mode (BUTTON_PIN, GPIO_PULLUP_ONLY) ;
    // ============================
=======
    // Set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

    // Enable interrupt on falling (1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);
>>>>>>> origin/master

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

<<<<<<< HEAD
    //hook isr handler for specific gpio pin again
    gpio_isr_handler_add(BUTTON_PIN, button_gpio_isr_handler, NULL);


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
                    &Button_ISR             // none taskHandle
                );

    // Start Scheduler
    vTaskStartScheduler(void);
=======
    // Attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);

    // Create 2 FreeRTOS tasks
    xTaskCreate(vPrintId, "print id", 2048, NULL, 1, NULL);
    xTaskCreate(vButtonIsr, "button isr", 2048, NULL, 1, &ISR);
>>>>>>> origin/master
}