#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "timing.h"

hw_timer_t* ack_timer = NULL;

void Initialize_Timers(){
    ack_timer = timerBegin(1, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_Ack_Timer();
    timerAttachInterrupt(ack_timer, &_on_ack_timer_timeout, true);
    timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(ack_timer);
  };

void IRAM_ATTR _on_ack_timer_timeout(){
  Stop_Ack_Timer();
  State_TimerCallback(Timer_Callbacks::ACK);
};

void Start_Ack_Timer(){
  timerStart(ack_timer);
}

void Stop_Ack_Timer(){
  timerStop(ack_timer);
}