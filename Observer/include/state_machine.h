#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "observer_config.h"

struct STATE_DATA {
    uint8_t target_lgh;
    uint8_t ack_index;
};

enum STATES {
    INITIAL = 0,
    QUERY_POSITIONS = 1,
    QUERY_DISTANCES = 2,
};

enum STATE_MACHINE_ERRORS {
  INEXISTING_STATE,
  WRONG_TRANSITION,
};

const uint8_t MAX_ACK_NUMBER = 5;

extern STATES current_state;
extern STATE_DATA current_state_data;

void Reset_And_Initialize_Machine();
void State_Machine_Error(STATE_MACHINE_ERRORS error);

void Change_State(STATES new_state);
void State_Enter();
void State_ReceiveCallback(const uint8_t* data, int dataLen);
void State_SentCallback();
void State_TimerCallback(TIMER_CALLBACKS timer_callback);
void State_SailorCommand(SAILOR_COMMANDS command);
void State_UWB_New_Range(uint16_t device, float range, float rx_power);
void State_Exit();

void Initial_Enter();
void Initial_ReceiveCallback(const uint8_t* data, int dataLen);
void Initial_SentCallback();
void Initial_TimerCallback(TIMER_CALLBACKS timer_callback);
void Initial_SailorCommand(SAILOR_COMMANDS command);
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power);
void Initial_Exit();

void Query_Positions_Enter();
void Query_Positions_ReceiveCallback(const uint8_t* data, int dataLen);
void Query_Positions_SentCallback();
void Query_Positions_TimerCallback(TIMER_CALLBACKS timer_callback);
void Query_Positions_SailorCommand(SAILOR_COMMANDS command);
void Query_Positions_UWB_New_Range(uint16_t device, float range, float rx_power);
void Query_Positions_Exit();

void Query_Distances_Enter();
void Query_Distances_ReceiveCallback(const uint8_t* data, int dataLen);
void Query_Distances_SentCallback();
void Query_Distances_TimerCallback(TIMER_CALLBACKS timer_callback);
void Query_Distances_SailorCommand(SAILOR_COMMANDS command);
void Query_Distances_UWB_New_Range(uint16_t device, float range, float rx_power);
void Query_Distances_Exit();


#endif