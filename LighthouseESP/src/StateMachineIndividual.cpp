/**
 * @file StateMachineIndividual.cpp
 * */

#include "StateMachine.h"
#include <math.h>

/** @defgroup StateMachine State Machine Functions
 *  @brief Functions implementing the state machine logic. They all follow the same framework as functions in StateMachineCommon.cpp
 *  @{
 */

#pragma region Initial State Functions
/** @defgroup InitialState Initial State
 *  @brief Functions for the INITIAL state.
 *  @{
 */
void Initial_Enter(){
  current_state_data.ignoring_sent_callbacks = true;
  if (LIGHTHOUSE_ID == 0){
    MESSAGES::Send_Master_LHG_Reset();
  }
};

void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
if (data[Data_Setup::COMMAND] == Data_Commands::CHANGE_STATE_COM){
  switch (data[Data_Setup::SINGLE_0]) {
    case States::UWB_RESPONSE:
      Change_State(States::UWB_RESPONSE);
      break;
  }
  };
};

void Initial_SentCallback(uint32_t send_time){
  if (current_state_data.ignoring_sent_callbacks){
    return;
  }
  Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
  Start_UWB_Activation_Timer();
};

void Initial_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::UWB_ACTIVATION){
    Change_State(States::UWB_QUERY);
  }
};

void Initial_ButtonCallback(uint8_t button) {
  current_state_data.ignoring_sent_callbacks = false;
  MESSAGES::Send_Change_To_UWB_Response(BROADCAST_RECEIVER_ID);
};
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Initial_Exit(){};
/** @} */
#pragma endregion

#pragma region UWB Query State Functions
/** @defgroup UWBQueryState UWB Query State
 *  @brief Functions for the UWB_QUERY state.
 *  @{
 */
void UWB_Query_Enter(){
  Restart_UWB_As_Tag();
  Start_UWB_Activation_Timer();
};

void UWB_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};

void UWB_Query_SentCallback(uint32_t send_time){};

void UWB_Query_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::UWB_ACTIVATION){
    Enable_UWB();
  }
};

void UWB_Query_ButtonCallback(uint8_t button){};

void UWB_Query_UWB_New_Range(uint16_t device, float range, float rx_power){
  int8_t lgh_index = Get_LGH_From_Short_Address(device);
  if (completed_distance_measurements[lgh_index] > MAX_DISTANCE_MEASUREMENTS){
    return;
  }
  if (lgh_index == -1){
    return;
  }
  Blink_LED();
  New_Measurement(lgh_index, range);
  if (Check_If_All_Distances_Are_Measured(completed_distance_measurements)){
    Change_State(States::POST_UWB_CHECK_IF_ALL_LGHS_SET);
  }
}

void UWB_Query_Exit(){
  Calculate_Distance_To_Targets(completed_distance_measurements);
};
/** @} */
#pragma endregion

#pragma region UWB Response State Functions
/** @defgroup UWBResponseState UWB Response State
 *  @brief Functions for the UWB_RESPONSE state.
 *  @{
 */
void UWB_Response_Enter(){
  Restart_UWB_As_Anchor();
  Enable_UWB();
};

void UWB_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::COMMAND] == Data_Commands::CHANGE_STATE_COM){
    switch (data[Data_Setup::SINGLE_0]) {
      case States::UWB_QUERY:
        current_state_data.ignoring_sent_callbacks = true;
        current_state_data.stored_next_state = States::UWB_QUERY;
        MESSAGES::Send_Ack(data[Data_Setup::TRANSMITTER_ID]);
        Change_State(States::UWB_QUERY);
        break;
      case States::DISTANCE_MEASURE_RESPONSE:
        current_state_data.ignoring_sent_callbacks = true;
        MESSAGES::Send_Ack(data[Data_Setup::TRANSMITTER_ID]);
        Change_State(States::DISTANCE_MEASURE_RESPONSE);
        break;
      default:
        State_Machine_Error(State_Machine_Errors::WRONG_TRANSITION);
    }
  }
};

void UWB_Response_SentCallback(uint32_t send_time){};
void UWB_Response_TimerCallback(Timer_Callbacks timer_callback){};
void UWB_Response_ButtonCallback(uint8_t button){};
void UWB_Response_UWB_New_Range(uint16_t device, float range, float rx_power){
  Blink_LED();
}
void UWB_Response_Exit(){};
/** @} */
#pragma endregion

#pragma region Post UWB Check If All LGHS Set State Functions
/** @defgroup PostUWBCheckState Post UWB Check If All LGHS Set State
 *  @brief Functions for the POST_UWB_CHECK_IF_ALL_LGHS_SET state.
 *  @{
 */
void Post_UWB_Check_If_All_LGHS_Set_Enter(){
  Disable_UWB();
  if (LIGHTHOUSE_ID == NUMBER_OF_LIGHTHOUSES - 1){
    Change_State(States::INFORM_END_CONFIG);
  }
  else {
    Change_State(States::RELAY_UWB_QUERING);
  }
};
void Post_UWB_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Post_UWB_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time){};
void Post_UWB_Check_If_All_LGHS_Set_TimerCallback(Timer_Callbacks timer_callback){};
void Post_UWB_Check_If_All_LGHS_Set_ButtonCallback(uint8_t button){};
void Post_UWB_Check_If_All_LGHS_Set_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Post_UWB_Check_If_All_LGHS_Set_Exit(){};
/** @} */
#pragma endregion

#pragma region Relay UWB Quering State Functions
/** @defgroup RelayUWBQueryState Relay UWB Quering State
 *  @brief Functions for the RELAY_UWB_QUERING state.
 *  @{
 */
void Relay_UWB_Quering_Enter(){
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  MESSAGES::Send_Relay_UWB_Response(current_ack_status.target_ack_lighthouse);
  Start_Ack_Timer();
};

void Relay_UWB_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::TRANSMITTER_ID] == current_ack_status.target_ack_lighthouse){
    if (data[Data_Setup::COMMAND] == Data_Commands::ACK_COM){
      Stop_Ack_Timer();
      Change_State(States::UWB_RESPONSE);
    }
  }
};

void Relay_UWB_Quering_SentCallback(uint32_t send_time){};

void Relay_UWB_Quering_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Start_Ack_Timer();
      MESSAGES::Send_Relay_UWB_Response(current_ack_status.target_ack_lighthouse);
    }
    else {
      Data_Transfer_LED_ON();
      _communication_error(Communication_Errors::ACK_FAIL);
      Change_State(States::UWB_RESPONSE);
    }
  }
};

void Relay_UWB_Quering_ButtonCallback(uint8_t button){};

void Relay_UWB_Quering_UWB_New_Range(uint16_t device, float range, float rx_power){}

void Relay_UWB_Quering_Exit(){};
/** @} */
#pragma endregion

#pragma region Inform End Config State Functions
/** @defgroup InformEndConfigState Inform End Config State
 *  @brief Functions for the INFORM_END_CONFIG state.
 *  @{
 */
void Inform_End_Config_Enter(){
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  Start_Ack_Timer();
  MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
};

void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::TRANSMITTER_ID] == current_ack_status.target_ack_lighthouse){
    if (data[Data_Setup::COMMAND] != Data_Commands::ACK_COM){
      return;
    }
    Stop_Ack_Timer();
    if (Increment_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index)){
      Change_State(States::DISTANCE_MEASURE_RESPONSE);
    }
    else {
      Start_Ack_Timer();
      MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
    }
  }
};
void Inform_End_Config_SentCallback(uint32_t send_time){};
void Inform_End_Config_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Start_Ack_Timer();
      MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
      return;
    }
    Data_Transfer_LED_ON();
    _communication_error(Communication_Errors::ACK_FAIL);

    if (Increment_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index)){
      Change_State(States::DISTANCE_MEASURE_RESPONSE);
    }
    else {
      Start_Ack_Timer();
      MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
    }
  }
};
void Inform_End_Config_ButtonCallback(uint8_t button){};
void Inform_End_Config_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Inform_End_Config_Exit(){};
/** @} */
#pragma endregion

#pragma region Distance Measure Response State Functions
/** @defgroup DistanceMeasureResponseState Distance Measure Response State
 *  @brief Functions for the DISTANCE_MEASURE_RESPONSE state.
 *  @{
 */
void Distance_Measure_Response_Enter(){
  if (LIGHTHOUSE_ID == 0){
    Change_State(States::DISTANCE_MEASURE_QUERY);
  }
};
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::COMMAND] == Data_Commands::QUERY_DISTANCE){
    float distance = distances_to_lighthouses[data[Data_Setup::SINGLE_0]];
    MESSAGES::Send_Response_Distance(data[Data_Setup::TRANSMITTER_ID], data[Data_Setup::SINGLE_0], distance);
  }
  else if (data[Data_Setup::COMMAND] == Data_Commands::SET_POSITION){
    memcpy(&position.x, &data[QUAD_0], sizeof(float));
    memcpy(&position.y, &data[QUAD_1], sizeof(float));
    memcpy(&position.z, &data[QUAD_2], sizeof(float));
    MESSAGES::Send_Ack(data[Data_Setup::TRANSMITTER_ID]);
    Change_State(States::OBSERVER_RESPONSE);
  }
};
void Distance_Measure_Response_SentCallback(uint32_t send_time){};
void Distance_Measure_Response_TimerCallback(Timer_Callbacks timer_callback){};
void Distance_Measure_Response_ButtonCallback(uint8_t button){};
void Distance_Measure_Response_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Distance_Measure_Response_Exit(){};
/** @} */
#pragma endregion

#pragma region Distance Measure Query State Functions
/** @defgroup DistanceMeasureQueryState Distance Measure Query State
 *  @brief Functions for the DISTANCE_MEASURE_QUERY state.
 *  @{
 */
void Distance_Measure_Query_Enter(){
  for (uint8_t i=0; i<NUMBER_OF_LIGHTHOUSES; i++){
    master_all_distances_matrix[0][i] = distances_to_lighthouses[i];
  }
  current_ack_status.current_ack_index = 0;
  Reset_Distance_Query_Target_Index(&current_state_data.distance_query_target);
  Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
  MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
};

void Distance_Measure_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::TRANSMITTER_ID] != current_state_data.target_lighthouse){
    return;
  }
  if (data[Data_Setup::COMMAND] == Data_Commands::RESPONSE_DISTANCE){
    Stop_Ack_Timer();
    if (data[Data_Setup::SINGLE_0] != current_state_data.distance_query_target){
      MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
      return;
    }
    float distance = 0.0f;
    memcpy(&distance, &data[Data_Setup::QUAD_0], sizeof(float));
    master_all_distances_matrix[current_state_data.target_lighthouse][current_state_data.distance_query_target] = distance;

    if (Increment_Distance_Query_Target_Index(&current_state_data.distance_query_target)){
      current_ack_status.current_ack_index = 0;
      Reset_Distance_Query_Target_Index(&current_state_data.distance_query_target);
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        Change_State(States::SEND_CALCULATED_POSITION);
        return;
      }
    }
    MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
  }
};
void Distance_Measure_Query_SentCallback(uint32_t send_time){};
void Distance_Measure_Query_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
    }
    else {
      _communication_error(Communication_Errors::ACK_FAIL);
      current_ack_status.current_ack_index = 0;
      Reset_Distance_Query_Target_Index(&current_state_data.distance_query_target);
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        Change_State(States::SEND_CALCULATED_POSITION);
        return;
      }
    }
  }
};
void Distance_Measure_Query_ButtonCallback(uint8_t button){};
void Distance_Measure_Query_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Distance_Measure_Query_Exit(){};
/** @} */
#pragma endregion

#pragma region Send Calculated Position State Functions
/** @defgroup SendCalculatedPositionState Send Calculated Position State
 *  @brief Functions for the SEND_CALCULATED_POSITION state.
 *  @{
 */
void Send_Calculated_Position_Enter(){
  for (uint8_t i = 0; i<NUMBER_OF_LIGHTHOUSES;i++){
    Calculate_Position_Of_Lighthouse(i);
  }
  Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
};

void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::TRANSMITTER_ID] != current_state_data.target_lighthouse){
    Stop_Ack_Timer();
    MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
    return;
  }
  if (data[Data_Setup::COMMAND] == Data_Commands::ACK_COM){
    Stop_Ack_Timer();
    current_ack_status.current_ack_index = 0;
    if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
      Change_State(States::OBSERVER_RESPONSE);
      return;
    }
    MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
  }
};

void Send_Calculated_Position_SentCallback(uint32_t send_time){};
void Send_Calculated_Position_TimerCallback(Timer_Callbacks timer_callback){
  if (timer_callback == Timer_Callbacks::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
    }
    else {
      _communication_error(Communication_Errors::ACK_FAIL);
      Data_Transfer_LED_ON();
      current_ack_status.current_ack_index = 0;
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        Change_State(States::OBSERVER_RESPONSE);
        return;
      }
    }
  }
};
void Send_Calculated_Position_ButtonCallback(uint8_t button){};
void Send_Calculated_Position_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Send_Calculated_Position_Exit(){};
/** @} */
#pragma endregion

#pragma region Observer Response State Functions
/** @defgroup ObserverResponseState Observer Response State
 *  @brief Functions for the OBSERVER_RESPONSE state.
 *  @{
 */
void Observer_Response_Enter(){
  if (LIGHTHOUSE_ID == 0){
    MESSAGES::Send_Observer_Ready();
  }
  Restart_UWB_As_Anchor();
  Enable_UWB();
  Data_Transfer_LED_ON();
};

void Observer_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[Data_Setup::COMMAND] == Data_Commands::OBSERVER_WAKEUP_RECKON){
    MESSAGES::Send_Observer_Ready();
  }
  if (data[Data_Setup::COMMAND] == Data_Commands::OBSERVER_QUERY_POSITION){
    Data_Transfer_LED_OFF();
    MESSAGES::Send_Observer_Position_Response();
  }
  else if (data[Data_Setup::COMMAND] == Data_Commands::OBSERVER_QUERY_UWB_ADDRESS){
    MESSAGES::Send_Observer_UWB_Address_Response();
  }
};
void Observer_Response_SentCallback(uint32_t send_time){};
void Observer_Response_TimerCallback(Timer_Callbacks timer_callback){};
void Observer_Response_ButtonCallback(uint8_t button){};
void Observer_Response_UWB_New_Range(uint16_t device, float range, float rx_power){
  Blink_LED();
}
void Observer_Response_Exit(){};
/** @} */
#pragma endregion

/** @} */