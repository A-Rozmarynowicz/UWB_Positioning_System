#include "StateMachine.h"

extern STATES current_state = STATES::INITIAL;
extern uint8_t burst_index = 0;

void Initialize_Machine(){
  State_Enter();
};

void Change_State(STATES new_state){
  Serial.printf("Switching from state %d to state %d  \n", current_state, new_state);
  State_Exit();
  current_state = new_state;
  State_Enter();
};

void State_Enter(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_Enter();
      break;
    case STATES::BURST_QUERY:
      Burst_Query_Enter();
      break;
    case STATES::BURST_RESPONSE:
      Burst_Response_Enter();
      break;
    case STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET: 
      Post_Burst_Check_If_All_LGHS_Set_Enter();
      break;
    case STATES::RELAY_BURST_QUERING:
      Relay_Burst_Quering_Enter();
      break;
    case STATES::INFORM_END_CONFIG:
      Inform_End_Config_Enter();
      break;
    case STATES::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_Enter();
      break;
    case STATES::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_Enter();
      break;
    case STATES::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_Enter();
      break;
    case STATES::SAILOR_RESPONSE:
      Sailor_Response_Enter();
      break;
    default:
      State_Machine_Error(ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::BURST_QUERY:
      Burst_Query_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::BURST_RESPONSE:
      Burst_Response_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET: 
      Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::RELAY_BURST_QUERING:
      Relay_Burst_Quering_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::INFORM_END_CONFIG:
      Inform_End_Config_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_ReceiveCallback(macAddr, data, dataLen);
      break;
    case STATES::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_Enter();
      break;
    case STATES::SAILOR_RESPONSE:
      Sailor_Response_ReceiveCallback(macAddr, data, dataLen);
      break;
    default:
      State_Machine_Error(ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_SentCallback(macAddr, status);
      break;
    case STATES::BURST_QUERY:
      Burst_Query_SentCallback(macAddr, status);
      break;
    case STATES::BURST_RESPONSE:
      Burst_Response_SentCallback(macAddr, status);
      break;
    case STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET: 
      Post_Burst_Check_If_All_LGHS_Set_SentCallback(macAddr, status);
      break;
    case STATES::RELAY_BURST_QUERING:
      Relay_Burst_Quering_SentCallback(macAddr, status);
      break;
    case STATES::INFORM_END_CONFIG:
      Inform_End_Config_SentCallback(macAddr, status);
      break;
    case STATES::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_SentCallback(macAddr, status);
      break;
    case STATES::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_SentCallback(macAddr, status);
      break;
    case STATES::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_SentCallback(macAddr, status);
      break;
    case STATES::SAILOR_RESPONSE:
      Sailor_Response_SentCallback(macAddr, status);
      break;
    default:
      State_Machine_Error(ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_TimerCallback(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_TimerCallback();
      break;
    case STATES::BURST_QUERY:
      Burst_Query_TimerCallback();
      break;
    case STATES::BURST_RESPONSE:
      Burst_Response_TimerCallback();
      break;
    case STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET: 
      Post_Burst_Check_If_All_LGHS_Set_TimerCallback();
      break;
    case STATES::RELAY_BURST_QUERING:
      Relay_Burst_Quering_TimerCallback();
      break;
    case STATES::INFORM_END_CONFIG:
      Inform_End_Config_TimerCallback();
      break;
    case STATES::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_TimerCallback();
      break;
    case STATES::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_TimerCallback();
      break;
    case STATES::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_TimerCallback();
      break;
    case STATES::SAILOR_RESPONSE:
      Sailor_Response_TimerCallback();
      break;
    default:
      State_Machine_Error(ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_Exit(){
  switch (current_state) {
    case STATES::INITIAL:
      Initial_Exit();
      break;
    case STATES::BURST_QUERY:
      Burst_Query_Exit();
      break;
    case STATES::BURST_RESPONSE:
      Burst_Response_Exit();
      break;
    case STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET: 
      Post_Burst_Check_If_All_LGHS_Set_Exit();
      break;
    case STATES::RELAY_BURST_QUERING:
      Relay_Burst_Quering_Exit();
      break;
    case STATES::INFORM_END_CONFIG:
      Inform_End_Config_Exit();
      break;
    case STATES::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_Exit();
      break;
    case STATES::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_Exit();
      break;
    case STATES::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_Exit();
      break;
    case STATES::SAILOR_RESPONSE:
      Sailor_Response_Exit();
      break;
    default:
      State_Machine_Error(ERRORS::INEXISTING_STATE);
      break;
  }
};

void State_Machine_Error(ERRORS error){
  // TODO
};
