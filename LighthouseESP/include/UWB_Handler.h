#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include "LighthouseConfig.h"
#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

extern const char* uwb_addresses_from_LGH[];

extern uint8_t uwb_enable;

void Initialize_UWB();
void Update_UWB();
void Restart_UWB_As_Tag();
void Restart_UWB_As_Anchor();

uint8_t Is_UWB_Enabled();
void Disable_UWB();
void Enable_UWB();

// Private
void _new_range();
void _new_device(DW1000Device* device);
void _inactive_device(DW1000Device* device);
void _reset_DW1000();

#endif