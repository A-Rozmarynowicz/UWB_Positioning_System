/**
 * @file timing.h
 * @brief Timer initialization and management for ACK handling.
 *
 * @details
 * This header defines the timer used for ACK timeout handling and provides
 * functions to initialize, start, stop, and handle errors related to the
 * timing system.
 *
 * It contains:
 * - Constants for timer periods
 * - External timer handle declarations
 * - Public timer control functions
 * - Private ISR callback declaration
 */

#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "observer_config.h"

const uint16_t ACK_TIMER_PERIOD_MS = 25;
extern hw_timer_t* ack_timer;

// Public
void Initialize_Timers();
void Start_Ack_Timer();
void Stop_Ack_Timer();
void Timing_Error();

// Private
void IRAM_ATTR _on_ack_timer_timeout();

#endif