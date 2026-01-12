#ifndef SAILOR_COMM_H
#define SAILOR_COMM_H

#include "observer_config.h"

#define SAILOR_MESSAGE_SIZE 16

enum OBSERVER_INFO_SETUP {
	OBS_ERROR_CODE = 0,
	OBS_POSITION_STRUCT = 4,
};

enum SAILOR_COMMANDS {

};


void Initialize_Sailor_Comm();
void Send_Current_Position(Position* current_pos);

#endif