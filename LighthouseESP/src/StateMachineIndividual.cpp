#include "StateMachine.h"

#pragma region Initial State Functions
void Initial_Enter(){
  if (LIGHTHOUSE_ID == 0){
    current_state_data.target_lighthouse = 1;
    MESSAGES::Send_Machine_Initialization(BROADCAST_RECEIVER_ID);
    Change_State(STATES::BURST_QUERY);
  }
  else {
    Change_State(STATES::BURST_RESPONSE);
  }
};

void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::INITIALIZE_MACHINE_COM){
    Change_State(STATES::BURST_RESPONSE);
  };
};

void Initial_SentCallback(uint32_t send_time){};
void Initial_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Initial_Exit(){};
#pragma endregion

#pragma region Burst Query State Functions
void Burst_Query_Enter(){
  current_state_data.elapsed_times_sum = 0.0;
  current_state_data.time_measurements_completed = 0;
  current_state_data.burst_index = 0;
  MESSAGES::Send_Burst_Query(current_state_data.target_lighthouse, current_state_data.burst_index);
};

void Burst_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::BURST_RESPONSE_COM){
    Stop_ms10_Timer();
    if (data[DATA_SETUP::SINGLE_0] != current_state_data.burst_index){
      //TODO
    }
    double offset = 0.0;
    memcpy(&offset, &data[DATA_SETUP::QUAD_0], sizeof(double));
    double travel_time = Get_Elapsed_Time_From_Measurements(current_state_data.last_registered_time, receive_time, offset);
    current_state_data.elapsed_times_sum += travel_time;
    current_state_data.time_measurements_completed += 1;
    // Serial.printf("Received index: %d. Travel time= %f\n", data[DATA_SETUP::SINGLE_0], travel_time);
    Handle_Sending_Burst_Query_Message();
  }
};

void Burst_Query_SentCallback(uint32_t send_time){
  current_state_data.last_registered_time = ESP.getCycleCount();
  Start_ms10_Timer();
};

void Burst_Query_TimerCallback(TIMER_CALLBACKS timer_callback){
  Handle_Sending_Burst_Query_Message();
};
void Burst_Query_Exit(){};
#pragma endregion

#pragma region Burst Response State Functions
void Burst_Response_Enter(){
  current_state_data.elapsed_times_sum = 0.0;
  current_state_data.time_measurements_completed = 0;
};

void Burst_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){
  if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::BURST_QUERY_COM){
    current_state_data.last_registered_time = receive_time;
    MESSAGES::Send_Burst_Response(data[DATA_SETUP::TRANSMITTER_ID], time_response_offset, data[DATA_SETUP::SINGLE_0]);
  }
};

void Burst_Response_SentCallback(uint32_t send_time){
  double response_time = Get_Elapsed_Time_From_Measurements(current_state_data.last_registered_time, send_time);
  current_state_data.elapsed_times_sum += response_time;
  current_state_data.time_measurements_completed += 1;
  Serial.printf("Response time: %f.    Average Response time: %f. Sum: %f. Number: %d \n", response_time, (current_state_data.elapsed_times_sum)/((double) current_state_data.time_measurements_completed), current_state_data.elapsed_times_sum, current_state_data.time_measurements_completed);
};

void Burst_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Burst_Response_Exit(){};
#pragma endregion

#pragma region Post Burst Check If All LGHS Set State Functions
void Post_Burst_Check_If_All_LGHS_Set_Enter(){
  float distance = C_SPEED * (current_state_data.elapsed_times_sum)/((float) current_state_data.time_measurements_completed * 2.0);
  Serial.printf("Distance: %f", distance);
};
void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Post_Burst_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time){};
void Post_Burst_Check_If_All_LGHS_Set_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Post_Burst_Check_If_All_LGHS_Set_Exit(){};
#pragma endregion

#pragma region Relay Burst Quering State Functions
void Relay_Burst_Quering_Enter(){};
void Relay_Burst_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Relay_Burst_Quering_SentCallback(uint32_t send_time){};
void Relay_Burst_Quering_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Relay_Burst_Quering_Exit(){};
#pragma endregion

#pragma region Inform End Config State Functions
void Inform_End_Config_Enter(){};
void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Inform_End_Config_SentCallback(uint32_t send_time){};
void Inform_End_Config_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Inform_End_Config_Exit(){};
#pragma endregion

#pragma region Distance Measure Response State Functions
void Distance_Measure_Response_Enter(){};
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Distance_Measure_Response_SentCallback(uint32_t send_time){};
void Distance_Measure_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Distance_Measure_Response_Exit(){};
#pragma endregion

#pragma region Distance Measure Query State Functions
void Distance_Measure_Query_Enter(){};
void Distance_Measure_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Distance_Measure_Query_SentCallback(uint32_t send_time){};
void Distance_Measure_Query_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Distance_Measure_Query_Exit(){};
#pragma endregion

#pragma region Send Calculated Position State Functions
void Send_Calculated_Position_Enter(){};
void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Send_Calculated_Position_SentCallback(uint32_t send_time){};
void Send_Calculated_Position_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Send_Calculated_Position_Exit(){};
#pragma endregion

#pragma region Sailor Response State Functions
void Sailor_Response_Enter(){};
void Sailor_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Sailor_Response_SentCallback(uint32_t send_time){};
void Sailor_Response_TimerCallback(TIMER_CALLBACKS timer_callback){};
void Sailor_Response_Exit(){};
#pragma endregion
