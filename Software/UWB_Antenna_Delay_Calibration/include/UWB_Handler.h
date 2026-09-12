#pragma once

#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H
#include <Arduino.h>
#include "DW1000Ranging.h"

const byte CHANNEL = DW1000.CHANNEL_2;
const byte* TRANSMIT_MODE = DW1000Class::MODE_LONGDATA_RANGE_ACCURACY;
const uint16_t MANUAL_ANTENNA_DELAY_VALUE = 0;

const uint16_t BASE_ANTENNA_DELAY_VALUE = 16350;
// connection pins
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

extern uint8_t UWB_mode;
extern bool use_default_antenna_delay_value;

void Init_UWB();
void New_Range();
void New_Blink(DW1000Device* device);
void Inactive_Device(DW1000Device* device);


#endif