#ifndef STATES_H
#define STATES_H
#include "LighthouseConfig.h"

void Handle_Sending_Burst_Query_Message();
uint8_t Get_New_State_From_Post_Burst(uint8_t current_target_lighthouse);

void Reset_Target_Lighthouse_Index(uint8_t* target_lighthouse_index);
bool Increment_Target_Lighthouse_Index(uint8_t* target_lighthouse_index);

void Reset_Distance_Query_Target_Index(uint8_t* distance_query_target_index);
bool Increment_Distance_Query_Target_Index(uint8_t* distance_query_target_index);

void Reset_Ack_Target_Index(uint8_t* ack_target_lighthouse, uint8_t* ack_message_index);
bool Increment_Ack_Target_Index(uint8_t* ack_target_lighthouse, uint8_t* ack_message_index);

bool Validate_Ack_Index_Increase(uint8_t* ack_index);

double Calculate_Avg_Response_Time(double time_responses_sum, uint16_t completed_measurements);

bool Handle_Post_Burst_State_Change(uint8_t* current_target_lighthouse);

bool Check_If_All_Distances_Are_Measured(uint8_t* received_distances);

#endif