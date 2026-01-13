#include "StateMachine.h"
#include <math.h>

#pragma region Initial State Functions
void Initial_Enter(){
  current_state_data.ignoring_sent_callbacks = true;
  if (LIGHTHOUSE_ID == 0){
    MESSAGES::Send_Master_LHG_Reset();
  }
};

void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::CHANGE_STATE_COM){
  switch (data[DATA_SETUP::SINGLE_0]) {
    case STATES::BURST_RESPONSE:
      Change_State(STATES::BURST_RESPONSE);
      break;
  }
  };
};

void Initial_SentCallback(uint32_t send_time){
  if (current_state_data.ignoring_sent_callbacks){
    return;
  }
  Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
  Start_Ack_Timer();
};

void Initial_TimerCallback(TIMER_CALLBACKS timer_callback){
  Change_State(STATES::BURST_QUERY);
};

void Initial_ButtonCallback(uint8_t button) {
  current_state_data.ignoring_sent_callbacks = false;
  MESSAGES::Send_Change_To_Burst_Response(BROADCAST_RECEIVER_ID);
};
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Initial_Exit(){};
#pragma endregion

#pragma region Burst Query State Functions
void Burst_Query_Enter(){
  Restart_UWB_As_Tag();
  Start_UWB_Restart_Ack_Timer();
};
void Burst_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Burst_Query_SentCallback(uint32_t send_time){};
void Burst_Query_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::UWB_RESTART_ACK){
    Enable_UWB();
  }
};
void Burst_Query_ButtonCallback(uint8_t button){};
void Burst_Query_UWB_New_Range(uint16_t device, float range, float rx_power){
  for (uint8_t i=0; i<NUMBER_OF_LIGHTHOUSES;i++){
    // if (uwb_addresses_from_LGH[i] == device){
    //   Calculate_Distance_To_Target(i, range);
    //   completed_distance_measurements[i] += 1;
    //   if (Check_If_All_Distances_Are_Measured(completed_distance_measurements)){
    //     Change_State(STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET);
    //   }
    //   break;
    // }
  }
}
void Burst_Query_Exit(){};
#pragma endregion

#pragma region Burst Response State Functions
void Burst_Response_Enter(){
  Restart_UWB_As_Anchor();
  Enable_UWB();
};

void Burst_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::CHANGE_STATE_COM){
    switch (data[DATA_SETUP::SINGLE_0]) {
      case STATES::BURST_QUERY:
        current_state_data.ignoring_sent_callbacks = true;
        current_state_data.stored_next_state = STATES::BURST_QUERY;
        MESSAGES::Send_Ack(data[DATA_SETUP::TRANSMITTER_ID]);
        Start_Ack_Timer();
        break;
      case STATES::DISTANCE_MEASURE_RESPONSE:
        current_state_data.ignoring_sent_callbacks = true;
        MESSAGES::Send_Ack(data[DATA_SETUP::TRANSMITTER_ID]);
        Change_State(STATES::DISTANCE_MEASURE_RESPONSE);
        break;
      default:
        State_Machine_Error(STATE_MACHINE_ERRORS::WRONG_TRANSITION);
    }
  }
};

void Burst_Response_SentCallback(uint32_t send_time){};
void Burst_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Burst_Response_ButtonCallback(uint8_t button){};
void Burst_Response_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Burst_Response_Exit(){};
#pragma endregion

#pragma region Post Burst Check If All LGHS Set State Functions
void Post_Burst_Check_If_All_LGHS_Set_Enter(){
  if (LIGHTHOUSE_ID == NUMBER_OF_LIGHTHOUSES - 1){
    Change_State(STATES::INFORM_END_CONFIG);
  }
  else {
    Change_State(STATES::RELAY_BURST_QUERING);
  }
};
void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Post_Burst_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time){};
void Post_Burst_Check_If_All_LGHS_Set_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Post_Burst_Check_If_All_LGHS_Set_ButtonCallback(uint8_t button){};
void Post_Burst_Check_If_All_LGHS_Set_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Post_Burst_Check_If_All_LGHS_Set_Exit(){};
#pragma endregion

#pragma region Relay Burst Quering State Functions
void Relay_Burst_Quering_Enter(){
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  Start_Ack_Timer();
  MESSAGES::Send_Relay_Burst_Response(current_ack_status.target_ack_lighthouse);
  MESSAGES::Send_Reset_Burst_Response_Info();
};
void Relay_Burst_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::TRANSMITTER_ID] == current_ack_status.target_ack_lighthouse){
    if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::ACK_COM){
      Serial.printf("Received Ack \n");
      Stop_Ack_Timer();
      Change_State(STATES::BURST_RESPONSE);
    }
  }
};

void Relay_Burst_Quering_SentCallback(uint32_t send_time){};
void Relay_Burst_Quering_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Serial.printf("Missed Single Ack \n");
      Start_Ack_Timer();
      MESSAGES::Send_Relay_Burst_Response(current_ack_status.target_ack_lighthouse);
    }
    else {
      Serial.printf("Missed All Ack\n");
      Data_Transfer_LED_ON();
      Communication_Error(COMMUNICATION_ERRORS::ACK_FAIL);
      Change_State(STATES::BURST_RESPONSE);
    }
  }
};

void Relay_Burst_Quering_ButtonCallback(uint8_t button){};
void Relay_Burst_Quering_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Relay_Burst_Quering_Exit(){};
#pragma endregion

#pragma region Inform End Config State Functions
void Inform_End_Config_Enter(){
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  Start_Ack_Timer();
  MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
};

void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::TRANSMITTER_ID] == current_ack_status.target_ack_lighthouse){
    if (data[DATA_SETUP::COMMAND] != DATA_COMMANDS::ACK_COM){
      return;
    }
    Serial.printf("Received EndConf Ack\n");
    Stop_Ack_Timer();
    if (Increment_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index)){
      Change_State(STATES::DISTANCE_MEASURE_RESPONSE);
    }
    else {
      Start_Ack_Timer();
      MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
    }
  }
};
void Inform_End_Config_SentCallback(uint32_t send_time){};
void Inform_End_Config_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Serial.printf("Missed a single EndConf Ack\n");
      Start_Ack_Timer();
      MESSAGES::Send_End_Of_Config_Message(current_ack_status.target_ack_lighthouse);
      return;
    }
    Serial.printf("Missed all EndConf Acks\n");
    Data_Transfer_LED_ON();
    Communication_Error(COMMUNICATION_ERRORS::ACK_FAIL);

    if (Increment_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index)){
      Change_State(STATES::DISTANCE_MEASURE_RESPONSE);
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
#pragma endregion

#pragma region Distance Measure Response State Functions
void Distance_Measure_Response_Enter(){
  if (LIGHTHOUSE_ID == 0){
    Change_State(STATES::DISTANCE_MEASURE_QUERY);
  }
};
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::QUERY_DISTANCE){
    float distance = distances_to_lighthouses[data[DATA_SETUP::SINGLE_0]];
    Serial.printf("Asked for distance to nr. %d. Distance = %f\n", data[DATA_SETUP::SINGLE_0], distance);
    MESSAGES::Send_Response_Distance(data[DATA_SETUP::TRANSMITTER_ID], data[DATA_SETUP::SINGLE_0], distance);
  }
  else if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::SET_POSITION){
    memcpy(&position.x, &data[QUAD_0], sizeof(float));
    memcpy(&position.y, &data[QUAD_1], sizeof(float));
    memcpy(&position.z, &data[QUAD_2], sizeof(float));
    Serial.printf("Set position: %0.2f | %0.2f | %0.2f \n", position.x, position.y, position.z);
    MESSAGES::Send_Ack(data[DATA_SETUP::TRANSMITTER_ID]);
    Change_State(STATES::SAILOR_RESPONSE);
  }
};
void Distance_Measure_Response_SentCallback(uint32_t send_time){};
void Distance_Measure_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Distance_Measure_Response_ButtonCallback(uint8_t button){};
void Distance_Measure_Response_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Distance_Measure_Response_Exit(){};
#pragma endregion

#pragma region Distance Measure Query State Functions
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
  if (data[DATA_SETUP::TRANSMITTER_ID] != current_state_data.target_lighthouse){
    Serial.printf("Distance Query Wrong target index: %d vs %d\n", data[DATA_SETUP::TRANSMITTER_ID], current_state_data.target_lighthouse);
    return;
  }
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::RESPONSE_DISTANCE){
    Stop_Ack_Timer();
    if (data[DATA_SETUP::SINGLE_0] != current_state_data.distance_query_target){
      Serial.printf("Wrong query distance target target: %d vs %d\n", data[DATA_SETUP::SINGLE_0], current_state_data.distance_query_target);
      MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
      return;
    }
    float distance = 0.0f;
    memcpy(&distance, &data[DATA_SETUP::QUAD_0], sizeof(float));
    master_all_distances_matrix[current_state_data.target_lighthouse][current_state_data.distance_query_target] = distance;
    Serial.printf("Received distance from %d about %d\n", current_state_data.target_lighthouse, current_state_data.distance_query_target);

    if (Increment_Distance_Query_Target_Index(&current_state_data.distance_query_target)){
      current_ack_status.current_ack_index = 0;
      Reset_Distance_Query_Target_Index(&current_state_data.distance_query_target);
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        Print_Master_All_Distances_Matrix();
        Serial.printf("Average distance: %f\n", (master_all_distances_matrix[0][1]+master_all_distances_matrix[1][0])/2.0);
        Change_State(STATES::SEND_CALCULATED_POSITION);
        return;
      }
    }
    MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
  }
};
void Distance_Measure_Query_SentCallback(uint32_t send_time){};
void Distance_Measure_Query_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Serial.printf("Missed a single ACK for Distance Query \n");
      MESSAGES::Send_Query_Distance(current_state_data.target_lighthouse, current_state_data.distance_query_target);
    }
    else {
      Serial.printf("Missed all ACK for Dsitance Query from %d \n", current_state_data.target_lighthouse);
      Communication_Error(COMMUNICATION_ERRORS::ACK_FAIL);

      current_ack_status.current_ack_index = 0;
      Reset_Distance_Query_Target_Index(&current_state_data.distance_query_target);
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        // Print_Master_All_Distances_Matrix();
        Change_State(STATES::SEND_CALCULATED_POSITION);
        return;
      }
    }
  }
};
void Distance_Measure_Query_ButtonCallback(uint8_t button){};
void Distance_Measure_Query_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Distance_Measure_Query_Exit(){};
#pragma endregion

#pragma region Send Calculated Position State Functions
void Send_Calculated_Position_Enter(){
  // float dist0[4] = {0.0, 1.0, 1.0, 1.0};
  // memcpy(&master_all_distances_matrix[0], &dist0, sizeof(float) * 4);

  // float dist1[4] = {1.0, 0.0, 1.0, 1.0};
  // memcpy(&master_all_distances_matrix[1], &dist1, sizeof(float) * 4);

  // float dist2[4] = {1.0, 1.0, 0.0, 1.0};
  // memcpy(&master_all_distances_matrix[2], &dist2, sizeof(float) * 4);

  // float dist3[4] = {1.0, 1.0, 1.0, 0.0};
  // memcpy(&master_all_distances_matrix[3], &dist3, sizeof(float) * 4);

  for (uint8_t i = 0; i<NUMBER_OF_LIGHTHOUSES;i++){
    Calculate_Position_Of_Lighthouse(i);
    Print_Position(i);
  }
  Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
  Reset_Ack_Target_Index(&current_ack_status.target_ack_lighthouse, &current_ack_status.current_ack_index);
  MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
};

void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::TRANSMITTER_ID] != current_state_data.target_lighthouse){
    Stop_Ack_Timer();
    Serial.printf("Set Position Wrong target index: %d vs %d\n", data[DATA_SETUP::TRANSMITTER_ID], current_state_data.target_lighthouse);
    MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
    return;
  }
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::ACK_COM){
    Stop_Ack_Timer();
    current_ack_status.current_ack_index = 0;
    if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
      Change_State(STATES::SAILOR_RESPONSE);
      return;
    }
    MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
  }
};

void Send_Calculated_Position_SentCallback(uint32_t send_time){};
void Send_Calculated_Position_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Serial.printf("Missed a single ACK for Set Position \n");
      MESSAGES::Send_Set_Position(current_state_data.target_lighthouse);
    }
    else {
      Serial.printf("Missed all ACK for Set Position from %d \n", current_state_data.target_lighthouse);
      Communication_Error(COMMUNICATION_ERRORS::ACK_FAIL);
      Data_Transfer_LED_ON();
      current_ack_status.current_ack_index = 0;
      if (Increment_Target_Lighthouse_Index(&current_state_data.target_lighthouse)){
        Change_State(STATES::SAILOR_RESPONSE);
        return;
      }
    }
  }
};
void Send_Calculated_Position_ButtonCallback(uint8_t button){};
void Send_Calculated_Position_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Send_Calculated_Position_Exit(){};
#pragma endregion

#pragma region Sailor Response State Functions
void Sailor_Response_Enter(){
  if (LIGHTHOUSE_ID == 0){
    MESSAGES::Send_Sailor_Ready();
  }
  Restart_UWB_As_Anchor();
  Enable_UWB();
};
void Sailor_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::OBSERVER_QUERY_POSITION){
    MESSAGES::Send_Sailor_Position_Response();
  }
};
void Sailor_Response_SentCallback(uint32_t send_time){};
void Sailor_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Sailor_Response_ButtonCallback(uint8_t button){};
void Sailor_Response_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Sailor_Response_Exit(){};
#pragma endregion









