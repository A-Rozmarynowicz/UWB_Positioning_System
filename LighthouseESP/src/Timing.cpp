#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h" // TODO tutaj Timers.h
#include "Timing.h"

hw_timer_t* uwb_activation_timer = NULL;
hw_timer_t* ack_timer = NULL;

void Initialize_Timers(){
    uwb_activation_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    if (uwb_activation_timer == nullptr){
      Timing_Error();
    }
    Stop_UWB_Activation_Timer();
    timerAttachInterrupt(uwb_activation_timer, &_on_UWB_activation_timer_timeout, true);
    timerAlarmWrite(uwb_activation_timer, UWB_ACTIVATION_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(uwb_activation_timer);

    ack_timer = timerBegin(1, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
    if (ack_timer == nullptr){
      Timing_Error();
    }
    Stop_Ack_Timer();
    timerAttachInterrupt(ack_timer, &_on_ack_timer_timeout, true);
    timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(ack_timer);
  };

void IRAM_ATTR _on_UWB_activation_timer_timeout(){
  Stop_UWB_Activation_Timer();
  State_TimerCallback(Timer_Callbacks::UWB_ACTIVATION);
};

void IRAM_ATTR _on_ack_timer_timeout(){
  Stop_Ack_Timer();
  State_TimerCallback(Timer_Callbacks::ACK);
};

void Start_UWB_Activation_Timer(){
  timerStart(uwb_activation_timer);
};

void Stop_UWB_Activation_Timer(){
  timerStop(uwb_activation_timer);
};

void Timing_Error() {
  Serial.printf("Timing ERROR!\n");
  Error_LED_On();
}

void Start_Ack_Timer(){
  timerStart(ack_timer);
}

void Stop_Ack_Timer(){
  timerStop(ack_timer);
}