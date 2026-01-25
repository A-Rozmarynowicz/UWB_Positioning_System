#include "string.h"
#include "communication.h"

uint8_t transmit_buffer[DATA_SIZE] = {0};

#pragma region Message Functions

/**
 * @brief Sends a position query request to a specific lighthouse.
 *
 * @param lgh_index Index of the lighthouse to query.
 */
void MESSAGES::Send_Query_Position(uint8_t lgh_index){
    transmit_buffer[Data_Setup::RECEIVER_ID] = lgh_index;
    transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_QUERY_POSITION;
    _send_esp();
}

/**
 * @brief Sends a broadcast wakeup message to all lighthouses.
 */
void MESSAGES::Send_Wakeup_Reckon() {
  transmit_buffer[Data_Setup::RECEIVER_ID] = BROADCAST_RECEIVER_ID;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_WAKEUP_RECKON;
  _send_esp();
}
#pragma endregion

#pragma region Other Functions

/**
 * @brief Initializes ESP-NOW communication and sets up callbacks.
 *
 * @details
 * - Sets WiFi mode to station and disconnects
 * - Initializes ESP-NOW protocol
 * - Registers receive and send callbacks
 * - Sets transmitter ID in transmit buffer
 */
void Initialize_Communication(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Init Success");
    esp_now_register_recv_cb(_receive_callback);
    esp_now_register_send_cb(_sent_callback);
  }
  else {
    _communication_error(Communication_Errors::PROTOCOL_INIT_FAIL);
  }
  transmit_buffer[Data_Setup::TRANSMITTER_ID] = SAILOR_ID;
};

/**
 * @brief Sends the current transmit buffer via ESP-NOW to all peers.
 *
 * @details
 * - Adds broadcast peer if not already registered
 * - Sends `transmit_buffer` using `esp_now_send`
 * - Handles errors using `_communication_error`
 */
void _send_esp(){
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_err_t result = esp_now_send(broadcastAddress, transmit_buffer, DATA_SIZE);
  if (result == ESP_OK) {}
  else {
    _communication_error(Communication_Errors::MESSAGE_SEND_FAIL);
  }
};

/**
 * @brief ESP-NOW receive callback.
 *
 * @param macAddr MAC address of sender.
 * @param data Pointer to received data buffer.
 * @param dataLen Length of received data.
 *
 * @details
 * Validates receiver ID and forwards valid messages to the state machine.
 */
void _receive_callback(const uint8_t* macAddr, const uint8_t* data, int dataLen){
  uint8_t receiver_id = data[RECEIVER_ID];
  if ((receiver_id != SAILOR_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    return;
  }
  State_ReceiveCallback(data, dataLen);
};

/**
 * @brief ESP-NOW send callback.
 *
 * @param macAddr MAC address of receiver.
 * @param status Send status result.
 *
 * @details
 * Calls `State_SentCallback()` on success or triggers communication error on failure.
 */
void _sent_callback(const uint8_t *macAddr, esp_now_send_status_t status){
  if (status == ESP_NOW_SEND_SUCCESS){
    State_SentCallback();
  }
  else {
    _communication_error(Communication_Errors::DELIVERY_FAIL);
  }
};


/**
 * @brief Handles communication-related errors.
 *
 * @param error Type of communication error.
 *
 * @details
 * - Restarts the device on protocol init failure
 * - Turns on error LED on any error
 * - Prints error type via Serial
 */
void _communication_error(Communication_Errors error){
  if (error == Communication_Errors::PROTOCOL_INIT_FAIL){
    Serial.println("ESP-NOW Init Failed");
    delay(100);
    ESP.restart();
  }
  Error_LED_On();
  Serial.printf("Communication Error: %d \n", error);
};
#pragma endregion