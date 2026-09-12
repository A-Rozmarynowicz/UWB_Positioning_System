#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H
#include <Arduino.h>
#include "DW1000Ranging.h"
#include "Calculations.h"

const byte CHANNEL = DW1000.CHANNEL_2;
extern const byte* UWB_TRANSMIT_MODE;
const uint16_t MANUAL_ANTENNA_DELAY_VALUE = 0;

const uint16_t BASE_ANTENNA_DELAY_VALUE = 16350;
// connection pins
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

extern uint8_t UWB_mode;
extern uint16_t antenna_value;

void Set_Antenna_Value(uint16_t new_val);
void Init_UWB();
void New_Range();
void New_Blink(DW1000Device* device);
void Inactive_Device(DW1000Device* device);
void Disable_UWB();

#endif