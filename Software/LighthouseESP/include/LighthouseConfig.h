/**
 * @file LighthouseConfig.h
 * @brief Global configuration header for the Lighthouse system.
 *
 * @details
 * This file contains system-wide configuration constants, hardware pin
 * definitions, and shared includes required by multiple modules of the
 * Lighthouse firmware.
 *
 * It defines:
 * - Global system parameters (number of lighthouses, observer ID)
 * - GPIO pin assignments used to determine the lighthouse identifier
 * - Common framework and module dependencies
 * - Global variables shared across compilation units
 */

#ifndef LIGHTHOUSECONFIG_H
#define LIGHTHOUSECONFIG_H

/**
 * @brief Total number of Lighthouse devices in the system.
 */
#define NUMBER_OF_LIGHTHOUSES (uint8_t) 4

/**
 * @brief Unique identifier of the observer device.
 */
#define OBSERVER_ID 169

/**
 * @brief GPIO pin used as the most significant bit of the lighthouse index.
*/
#define INDEX_PIN_2 (uint8_t) 27

/**
 * @brief GPIO pin used as the middle bit of the lighthouse index.
 */
#define INDEX_PIN_1 (uint8_t) 26

/**
 * @brief GPIO pin used as the least significant bit of the lighthouse index.
 */
#define INDEX_PIN_0 (uint8_t) 25

#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "Timing.h"
#include "StateMachine.h"
#include "Communication.h"
#include "Measure.h"
#include "States.h"
#include "Interface.h"
#include "UWB_Handler.h"

/**
 * @brief Unique identifier of the current Lighthouse device.
 *
 * The value is determined at startup based on the state of index pins.
 */
extern uint8_t LIGHTHOUSE_ID;

#endif