#include <Arduino.h>
#include "esp32-hal-timer.h"

hw_timer_t* burst_timer = NULL;

void setup() {



  Serial.begin(115200);

  pinMode(2, OUTPUT);
}

void loop() {

}


void IRAM_ATTR On_Burst_Timer_Timeout(){
  // Stop_Burst_Timer();
  digitalWrite(2, !digitalRead(2));
  float x = 0.69;
  float y = 4.20;
  float z = 5.99;
  uint8_t message[16] = {0};
  memcpy(&(message[4]), &x, sizeof(float));
  memcpy(&(message[8]), &y, sizeof(float));
  memcpy(&(message[12]), &z, sizeof(float));
  Serial2.write(message, 16);
  Serial.println("Wyslano");

  Start_Burst_Timer();
};