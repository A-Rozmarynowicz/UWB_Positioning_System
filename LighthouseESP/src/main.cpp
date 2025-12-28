#include "LighthouseConfig.h"

void ICACHE_RAM_ATTR buttonISR();
void setup();
void loop();

uint8_t LIGHTHOUSE_ID = 0;

void ICACHE_RAM_ATTR buttonISR() {
  State_Button_Callback(STATUS_BUTTON);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Began");
  delay(10);

  pinMode(INDEX_PIN_0, INPUT_PULLDOWN);
  pinMode(INDEX_PIN_1, INPUT_PULLDOWN);
  pinMode(INDEX_PIN_2, INPUT_PULLDOWN);

  delay(100);

  uint8_t idx0 = digitalRead(INDEX_PIN_0);
  uint8_t idx1 = digitalRead(INDEX_PIN_1);
  uint8_t idx2 = digitalRead(INDEX_PIN_2);

  LIGHTHOUSE_ID = 4*idx2 + 2*idx1 + 1*idx0;
  Serial.printf("LIGHTHOUSE_ID: %d \n", LIGHTHOUSE_ID);

  Initialize_Interface();
  Serial.println("Interface Inited");
  Initialize_Timers();
  Serial.println("Timers Inited");
  Initialize_Communication();
  Serial.println("Communication Inited");
  Reset_And_Initialize_Machine();
  Serial.println("Machine Initialized");

  pinMode(STATUS_BUTTON, INPUT_PULLUP);
  attachInterrupt(STATUS_BUTTON, buttonISR, RISING);
}

void loop(){}