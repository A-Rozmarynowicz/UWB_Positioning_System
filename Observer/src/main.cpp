#include "observer_config.h"

void setup() {
  Serial.begin(115200);
  Serial.printf("Inited serial to PC\n");
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
  if (Is_Ack_Timer_Triggered()){
    Handle_Ack_Timer_Callback();
  }
  if (Is_New_Range_Received()) {
    Handle_Last_Range_Callback();
  }
}
