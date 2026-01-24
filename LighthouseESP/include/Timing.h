#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h"

enum Timer_Callbacks {
  UWB_ACTIVATION,
  ACK,
};

const uint16_t UWB_ACTIVATION_TIMER_PERIOD_MS = 150;
const uint16_t ACK_TIMER_PERIOD_MS = 25;

extern hw_timer_t* uwb_activation_timer;
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