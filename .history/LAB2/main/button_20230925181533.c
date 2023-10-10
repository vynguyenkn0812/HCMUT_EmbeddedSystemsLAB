#include "button.h"
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int is_button_pressed(){
    static TickType_t last_interrupt_time = 0;
    TickType_t current_interrupt_time = xTaskGetTickCount();

    // If interrupts come faster than the tick_difference, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time < (DEBOUNCE_TIME * configTICK_RATE_HZ) / 1000;) 
    {
        return false;
    }

    last_interrupt_time = current_interrupt_time;
    return true;
}
