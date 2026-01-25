/**
 * @file Interface.h
 * @brief Hardware interface abstraction for LEDs and user button.
 *
 * @details
 * This header defines the hardware interface used by the Lighthouse system,
 * including status LEDs and a user button. It provides constants describing
 * GPIO assignments and declares public and private interface-related functions.
 *
 * The interface layer is responsible for:
 * - Initializing GPIOs used for LEDs and button input
 * - Visual indication of system status and data transfer activity
 * - Handling button interrupts
 */

#ifndef INTERFACE_H
#define INTERFACE_H
#include "LighthouseConfig.h"

/**
 * @brief GPIO pin used to indicate data transfer activity.
 */
#define DATA_TRANSFER_LED (uint8_t) 2

/**
 * @brief GPIO pin used to indicate error states.
 */
#define ERROR_LED (uint8_t) 2

/**
 * @brief GPIO pin connected to the status button.
 */
#define STATUS_BUTTON (uint8_t) 4

// Public
void Initialize_Interface();
void Blink_LED();
void Data_Transfer_LED_ON();
void Data_Transfer_LED_OFF();
void Error_LED_On();

// Private
void ICACHE_RAM_ATTR _button_ISR();

#endif