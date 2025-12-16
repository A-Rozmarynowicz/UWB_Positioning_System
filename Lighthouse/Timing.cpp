#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "Timing.h"

hw_timer_t* response_await_timer = NULL;
uint8_t czas = 0;

void Initialize_Timers(){
    response_await_timer = timerBegin(0, 80, true); // Źródło zegarów to 80MHz // TODO obsługa błędów 
    Stop_Response_Await_Timer();
    timerAttachInterrupt(response_await_timer, &On_Response_Await_Timer_Timeout, true);
    timerAlarmWrite(response_await_timer, 2e4, true); // 20ms
    timerAlarmEnable(response_await_timer);
 };

void IRAM_ATTR On_Response_Await_Timer_Timeout(){
  Serial.printf("Hello There!\n");
};

void Start_Response_Await_Timer(){
  timerStart(response_await_timer);
};

void Stop_Response_Await_Timer(){
  timerStop(response_await_timer);
};