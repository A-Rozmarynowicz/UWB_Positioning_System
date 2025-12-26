#include "LighthouseConfig.h"

#define STATUS_BUTTON (uint8_t) 4

const uint32_t CYCLE_COUNT_MAX = 4294967295;

void ICACHE_RAM_ATTR buttonISR() {
  Reset_And_Initialize_Machine();
  Serial.println("Machine Inited");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Began");
  delay(10);
  Initialize_Timers();
  Serial.println("Timers Inited");
  Initialize_Communication();
  Serial.println("Communication Inited");

  pinMode(STATUS_BUTTON, INPUT_PULLUP);
  attachInterrupt(STATUS_BUTTON, buttonISR, RISING);
}
 
void loop(){}