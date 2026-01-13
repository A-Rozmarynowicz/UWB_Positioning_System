#include "state_machine.h"

STATES current_state = STATES::INITIAL;
STATE_DATA current_state_data = {0};

void Reset_And_Initialize_Machine(){
  current_state = STATES::INITIAL;
  current_state_data = {0};
  State_Enter();
};

void Change_State(STATES new_state){
  Serial.printf("Switching from state %d to state %d  \n ---------------- \n", current_state, new_state);
  State_Exit();
  current_state = new_state;
  State_Enter();
};

void State_Enter(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_Enter();
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_Enter();
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_Enter();
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_ReceiveCallback(const uint8_t* data, int dataLen){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_ReceiveCallback(data, dataLen);
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_ReceiveCallback(data, dataLen);
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_ReceiveCallback(data, dataLen);
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_SentCallback(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_SentCallback();
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_SentCallback();
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_SentCallback();
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_TimerCallback(TIMER_CALLBACKS timer_callback){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_TimerCallback(timer_callback);
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_TimerCallback(timer_callback);
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_TimerCallback(timer_callback);
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_SailorCommand(SAILOR_COMMANDS command){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_SailorCommand(command);
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_SailorCommand(command);
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_SailorCommand(command);
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_Exit(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_Exit();
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_Exit();
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_Exit();
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_UWB_Info() {
  switch (current_state) {
    case STATES::INITIAL:
      Initial_UWB_Info();
      break;
    case STATES::QUERY_POSITIONS:
      Query_Positions_UWB_Info();
      break;
    case STATES::QUERY_DISTANCES:
      Query_Distances_UWB_Info();
      break;
    default:
      State_Machine_Error(STATE_MACHINE_ERRORS::INEXISTING_STATE);
      break;
  }
}

void State_Machine_Error(STATE_MACHINE_ERRORS error){
  // TODO
  Serial.printf("State Machine Error: %d \n", error);
};
