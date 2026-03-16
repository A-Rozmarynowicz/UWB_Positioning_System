/**
 * @file Timing.h
 * @brief Timer management module for the Lighthouse system.
 *
 * This module provides initialization and control of hardware timers used for:
 * - UWB activation delays
 * - ACK message timeouts
 *
 * The timers are implemented using ESP32 hardware timers and are used across
 * different state machine transitions.
 */

#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h"

/**
 * @brief Timer callback identifiers.
 *
 * Used to distinguish which timer has triggered in the ISR handlers.
 */
enum Timer_Callbacks {
  UWB_ACTIVATION,
  ACK,
};

/**
 * @brief UWB activation timer period in milliseconds.
 */
const uint16_t UWB_ACTIVATION_TIMER_PERIOD_MS = 150;

/**
 * @brief ACK timeout timer period in milliseconds.
 */
const uint16_t ACK_TIMER_PERIOD_MS = 25;


/**
 * @brief Hardware timer instance used for UWB activation.
 */
extern hw_timer_t* uwb_activation_timer;

/**
 * @brief Hardware timer instance used for ACK timeout.
 */
extern hw_timer_t* ack_timer;

void Initialize_Timers();

void Start_UWB_Activation_Timer();
void Stop_UWB_Activation_Timer();

void Start_Ack_Timer();
void Stop_Ack_Timer();

void Timing_Error();

// Private
void IRAM_ATTR _on_UWB_activation_timer_timeout();
void IRAM_ATTR _on_ack_timer_timeout();

#endif