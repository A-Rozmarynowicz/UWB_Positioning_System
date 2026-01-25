/**
 * @file uwb_handler.h
 * @brief UWB (DW1000) initialization and management.
 *
 * @details
 * This header contains constants, external variables and function
 * declarations used to manage the DW1000 UWB module.
 * It provides functions for initialization, update loop handling,
 * enabling/disabling the module, and UWB callbacks.
 */

#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include <SPI.h>
#include "DW1000Ranging.h"
#include "observer_config.h"

/**
 * @brief Length of a UWB address in bytes.
 *
 * UWB uses 64-bit addresses (8 bytes). This constant is used to define
 * address arrays and to perform address comparisons.
 */
#define UWB_ADDRESS_LENGTH 8

/**
 * @brief UWB addresses assigned to each lighthouse.
 *
 * Each lighthouse has a unique 8-byte UWB address.
 * The array index corresponds to the lighthouse ID
 * (0..NUMBER_OF_LIGHTHOUSES-1).
 */
extern const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH];

/** @defgroup ConnectionPins Connection Pins
 * @brief SPI Connection Pins
 * @{
*/
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

const int8_t PIN_MOSI = 23;
const int8_t PIN_MISO = 19;
const int8_t PIN_SCK = 18;
/** @} */

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