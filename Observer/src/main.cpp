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

  Update_LGH_Position(0, 0, 0, 0);
  Update_LGH_Position(1, 1, 0, 0);
  Update_LGH_Position(2, 0.5, 0.866, 0);
  Update_LGH_Position(3, 0.5, 0.866/3.0, 0.8165);

  Update_Distance_To_LGH(0, 1.0);
  Update_Distance_To_LGH(1, 1.0);
  Update_Distance_To_LGH(2, 1.0);
  Update_Distance_To_LGH(3, 0.8165*2.0);

  Build_A_Matrix();
  Build_AT_Matrix();
  Build_ATA_Matrix();
  Build_ATA_Inv_Matrix();
  Build_B_Vector_Constants();
  Build_B_Vector();
  Calculate_ATB_Matrix();
  Calculate_Solution();
  pinMode(2, OUTPUT);
}

void loop() {}
