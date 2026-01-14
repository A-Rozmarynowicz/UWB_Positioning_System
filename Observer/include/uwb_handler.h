#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include <SPI.h>
#include "DW1000Ranging.h"
#include "observer_config.h"

const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

extern char uwb_address[24];

extern uint8_t uwb_enable;

// Public
void Initialize_UWB();
void Update_UWB();
uint8_t Is_UWB_Enabled();
void Disable_UWB();
void Enable_UWB();

// Private
void _new_range();
void _new_device(DW1000Device* device);
void _inactive_device(DW1000Device* device);


#endif