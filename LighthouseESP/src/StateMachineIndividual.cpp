#include "StateMachine.h"

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
  Start_Burst_Timer();
};

void Initial_TimerCallback(TIMER_CALLBACKS timer_callback){
  Change_State(STATES::BURST_QUERY);
};

void Initial_ButtonCallback(uint8_t button) {
  current_state_data.ignoring_sent_callbacks = false;
  MESSAGES::Send_Change_To_Burst_Response(BROADCAST_RECEIVER_ID);
};

void Initial_Exit(){};
#pragma endregion

#pragma region Burst Query State Functions
void Burst_Query_Enter(){
  current_state_data.elapsed_times_sum = 0.0;
  current_state_data.time_measurements_completed = 0;
  current_state_data.message_index = 0;
  Start_Burst_Timer();
};

void Burst_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::BURST_RESPONSE_COM){
    if (current_state_data.message_index < 10){
      return;
    }
    double travel_time = Get_Elapsed_Time_From_Measurements(current_state_data.last_registered_time, receive_time);
    if (travel_time < 0.00009){
      Serial.printf("To short time: %f\n", travel_time);
      return;
    }
    uint32_t first_registered_time = current_state_data.last_registered_time;
    uint32_t second_registered_time = receive_time;
    uint32_t travel_cycle_counts = 0;
    if (first_registered_time > second_registered_time){
      travel_cycle_counts = (CYCLE_COUNT_MAX - first_registered_time) + second_registered_time;
    }
    else {
      travel_cycle_counts = second_registered_time - first_registered_time;
    }
    // Serial.printf("Cycles: %d\n", travel_cycle_counts);
    current_state_data.elapsed_times_sum += travel_time;
    current_state_data.time_measurements_completed += 1;

    // Serial.printf("Received packet: %d. Time: %f \n", current_state_data.message_index, travel_time);
    // if (travel_time < 0.0001) {
    //   Serial.printf("---------------------------\n");
    // }
  }
};

void Burst_Query_SentCallback(uint32_t send_time){
  // Serial.printf("Sent packet: %d\n", current_state_data.message_index);
  current_state_data.last_registered_time = ESP.getCycleCount();
  Start_Burst_Timer();
  // Data_Transfer_LED_ON();
};

void Burst_Query_TimerCallback(TIMER_CALLBACKS timer_callback){
  Handle_Sending_Burst_Query_Message();
  // Serial.printf("Timer packet: %d\n", current_state_data.message_index);
};

void Burst_Query_ButtonCallback(uint8_t button){};
void Burst_Query_Exit(){
  Serial.printf("Desired: %d, complete: %d\n", BURST_COUNT, current_state_data.time_measurements_completed);
};
#pragma endregion

#pragma region Burst Response State Functions
void Burst_Response_Enter(){
  current_state_data.elapsed_times_sum = 0.0;
  current_state_data.time_measurements_completed = 0;
  current_state_data.ignoring_sent_callbacks = false;
};

void Burst_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::BURST_QUERY_COM){
    current_state_data.last_registered_time = receive_time;
    MESSAGES::Send_Burst_Response(data[DATA_SETUP::TRANSMITTER_ID]);
  }
  else if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::QUERY_AVG_RESPONSE_TIME) {
    current_state_data.ignoring_sent_callbacks = true;
    double avg = Calculate_Avg_Response_Time(current_state_data.elapsed_times_sum, current_state_data.time_measurements_completed);
    MESSAGES::Send_Response_Avg_Response_Time(data[DATA_SETUP::TRANSMITTER_ID], avg);
    Serial.printf("Avg response time (self): %f.\n", avg);
  }
  else if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::CHANGE_STATE_COM){
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

void Burst_Response_SentCallback(uint32_t send_time){
  if (current_state_data.ignoring_sent_callbacks){
    return;
  }
  double response_time = Get_Elapsed_Time_From_Measurements(current_state_data.last_registered_time, send_time);
  current_state_data.elapsed_times_sum += response_time;
  current_state_data.time_measurements_completed += 1;
};

void Burst_Response_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    switch (current_state_data.stored_next_state)
    {
    case STATES::BURST_QUERY:
      Reset_Target_Lighthouse_Index(&current_state_data.target_lighthouse);
      Change_State(STATES::BURST_QUERY);
      break;
    default:
      break; // TODO
    }
  }
};
void Burst_Response_ButtonCallback(uint8_t button){};
void Burst_Response_Exit(){};
#pragma endregion

#pragma region Post Burst Check If All LGHS Set State Functions
void Post_Burst_Check_If_All_LGHS_Set_Enter(){
  current_state_data.message_index = 0;
  current_ack_status.target_ack_lighthouse = current_state_data.target_lighthouse;
  current_ack_status.current_ack_index = 0;
  Start_Ack_Timer();
  MESSAGES::Send_Query_Avg_Response_Time(current_state_data.target_lighthouse);
};

void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] != DATA_COMMANDS::RESPOND_AVG_RESPONSE_TIME){
    return;
  }

  double avg_response_time = 0.0;
  memcpy(&avg_response_time, &data[DATA_SETUP::QUAD_0], sizeof(double));
  avg_response_time = max(avg_response_time, current_state_data.stored_targets_avg_response_time);
  current_state_data.stored_targets_avg_response_time = avg_response_time;

  Calculate_Distance_To_Target(current_state_data.elapsed_times_sum, current_state_data.time_measurements_completed,
                              avg_response_time, current_state_data.target_lighthouse);
  Serial.printf("Distance: %f. AVG Response (target): %f\n", distances_to_lighthouses[current_state_data.target_lighthouse], avg_response_time);

  if (!Handle_Post_Burst_State_Change(&current_state_data.target_lighthouse)){
    State_Machine_Error(STATE_MACHINE_ERRORS::WRONG_TRANSITION);
  }
};

void Post_Burst_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time){};

void Post_Burst_Check_If_All_LGHS_Set_TimerCallback(TIMER_CALLBACKS timer_callback){
  if (timer_callback == TIMER_CALLBACKS::ACK){
    if (Validate_Ack_Index_Increase(&current_ack_status.current_ack_index)){
      Serial.printf("Missed a single Avg response\n");
      Start_Ack_Timer();
      MESSAGES::Send_Query_Avg_Response_Time(current_state_data.target_lighthouse);
    }
    else {
      Serial.printf("Missed all Avg responses\n");
      Communication_Error(COMMUNICATION_ERRORS::ACK_FAIL);
      Data_Transfer_LED_ON();

      if (!Handle_Post_Burst_State_Change(&current_state_data.target_lighthouse)){
        State_Machine_Error(STATE_MACHINE_ERRORS::WRONG_TRANSITION);
      }
    }
  }
};
void Post_Burst_Check_If_All_LGHS_Set_ButtonCallback(uint8_t button){};
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
    Serial.printf("Set position: %0.2f | %0.2f | %0.2f \n");
    MESSAGES::Send_Ack(data[DATA_SETUP::TRANSMITTER_ID]);
    Change_State(STATES::SAILOR_RESPONSE);
  }
};
void Distance_Measure_Response_SentCallback(uint32_t send_time){};
void Distance_Measure_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Distance_Measure_Response_ButtonCallback(uint8_t button){};
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
    Serial.printf("Received distance\n");

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
void Distance_Measure_Query_Exit(){};
#pragma endregion

#pragma region Send Calculated Position State Functions
void Send_Calculated_Position_Enter(){};
void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Send_Calculated_Position_SentCallback(uint32_t send_time){};
void Send_Calculated_Position_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Send_Calculated_Position_ButtonCallback(uint8_t button){};
void Send_Calculated_Position_Exit(){};
#pragma endregion

#pragma region Sailor Response State Functions
void Sailor_Response_Enter(){};
void Sailor_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Sailor_Response_SentCallback(uint32_t send_time){};
void Sailor_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Sailor_Response_ButtonCallback(uint8_t button){};
void Sailor_Response_Exit(){};
#pragma endregion
