/*
 * Created by Nhom 6
*/

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "FreeRTOSConfig.h"
#include "button.h"

TaskHandle_t ISR = NULL;

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

    // Set the correct direction
    gpio_set_direction(CONFIG_BUTTON_PIN, GPIO_MODE_INPUT);

    // Enable interrupt on falling (1->0) edge for button pin
    gpio_set_intr_type(CONFIG_BUTTON_PIN, GPIO_INTR_NEGEDGE);

    // Install the driver’s GPIO ISR handler service, which allows per-pin GPIO interrupt handlers.
    // install ISR service with default configuration
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Attach the interrupt service routine
    gpio_isr_handler_add(CONFIG_BUTTON_PIN, button_isr_handler, NULL);

    // Create 2 FreeRTOS tasks
    xTaskCreate(vPrintId, "print id", 2048, NULL, 1, NULL);
    xTaskCreate(vButtonIsr, "button isr", 2048, NULL, 1, &ISR);
}