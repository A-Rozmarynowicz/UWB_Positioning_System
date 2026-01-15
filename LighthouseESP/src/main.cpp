#include "LighthouseConfig.h"
#include "esp_pm.h"
#include "esp_wifi.h"


void ICACHE_RAM_ATTR buttonISR();
void setup();
void loop();

uint8_t LIGHTHOUSE_ID = 0;

void ICACHE_RAM_ATTR buttonISR() {
  State_Button_Callback(STATUS_BUTTON);
}

void setup() {
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
  Initialize_UWB();
  Serial.println("UWB Initialized");
  Reset_And_Initialize_Machine();
  Serial.println("Machine Initialized");

  pinMode(STATUS_BUTTON, INPUT_PULLUP);
  attachInterrupt(STATUS_BUTTON, buttonISR, RISING);

  setCpuFrequencyMhz(240);

  esp_pm_lock_handle_t cpu_freq_lock;
  esp_pm_lock_handle_t apb_freq_lock;
  esp_pm_lock_handle_t no_light_sleep_lock;

  esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "cpu_freq_lock_name", &cpu_freq_lock);
  esp_pm_lock_acquire(cpu_freq_lock);

  esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "apb_freq_lock_name", &apb_freq_lock);
  esp_pm_lock_acquire(apb_freq_lock);

  esp_pm_lock_create(ESP_PM_NO_LIGHT_SLEEP, 0, "no_light_sleep_lock_name", &no_light_sleep_lock);
  esp_pm_lock_acquire(no_light_sleep_lock);
  esp_wifi_set_ps(WIFI_PS_NONE);
}

void loop(){
  if (Is_UWB_Enabled){
    Update_UWB();
  }
}