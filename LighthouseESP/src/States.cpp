#include "States.h"

void Handle_Sending_Burst_Query_Message(){
    current_state_data.burst_index += 1;
    if (current_state_data.burst_index >= BURST_COUNT){
        Change_State(STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET);
        return;
    }
    MESSAGES::Send_Burst_Query(current_state_data.target_lighthouse, current_state_data.burst_index);
}