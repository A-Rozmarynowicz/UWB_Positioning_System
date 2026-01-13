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
  Initialize_UWB();
  Serial.printf("Inited UWB");
  // Update_LGH_Position(0, 0, 0, 0);
  // Update_LGH_Position(1, 1, 0, 0);
  // Update_LGH_Position(2, 0.5, 0.866, 0);
  // Update_LGH_Position(3, 0.5, 0.866/3.0, 0.8165);

  // Update_Distance_To_LGH(0, 1.0);
  // Update_Distance_To_LGH(1, 1.0);
  // Update_Distance_To_LGH(2, 1.0);
  // Update_Distance_To_LGH(3, 0.8165*2.0);

  pinMode(2, OUTPUT);
}

void loop() {
  if (Is_UWB_Enabled()){
    
  }
}
