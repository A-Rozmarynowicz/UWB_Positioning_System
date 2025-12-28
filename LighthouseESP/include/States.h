#ifndef STATES_H
#define STATES_H
#include "LighthouseConfig.h"

void Handle_Sending_Burst_Query_Message();
uint8_t Get_New_State_From_Post_Burst(uint8_t current_target_lighthouse);
void Increment_Target_Lighthouse_Index(uint8_t* target_lighthouse_index);
double Calculate_Avg_Response_Time(double time_responses_sum, uint16_t completed_measurements);

#endif