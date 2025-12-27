#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h"

hw_timer_t* ms10_timer = NULL;
uint8_t czas = 0;

void Initialize_Timers(){
    ms10_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_ms10_Timer();
    timerAttachInterrupt(ms10_timer, &On_ms10_Timer_Timeout, true);
    timerAlarmWrite(ms10_timer, 10*10, true); // 10ms
    timerAlarmEnable(ms10_timer);
 };

void IRAM_ATTR On_ms10_Timer_Timeout(){
  Stop_ms10_Timer();
  State_TimerCallback(TIMER_CALLBACKS::MS_10);
};

void Start_ms10_Timer(){
  timerStart(ms10_timer);
};

void Stop_ms10_Timer(){
  timerStop(ms10_timer);
};