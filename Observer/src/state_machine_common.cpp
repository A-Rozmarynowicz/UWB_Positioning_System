#include "state_machine.h"

States current_state = States::INITIAL;
State_Data current_state_data = {0};

void Reset_And_Initialize_Machine(){
  current_state = States::INITIAL;
  current_state_data = {0};
  State_Enter();
};

void Change_State(States new_state){
  Serial.printf("Switching from state %d to state %d  \n ---------------- \n", current_state, new_state);
  State_Exit();
  current_state = new_state;
  State_Enter();
};

void State_Enter(){
  switch (current_state) {
    case States::INITIAL:
      Initial_Enter();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_Enter();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_Enter();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_ReceiveCallback(const uint8_t* data, int dataLen){
  switch (current_state) {
    case States::INITIAL:
      Initial_ReceiveCallback(data, dataLen);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_ReceiveCallback(data, dataLen);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_ReceiveCallback(data, dataLen);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_SentCallback(){
  switch (current_state) {
    case States::INITIAL:
      Initial_SentCallback();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_SentCallback();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_SentCallback();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_TimerCallback(Timer_Callbacks timer_callback){
  switch (current_state) {
    case States::INITIAL:
      Initial_TimerCallback(timer_callback);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_TimerCallback(timer_callback);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_TimerCallback(timer_callback);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_SailorCommand(Sailor_Commands command){
  switch (current_state) {
    case States::INITIAL:
      Initial_SailorCommand(command);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_SailorCommand(command);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_SailorCommand(command);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_Exit(){
  switch (current_state) {
    case States::INITIAL:
      Initial_Exit();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_Exit();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_Exit();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_UWB_New_Range(uint16_t device, float range, float rx_power) {
  switch (current_state) {
    case States::INITIAL:
      Initial_UWB_New_Range(device, range, rx_power);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_UWB_New_Range(device, range, rx_power);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_UWB_New_Range(device, range, rx_power);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
}

void State_Machine_Error(State_Machine_Errors error){
  // TODO
  Serial.printf("State Machine Error: %d \n", error);
};
