#include "button.h"
#include "driver/gptimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int is_button_pressed(void)
{
    static TickType_t last_interrupt_time = 0;
    TickType_t interrupt_time = xTaskGetTickCount();

    // Calculate time difference in ticks equivalent to 80ms
    TickType_t tick_difference = (DEBOUNCE_TIME * configTICK_RATE_HZ) / 1000;

    // If interrupts come faster than the tick_difference, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time < tick_difference) 
    {
        return false;
    }

    last_interrupt_time = interrupt_time;
    return true;
}

