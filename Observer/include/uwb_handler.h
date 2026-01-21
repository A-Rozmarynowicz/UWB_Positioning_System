#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include <SPI.h>
#include "DW1000Ranging.h"
#include "observer_config.h"

#define UWB_ADDRESS_LENGTH 8

extern const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH];

// connection pins
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

const int8_t PIN_MOSI = 23;
const int8_t PIN_MISO = 19;
const int8_t PIN_SCK = 18;

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