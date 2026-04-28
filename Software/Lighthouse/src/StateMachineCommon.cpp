#include "StateMachine.h"

States current_state = States::INITIAL;
State_Data current_state_data = {0};
uint8_t completed_distance_measurements[NUMBER_OF_LIGHTHOUSES] = {0};

/**
 * @brief Resets and initializes the state machine to the initial state.
 *
 * @return void
 */
void Reset_And_Initialize_Machine(){
  current_state = States::INITIAL;
  current_state_data = {0};
  State_Enter();
};

/**
 * @brief Changes the current state and calls exit/enter handlers.
 *
 * @param new_state The state to switch to.
 *
 * @return void
 */
void Change_State(States new_state){
  Serial.printf("Switching from state %d to state %d  \n ---------------- \n", current_state, new_state);
  State_Exit();
  current_state = new_state;
  State_Enter();
};

/**
 * @brief Calls the enter handler for the current state.
 *
 * @return void
 */
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

/**
 * @brief Calls the receive callback handler for the current state.
 *
 * @param data Pointer to received data.
 * @param dataLen Length of received data.
 * @param receive_time Timestamp when data was received.
 *
 * @return void
 */
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

/**
 * @brief Calls the sent callback handler for the current state.
 *
 * @param send_time Timestamp when the message was sent.
 *
 * @return void
 */
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


/**
 * @brief Calls the timer callback handler for the current state.
 *
 * @param timer_callback Identifier of the triggered timer.
 *
 * @return void
 */
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

/**
 * @brief Calls the button callback handler for the current state.
 *
 * @param button Button ID that triggered the callback.
 *
 * @return void
 */
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

/**
 * @brief Calls the UWB range callback handler for the current state.
 *
 * @param device UWB device ID.
 * @param range Measured range to device.
 * @param rx_power Received signal power.
 *
 * @return void
 */
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


/**
 * @brief Calls the exit handler for the current state.
 *
 * @return void
 */
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

/**
 * @brief Handles state machine errors.
 *
 * @param error Error code.
 *
 * @return void
 */
void State_Machine_Error(State_Machine_Errors error){
  Error_LED_On();
};
