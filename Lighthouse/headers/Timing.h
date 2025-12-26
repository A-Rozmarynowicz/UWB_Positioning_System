#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h"

enum TIMER_CALLBACKS {
  MS_10=0,
};

extern hw_timer_t* ms10_timer;
extern uint8_t czas;

void IRAM_ATTR On_ms10_Timer_Timeout();
void Initialize_Timers();

void Start_ms10_Timer();
void Stop_ms10_Timer();

#endif