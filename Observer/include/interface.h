#ifndef INTERFACE_H
#define INTERFACE_H

#include "observer_config.h"

const uint8_t UWB_EXCHANGE_LED = 2;
const uint8_t ERROR_LED = 2;

void Initialize_Interface();
void Blink_LED();
void Error_LED_On();

#endif