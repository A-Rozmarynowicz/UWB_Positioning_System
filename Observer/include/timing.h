#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "observer_config.h"

extern bool ack_timer_triggered;
const uint16_t ACK_TIMER_PERIOD_MS = 25;
extern hw_timer_t* ack_timer;

// Public
void Initialize_Timers();
void Start_Ack_Timer();
void Stop_Ack_Timer();
bool Is_Ack_Timer_Triggered();
void Handle_Ack_Timer_Callback();

// Private
void IRAM_ATTR _on_ack_timer_timeout();

#endif