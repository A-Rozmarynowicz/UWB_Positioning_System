#ifndef SAILOR_COMM_H
#define SAILOR_COMM_H

#include "observer_config.h"

#define SAILOR_MESSAGE_SIZE 16

enum Observer_Info_Setup {
	OBS_ERROR_CODE = 0,
	OBS_POSITION_STRUCT = 4,
};

// Public
void Initialize_Sailor_Comm();
void Send_Current_Position(Position* current_pos);

#endif