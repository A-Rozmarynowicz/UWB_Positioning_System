/**
 * @file states_functions.h
 * @brief Helper functions for managing lighthouse indices.
 *
 * @details
 * This header provides helper utilities for manipulating the current target
 * lighthouse index used in state machine operations.
 *
 * It contains:
 * - A function for incrementing the target lighthouse index
 */

#ifndef STATES_FUNCTIONS_H
#define STATES_FUNCTIONS_H

#include "observer_config.h"

void Increment_Target_LGH(uint8_t* index);

#endif