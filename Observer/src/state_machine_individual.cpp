#include "state_machine.h"

#pragma region Initial State Functions
void Initial_Enter(){}
void Initial_ReceiveCallback(const uint8_t* data, int dataLen){}
void Initial_SentCallback(){}
void Initial_TimerCallback(TIMER_CALLBACKS timer_callback){}
void Initial_SailorCommand(SAILOR_COMMANDS command){}
void Initial_Exit(){}
#pragma endregion

#pragma region Query Positions State Functions
void Query_Positions_Enter(){}
void Query_Positions_ReceiveCallback(const uint8_t* data, int dataLen){}
void Query_Positions_SentCallback(){}
void Query_Positions_TimerCallback(TIMER_CALLBACKS timer_callback){}
void Query_Positions_SailorCommand(SAILOR_COMMANDS command){}
void Query_Positions_Exit(){}
#pragma endregion

#pragma region Query Distances State Functions
void Query_Distances_Enter(){}
void Query_Distances_ReceiveCallback(const uint8_t* data, int dataLen){}
void Query_Distances_SentCallback(){}
void Query_Distances_TimerCallback(TIMER_CALLBACKS timer_callback){}
void Query_Distances_SailorCommand(SAILOR_COMMANDS command){}
void Query_Distances_Exit(){}
#pragma endregion
