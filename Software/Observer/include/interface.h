/**
 * @file interface.h
 * @brief Interface utilities for LEDs and basic hardware feedback.
 *
 * @details
 * This header defines constants and public functions used to control the
 * onboard LEDs for status indication.
 *
 * It provides:
 * - Pin assignments for UWB exchange and error indication LEDs
 * - Initialization and control functions for the LEDs
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "observer_config.h"

/**
 * @brief GPIO pin used for UWB exchange indication LED.
 */
const uint8_t UWB_EXCHANGE_LED = 2;

/**
 * @brief GPIO pin used for error indication LED.
 */
const uint8_t ERROR_LED = 2;

void Initialize_Interface();
void Blink_LED();
void Error_LED_On();

#endif