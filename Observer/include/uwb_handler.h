#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include "observer_config.h"

extern uint8_t uwb_enable;

void Initialize_UWB();

uint8_t Is_UWB_Enabled();

void Disable_UWB();
void Enable_UWB();

#endif