#include <Arduino.h>
#include "esp32-hal-timer.h"

hw_timer_t* burst_timer = NULL;

void Start_Burst_Timer();
void Stop_Burst_Timer();
void IRAM_ATTR On_Burst_Timer_Timeout();

void setup() {
  burst_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz // TODO obsługa błędów
  Stop_Burst_Timer();
  timerAttachInterrupt(burst_timer, &On_Burst_Timer_Timeout, true);
  timerAlarmWrite(burst_timer, 1000*10, true);
  timerAlarmEnable(burst_timer);

  Serial2.begin(9600, SERIAL_8N1);
  Serial.begin(115200);
  Start_Burst_Timer();
  pinMode(2, OUTPUT);
}

void loop() {

}

void Start_Burst_Timer(){
  timerStart(burst_timer);
};

void Stop_Burst_Timer(){
  timerStop(burst_timer);
};

void IRAM_ATTR On_Burst_Timer_Timeout(){
  // Stop_Burst_Timer();
  digitalWrite(2, !digitalRead(2));
  float x = 0.69;
  float y = 4.20;
  float z = 1.23;
  uint8_t message[12] = {0};
  memcpy(&(message[0]), &x, sizeof(float));
  memcpy(&(message[4]), &y, sizeof(float));
  memcpy(&(message[8]), &z, sizeof(float));
  Serial2.write(message, 12);
  Serial.println("Wyslano");

  Start_Burst_Timer();
};