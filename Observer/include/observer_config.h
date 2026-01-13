#ifndef OBSERVER_CONFIG_H
#define OBSERVER_CONFIG_H

#define NUMBER_OF_LIGHTHOUSES 4
#define SAILOR_ID 169

enum TIMER_CALLBACKS {
  ACK,
};

enum SAILOR_COMMANDS {
	cmd_s_1 = 0,
};

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "state_machine.h"
#include "timing.h"
#include "sailor_comm.h"
#include "communication.h"
#include "uwb_handler.h"
#include "calculations.h"

#endif