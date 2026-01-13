#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h" // TODO tutaj Timers.h

hw_timer_t* burst_timer = NULL;
hw_timer_t* ack_timer = NULL;

void Initialize_Timers(){
    burst_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_Burst_Timer();
    timerAttachInterrupt(burst_timer, &On_Burst_Timer_Timeout, true);
    timerAlarmWrite(burst_timer, BURST_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(burst_timer);

    ack_timer = timerBegin(1, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_Ack_Timer();
    timerAttachInterrupt(ack_timer, &On_Ack_Timer_Timeout, true);
    timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(ack_timer);
  };

void IRAM_ATTR On_Burst_Timer_Timeout(){
  Stop_Burst_Timer();
  State_TimerCallback(TIMER_CALLBACKS::BURST);
};

void IRAM_ATTR On_Ack_Timer_Timeout(){
  Stop_Ack_Timer();
  State_TimerCallback(TIMER_CALLBACKS::ACK);
};

void Start_Burst_Timer(){
  timerStart(burst_timer);
};

void Stop_Burst_Timer(){
  timerStop(burst_timer);
};

void Start_Ack_Timer(){
  timerStart(ack_timer);
}

void Stop_Ack_Timer(){
  timerStop(ack_timer);
}