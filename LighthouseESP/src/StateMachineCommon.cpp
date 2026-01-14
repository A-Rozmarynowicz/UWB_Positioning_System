#include "StateMachine.h"

States current_state = States::INITIAL;
StateData current_state_data = {0};
uint8_t completed_distance_measurements[NUMBER_OF_LIGHTHOUSES] = {0};

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
    case States::UWB_QUERY:
      UWB_Query_Enter();
      break;
    case States::UWB_RESPONSE:
      UWB_Response_Enter();
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_Enter();
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_Enter();
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_Enter();
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_Enter();
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_Enter();
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_Enter();
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_Enter();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  switch (current_state) {
    case States::INITIAL:
      Initial_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::UWB_QUERY:
      UWB_Query_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::UWB_RESPONSE:
      UWB_Response_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_ReceiveCallback(data, dataLen, receive_time);
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_ReceiveCallback(data, dataLen, receive_time);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_SentCallback(uint32_t send_time){
  switch (current_state) {
    case States::INITIAL:
      Initial_SentCallback(send_time);
      break;
    case States::UWB_QUERY:
      UWB_Query_SentCallback(send_time);
      break;
    case States::UWB_RESPONSE:
      UWB_Response_SentCallback(send_time);
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_SentCallback(send_time);
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_SentCallback(send_time);
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_SentCallback(send_time);
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_SentCallback(send_time);
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_SentCallback(send_time);
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_SentCallback(send_time);
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_SentCallback(send_time);
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
    case States::UWB_QUERY:
      UWB_Query_TimerCallback(timer_callback);
      break;
    case States::UWB_RESPONSE:
      UWB_Response_TimerCallback(timer_callback);
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_TimerCallback(timer_callback);
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_TimerCallback(timer_callback);
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_TimerCallback(timer_callback);
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_TimerCallback(timer_callback);
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_TimerCallback(timer_callback);
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_TimerCallback(timer_callback);
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_TimerCallback(timer_callback);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_Button_Callback(uint8_t button){
  switch (current_state) {
    case States::INITIAL:
      Initial_ButtonCallback(button);
      break;
    case States::UWB_QUERY:
      UWB_Query_ButtonCallback(button);
      break;
    case States::UWB_RESPONSE:
      UWB_Response_ButtonCallback(button);
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_ButtonCallback(button);
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_ButtonCallback(button);
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_ButtonCallback(button);
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_ButtonCallback(button);
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_ButtonCallback(button);
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_ButtonCallback(button);
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_ButtonCallback(button);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_UWB_New_Range(uint16_t device, float range, float rx_power){
  switch (current_state) {
    case States::INITIAL:
      Initial_UWB_New_Range(device, range, rx_power);
      break;
    case States::UWB_QUERY:
      UWB_Query_UWB_New_Range(device, range, rx_power);
      break;
    case States::UWB_RESPONSE:
      UWB_Response_UWB_New_Range(device, range, rx_power);
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_UWB_New_Range(device, range, rx_power);
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_UWB_New_Range(device, range, rx_power);
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_UWB_New_Range(device, range, rx_power);
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_UWB_New_Range(device, range, rx_power);
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_UWB_New_Range(device, range, rx_power);
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_UWB_New_Range(device, range, rx_power);
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_UWB_New_Range(device, range, rx_power);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
}

void State_Exit(){
  switch (current_state) {
    case States::INITIAL:
      Initial_Exit();
      break;
    case States::UWB_QUERY:
      UWB_Query_Exit();
      break;
    case States::UWB_RESPONSE:
      UWB_Response_Exit();
      break;
    case States::POST_UWB_CHECK_IF_ALL_LGHS_SET:
      Post_UWB_Check_If_All_LGHS_Set_Exit();
      break;
    case States::RELAY_UWB_QUERING:
      Relay_UWB_Quering_Exit();
      break;
    case States::INFORM_END_CONFIG:
      Inform_End_Config_Exit();
      break;
    case States::DISTANCE_MEASURE_RESPONSE:
      Distance_Measure_Response_Exit();
      break;
    case States::DISTANCE_MEASURE_QUERY:
      Distance_Measure_Query_Exit();
      break;
    case States::SEND_CALCULATED_POSITION:
      Send_Calculated_Position_Exit();
      break;
    case States::OBSERVER_RESPONSE:
      Observer_Response_Exit();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

void State_Machine_Error(State_Machine_Errors error){
  // TODO
  Serial.printf("State Machine Error: %d \n", error);
};
