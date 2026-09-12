#include <Arduino.h>
#include <SPI.h>
// #include "DW1000Ranging.h"
#include "UWB_Handler.h"
#include "Calculations.h"



void setup() {
  Serial.begin(115200);
  delay(1000);
  //init the configuration

}

void loop() {
  DW1000Ranging.loop();
}

