#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h" // TODO tutaj Timers.h

hw_timer_t* uwb_restart_ack_timer = NULL;
hw_timer_t* ack_timer = NULL;

void Initialize_Timers(){
    uwb_restart_ack_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_UWB_Restart_Ack_Timer();
    timerAttachInterrupt(uwb_restart_ack_timer, &On_UWB_Restart_Ack_Timer_Timeout, true);
    timerAlarmWrite(uwb_restart_ack_timer, BURST_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(uwb_restart_ack_timer);

    ack_timer = timerBegin(1, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    Stop_Ack_Timer();
    timerAttachInterrupt(ack_timer, &On_Ack_Timer_Timeout, true);
    timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(ack_timer);
  };

void IRAM_ATTR On_UWB_Restart_Ack_Timer_Timeout(){
  Stop_UWB_Restart_Ack_Timer();
  State_TimerCallback(TIMER_CALLBACKS::UWB_RESTART_ACK);
};

void IRAM_ATTR On_Ack_Timer_Timeout(){
  Stop_Ack_Timer();
  State_TimerCallback(TIMER_CALLBACKS::ACK);
};

void Start_UWB_Restart_Ack_Timer(){
  timerStart(uwb_restart_ack_timer);
};

void Stop_UWB_Restart_Ack_Timer(){
  timerStop(uwb_restart_ack_timer);
};

void Start_Ack_Timer(){
  timerStart(ack_timer);
}

void Stop_Ack_Timer(){
  timerStop(ack_timer);
}