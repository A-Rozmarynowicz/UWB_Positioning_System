#ifndef LIGHTHOUSECONFIG_H
#define LIGHTHOUSECONFIG_H

#define NUMBER_OF_LIGHTHOUSES (uint8_t) 4
#define OBSERVER_ID 169

#define INDEX_PIN_2 (uint8_t) 27
#define INDEX_PIN_1 (uint8_t) 26
#define INDEX_PIN_0 (uint8_t) 25

#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "Timing.h"
#include "StateMachine.h"
#include "Communication.h"
#include "Measure.h"
#include "States.h"
#include "Interface.h"
#include "UWB_Handler.h"

const uint32_t CYCLE_COUNT_MAX = 4294967295;

extern uint8_t LIGHTHOUSE_ID;

#endif