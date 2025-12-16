#ifndef TIMING_H
#define TIMING_H
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h"

extern hw_timer_t* response_await_timer;
extern uint8_t czas;

void IRAM_ATTR On_Response_Await_Timer_Timeout();
void Initialize_Timers();

void Start_Response_Await_Timer();
void Stop_Response_Await_Timer();

#endif