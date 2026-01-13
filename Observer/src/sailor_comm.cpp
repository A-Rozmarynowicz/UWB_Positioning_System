#include "sailor_comm.h"
#include <string.h>

void Initialize_Sailor_Comm(){
    Serial2.begin(9600, SERIAL_8N1);
}

void Send_Current_Position(Position* current_pos) {
    uint8_t message[SAILOR_MESSAGE_SIZE] = {0};
    memcpy(&(message[OBS_POSITION_STRUCT]), current_pos, sizeof(Position));
    Serial2.write(message, SAILOR_MESSAGE_SIZE);
}
