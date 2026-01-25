/**
 * @file main.cpp
 *
 * @brief Entry point of the firmware.
 * @author Arkadiusz Rozmarynowicz
 * @date 01.2026
 *
 * @details
 *
 * This file contains the main setup and loop functions for the
 * ESP32-based lighthouse system.
 *
 * The application initializes peripherals, starts the state machine,
 * and handles periodic updates.
 */

#include "observer_config.h"

void setup() {
  Serial.begin(115200);
  Serial.printf("Inited serial to PC\n");
  Initialize_Timers();
  Initialize_Sailor_Comm();
  Serial.printf("Initialized Sailor Comm\n");
  Initialize_Communication();
  Serial.printf("Initialized ESP NOW\n");
  Reset_And_Initialize_Machine();
  Serial.printf("Inited state machine\n");
  Initialize_UWB();
  Serial.printf("Inited UWB");
  Initialize_Interface();
}

void loop() {
  if (Is_UWB_Enabled()){
    Update_UWB();
  }
}
