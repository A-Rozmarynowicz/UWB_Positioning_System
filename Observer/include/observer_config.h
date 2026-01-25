/**
 * @file observer_config.h
 * @brief Global configuration and shared type definitions.
 *
 * @details
 * This header defines global constants, enums, and shared structures used
 * across the project. It also includes all other module headers to ensure
 * consistent access to configuration and interfaces.
 *
 * It provides:
 * - Global system constants (e.g., number of lighthouses, device ID)
 * - Shared data structures (e.g., Position)
 * - Common enums used by multiple modules
 * - Includes for all other project headers
 */

#ifndef OBSERVER_CONFIG_H
#define OBSERVER_CONFIG_H

/**
 * @brief Total number of lighthouses in the system.
 */
#define NUMBER_OF_LIGHTHOUSES 4

/**
 * @brief Unique ID of this device (sailor).
 */
#define SAILOR_ID 169

/**
 * @brief Timer callback identifiers.
 */
enum Timer_Callbacks {
  ACK,
};

/**
 * @brief Commands available to the sailor device.
 */
enum Sailor_Commands {
	cmd_s_1 = 0,
};

/**
 * @brief 3D position structure used throughout the system.
 */
typedef struct Position {
    float x;
    float y;
    float z;
} Position;

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "state_machine.h"
#include "timing.h"
#include "sailor_comm.h"
#include "communication.h"
#include "uwb_handler.h"
#include "calculations.h"
#include "interface.h"

#endif