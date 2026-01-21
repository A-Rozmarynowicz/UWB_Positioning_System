#ifndef OBSERVER_CONFIG_H
#define OBSERVER_CONFIG_H

#define NUMBER_OF_LIGHTHOUSES 4
#define SAILOR_ID 169

enum Timer_Callbacks {
  ACK,
};

enum Sailor_Commands {
	cmd_s_1 = 0,
};

typedef struct Position {
    float x;
    float y;
    float z;
} Position;

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "state_machine.h"
#include "timing.h"
#include "sailor_comm.h"
#include "communication.h"
#include "uwb_handler.h"
#include "calculations.h"
#include "interface.h"

#endif