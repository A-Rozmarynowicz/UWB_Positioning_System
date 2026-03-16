/**
 * @file sailor_comm.h
 * @brief Communication interface for the sailor device.
 *
 * @details
 * This header defines constants and data layout used for sending information
 * from the sailor device to the observer (or other nodes).
 *
 * It provides:
 * - Message size constant
 * - Data layout enum for encoding sailor messages
 * - Public function declarations for initialization and sending position
 */

#ifndef SAILOR_COMM_H
#define SAILOR_COMM_H

#include "observer_config.h"

/**
 * @brief Size of a single sailor message in bytes.
 */
#define SAILOR_MESSAGE_SIZE 16

/**
 * @brief Byte offsets for different data fields inside a sailor message.
 */
enum Observer_Info_Setup {
	OBS_ERROR_CODE = 0,
	OBS_POSITION_STRUCT = 4,
};

// Public
void Initialize_Sailor_Comm();
void Send_Current_Position(Position* current_pos);

#endif