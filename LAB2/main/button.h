/*
 * Created by Nhom 6
*/

#ifndef BUTTON_H
#define BUTTON_H

#define CONFIG_BUTTON_PIN 0
#define ESP_INTR_FLAG_DEFAULT 0
#define DEBOUNCE_TIME 200  // in ms

int is_button_pressed(void);

#endif