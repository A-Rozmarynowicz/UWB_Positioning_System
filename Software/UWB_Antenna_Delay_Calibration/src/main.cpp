#include <Arduino.h>
#include <SPI.h>
// #include "DW1000Ranging.h"
#include "UWB_Handler.h"
#include "Calculations.h"


const uint8_t UWB_MODE_SELECT_PIN = 32;
const uint8_t ANTENNA_DELAY_VALUE_SELECT_PIN = 27;

bool done = false;

void setup() {
  Serial.begin(115200);
  pinMode(UWB_MODE_SELECT_PIN, INPUT_PULLDOWN);
  pinMode(ANTENNA_DELAY_VALUE_SELECT_PIN, INPUT_PULLDOWN);
  delay(100);

  if (digitalRead(UWB_MODE_SELECT_PIN))
  {
    UWB_mode = TAG;
    Serial.println("TAG");
  }
  else {
    UWB_mode = ANCHOR;
    Serial.println("ANCHOR");
  }

  if (digitalRead(ANTENNA_DELAY_VALUE_SELECT_PIN))
  {
    Set_Antenna_Value(MANUAL_ANTENNA_DELAY_VALUE);
  }
  else
  {
    Set_Antenna_Value(BASE_ANTENNA_DELAY_VALUE);
  }

  Serial.printf("Antenna value: %d \n", antenna_value);

  Init_UWB();
}

void loop() {
  if (done){return;}
  DW1000Ranging.loop();
  if (Is_Enough_Measurements() && (UWB_mode == TAG)){
    done = true;
    Disable_UWB();
    Estimate_Distance();
    Serial.printf("Distance estimation: %0.3fm \n", Get_Estimated_Distance());
  }
}

