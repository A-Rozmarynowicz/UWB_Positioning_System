#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H
#include <Arduino.h>
#include "DW1000Ranging.h"

static constexpr byte CHANNEL = DW1000.CHANNEL_2;
const uint8_t UWB_MODE = ANCHOR; // TAG

// connection pins
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

void Init_UWB();
void New_Range();
void New_Blink(DW1000Device* device);
void Inactive_Device(DW1000Device* device);


#endif