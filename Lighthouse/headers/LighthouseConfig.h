#ifndef LIGHTHOUSECONFIG_H
#define LIGHTHOUSECONFIG_H
#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "Timing.h"
#include "StateMachine.h"
#include "Communication.h"

#define LIGHTHOUSE_ID (uint8_t) 0
#define CLOCK_PERIOD (double) 1/(240E+6)

const uint8_t NUMBER_OF_LIGHTHOUSES = 4;

#endif