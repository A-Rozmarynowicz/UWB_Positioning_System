#include "state_machine.h"

States current_state = States::INITIAL;
State_Data current_state_data = {0};

/**
 * @brief Resets the state machine to the initial state and triggers the enter handler.
 *
 * @details
 * This function sets the current state to `INITIAL`, clears state data and calls
 * `State_Enter()` to run the initial state's enter handler.
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
 * @details
 * This function calls the current state's exit handler, changes the state,
 * and then calls the new state's enter handler.
 */
void Change_State(States new_state){
  Serial.printf("Switching from state %d to state %d  \n ---------------- \n", current_state, new_state);
  State_Exit();
  current_state = new_state;
  State_Enter();
};

/**
 * @brief Calls the enter handler of the current state.
 *
 * @details
 * Based on the current state, this function dispatches the call to the
 * appropriate `*_Enter()` function.
 */
void State_Enter(){
  switch (current_state) {
    case States::INITIAL:
      Initial_Enter();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_Enter();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_Enter();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

/**
 * @brief Dispatches received ESP-NOW messages to the current state's handler.
 *
 * @param data Pointer to received data buffer.
 * @param dataLen Length of received data.
 */
void State_ReceiveCallback(const uint8_t* data, int dataLen){
  switch (current_state) {
    case States::INITIAL:
      Initial_ReceiveCallback(data, dataLen);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_ReceiveCallback(data, dataLen);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_ReceiveCallback(data, dataLen);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

/**
 * @brief Dispatches send completion callbacks to the current state.
 */
void State_SentCallback(){
  switch (current_state) {
    case States::INITIAL:
      Initial_SentCallback();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_SentCallback();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_SentCallback();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};


/**
 * @brief Dispatches timer callbacks to the current state.
 *
 * @param timer_callback The timer callback type.
 */
void State_TimerCallback(Timer_Callbacks timer_callback){
  switch (current_state) {
    case States::INITIAL:
      Initial_TimerCallback(timer_callback);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_TimerCallback(timer_callback);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_TimerCallback(timer_callback);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

/**
 * @brief Dispatches Sailor commands to the current state.
 *
 * @param command The command received from Sailor.
 */
void State_SailorCommand(Sailor_Commands command){
  switch (current_state) {
    case States::INITIAL:
      Initial_SailorCommand(command);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_SailorCommand(command);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_SailorCommand(command);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

/**
 * @brief Calls the exit handler of the current state.
 *
 * @details
 * Based on the current state, this function dispatches the call to the
 * appropriate `*_Exit()` function.
 */
void State_Exit(){
  switch (current_state) {
    case States::INITIAL:
      Initial_Exit();
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_Exit();
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_Exit();
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
};

/**
 * @brief Dispatches UWB ranging updates to the current state.
 *
 * @param device Short address of the device.
 * @param range Measured distance.
 * @param rx_power Received power level.
 */
void State_UWB_New_Range(uint16_t device, float range, float rx_power) {
  switch (current_state) {
    case States::INITIAL:
      Initial_UWB_New_Range(device, range, rx_power);
      break;
    case States::QUERY_POSITIONS:
      Query_Positions_UWB_New_Range(device, range, rx_power);
      break;
    case States::QUERY_DISTANCES:
      Query_Distances_UWB_New_Range(device, range, rx_power);
      break;
    default:
      State_Machine_Error(State_Machine_Errors::INEXISTING_STATE);
      break;
  }
}

/**
 * @brief Handles errors inside the state machine.
 *
 * @param error Error type to report.
 */
void State_Machine_Error(State_Machine_Errors error){
  Error_LED_On();
  Serial.printf("State Machine Error: %d \n", error);
};
