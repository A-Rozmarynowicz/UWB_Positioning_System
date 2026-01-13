#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "observer_config.h"

const uint16_t ACK_TIMER_PERIOD_MS = 25;

extern hw_timer_t* ack_timer;

void IRAM_ATTR On_Ack_Timer_Timeout();
void Initialize_Timers();

void Start_Ack_Timer();
void Stop_Ack_Timer();

#endif