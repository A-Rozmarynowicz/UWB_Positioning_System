#ifndef INTERFACE_H
#define INTERFACE_H
#include "LighthouseConfig.h"

#define DATA_TRANSFER_LED (uint8_t) 2

void Initialize_Interface();

void Data_Transfer_LED_ON();
void Data_Transfer_LED_OFF();

#endif