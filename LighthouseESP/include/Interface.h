#ifndef INTERFACE_H
#define INTERFACE_H
#include "LighthouseConfig.h"

#define DATA_TRANSFER_LED (uint8_t) 2
#define ERROR_LED (uint8_t) 2
#define STATUS_BUTTON (uint8_t) 4


// Public
void Initialize_Interface();
void Blink_LED();
void Data_Transfer_LED_ON();
void Data_Transfer_LED_OFF();
void Error_LED_On();

// Private
void ICACHE_RAM_ATTR _button_ISR();

#endif