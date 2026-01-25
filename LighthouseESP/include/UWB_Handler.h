/**
 * @file UWB_Handler.h
 * @brief UWB (Ultra Wide Band) initialization and handling utilities.
 *
 * This module provides configuration and helper functions for DW1000-based UWB
 * communication. It includes initialization, enabling/disabling, address
 * conversion and callback handlers for UWB events.
 */

#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include "LighthouseConfig.h"
#include <SPI.h>
#include "DW1000Ranging.h"

#define UWB_ADDRESS_LENGTH 8

/** @defgroup ConnectionPins Connection Pins
 *  @brief SPI connection pins.
 *  @{
 */
const int8_t PIN_RST = 22;  // reset pin
const int8_t PIN_IRQ = 33;   // irq pin
const int8_t PIN_SS = 5;    // spi select pin

const int8_t PIN_MOSI = 23;
const int8_t PIN_MISO = 19;
const int8_t PIN_SCK = 18;
/** @} */

/**
 * @brief UWB addresses for each lighthouse.
 */
extern const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH];

/**
 * @brief UWB enable flag.
 */
extern uint8_t uwb_enable;

void Initialize_UWB();
void Update_UWB();
void Restart_UWB_As_Tag();
void Restart_UWB_As_Anchor();

uint8_t Is_UWB_Enabled();
void Disable_UWB();
void Enable_UWB();

uint16_t Get_Short_Address_From_Long(const uint8_t* address);
int8_t Get_LGH_From_Short_Address(const uint16_t short_address);
int8_t Get_LGH_From_Address(const uint8_t* address);
bool Are_Addresses_Equal(uint8_t* first, uint8_t* second);

// Private
void _new_range();
void _new_blink(DW1000Device* device);
void _new_device(DW1000Device* device);
void _inactive_device(DW1000Device* device);
void _reset_DW1000();

void _format_address_to_string(uint8_t lgh_index, char address_str[24]);

#endif