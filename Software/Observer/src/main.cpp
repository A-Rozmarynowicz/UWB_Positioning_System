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
  Initialize_Timers();
  Initialize_Sailor_Comm();
  Initialize_Communication();
  Reset_And_Initialize_Machine();
  Initialize_UWB();
  Initialize_Interface();
}

void loop() {
  if (Is_UWB_Enabled()){
    Update_UWB();
  }
}
