#ifndef UWB_HANDLER_H
#define UWB_HANDLER_H

#include "LighthouseConfig.h"

extern uint8_t uwb_enable;

void Initialize_UWB();
void Restart_UWB_As_Tag();
void Restart_UWB_As_Anchor();

uint8_t Is_UWB_Enabled();

void Disable_UWB();
void Enable_UWB();

#endif