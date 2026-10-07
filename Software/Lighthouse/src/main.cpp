/**
 * @file main.cpp
 *
 * @brief Initialization and main control program for a UWB Lighthouse.
 * @author Arkadiusz Rozmarynowicz
 * @date 01.2026
 *
 * @details
 * This program is designed for an ESP32 microcontroller acting as a UWB
 * lighthouse device. It is responsible for:
 * - Reading the lighthouse identifier (LIGHTHOUSE_ID) from three configuration
 *   pins configured as INPUT_PULLDOWN.
 * - Initializing hardware interfaces, timers, communication modules, and the
 *   UWB subsystem.
 * - Resetting and initializing the internal state machine controlling the
 *   lighthouse operation.
 * - Periodically updating the UWB subsystem in the main program loop.
 *
 * The application is built using the Arduino framework for ESP32.
 */


#include "LighthouseConfig.h"
#include "esp_pm.h"
#include "esp_wifi.h"

void setup();
void loop();

const uint8_t LIGHTHOUSE_ID = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Began");
  delay(10);


  Initialize_Interface();
  Initialize_Timers();
  Initialize_Communication();
  Initialize_UWB();
  Reset_And_Initialize_Machine();

  Serial.printf("LIGHTHOUSE_ID: %d \n", LIGHTHOUSE_ID);
  Serial.printf("Number of lighthouses: %d \n", NUMBER_OF_LIGHTHOUSES);


  // setCpuFrequencyMhz(240);

  // esp_pm_lock_handle_t cpu_freq_lock;
  // esp_pm_lock_handle_t apb_freq_lock;
  // esp_pm_lock_handle_t no_light_sleep_lock;

  // esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "cpu_freq_lock_name", &cpu_freq_lock);
  // esp_pm_lock_acquire(cpu_freq_lock);

  // esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "apb_freq_lock_name", &apb_freq_lock);
  // esp_pm_lock_acquire(apb_freq_lock);

  // esp_pm_lock_create(ESP_PM_NO_LIGHT_SLEEP, 0, "no_light_sleep_lock_name", &no_light_sleep_lock);
  // esp_pm_lock_acquire(no_light_sleep_lock);
  // esp_wifi_set_ps(WIFI_PS_NONE);
}

void loop(){
  if (Is_UWB_Enabled){
    Update_UWB();
  }
}