#include <Arduino.h>
#include "esp32-hal-timer.h"
#include "observer_config.h"

hw_timer_t* burst_timer = NULL;

void setup() {

  Serial.begin(115200);
  Serial.printf("Inited serial to PC\n");
  Initialize_Sailor_Comm();
  Serial.printf("Initialized Sailor Comm\n");
  Reset_And_Initialize_Machine();

  Serial.printf("Inited state machine\n");

  pinMode(2, OUTPUT);
}

void loop() {}
