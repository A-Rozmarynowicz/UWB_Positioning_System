#include "string.h"
#include "Communication.h"

uint8_t buffer[DATA_SIZE] = {0};

#pragma region Message Functions
void MESSAGES::Send_Machine_Initialization(uint8_t receiver){
  buffer[DATA_SETUP::RECEIVER_ID] = receiver;
  buffer[DATA_SETUP::COMMAND] = DATA_COMMANDS::INITIALIZE_MACHINE_COM;
  Send_ESP();
}

void MESSAGES::Send_Burst_Query(uint8_t receiver, uint8_t burst_index){
  buffer[DATA_SETUP::RECEIVER_ID] = receiver;
  buffer[DATA_SETUP::COMMAND] = DATA_COMMANDS::BURST_QUERY_COM;
  buffer[DATA_SETUP::SINGLE_0] = burst_index;
  Send_ESP();
};

void MESSAGES::Send_Burst_Response(uint8_t receiver, float response_time, uint8_t burst_index){
  buffer[DATA_SETUP::RECEIVER_ID] = receiver;
  buffer[DATA_SETUP::COMMAND] = DATA_COMMANDS::BURST_RESPONSE_COM;
  buffer[DATA_SETUP::SINGLE_0] = burst_index;
  memcpy(&buffer[DATA_SETUP::QUAD_0], &response_time, sizeof(float));
  Send_ESP();
}

void MESSAGES::Send_Relay_Burst_Response(uint8_t new_burster_id){
  buffer[DATA_SETUP::RECEIVER_ID] = new_burster_id;
  buffer[DATA_SETUP::COMMAND] = DATA_COMMANDS::CHANGE_STATE_COM;
  buffer[DATA_SETUP::SINGLE_0] = STATES::BURST_QUERY;
  Send_ESP();
}

void MESSAGES::Send_End_Of_Config_Message(){
  buffer[DATA_SETUP::RECEIVER_ID] = BROADCAST_RECEIVER_ID;
  buffer[DATA_SETUP::COMMAND] = DATA_COMMANDS::CHANGE_STATE_COM;
  buffer[DATA_SETUP::SINGLE_0] = STATES::DISTANCE_MEASURE_RESPONSE;
  Send_ESP();
}
#pragma endregion

#pragma region Other Functions
void Initialize_Communication(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Init Success");
    esp_now_register_recv_cb(Receive_Callback);
    esp_now_register_send_cb(Sent_Callback);
  }
  else {
    Communication_Error(COMMUNICATION_ERRORS::PROTOCOL_INIT_FAIL);
  }
  buffer[DATA_SETUP::TRANSMITTER_ID] = LIGHTHOUSE_ID;
};

void Send_ESP(){
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_err_t result = esp_now_send(broadcastAddress, buffer, DATA_SIZE);
  if (result == ESP_OK) {}
  else {
    Communication_Error(COMMUNICATION_ERRORS::MESSAGE_SEND_FAIL);
  }
};

void Receive_Callback(const uint8_t* macAddr, const uint8_t* data, int dataLen){
  uint32_t message_receive_time = ESP.getCycleCount();
  uint8_t receiver_id = data[RECEIVER_ID];
  if ((receiver_id != LIGHTHOUSE_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    Serial.println("This is NOT Me...");
    return;
  }
  State_ReceiveCallback(data, dataLen, message_receive_time);
};

void Sent_Callback(const uint8_t *macAddr, esp_now_send_status_t status){
  uint32_t message_sent_time = ESP.getCycleCount();
  if (status == ESP_NOW_SEND_SUCCESS){
    State_SentCallback(message_sent_time);
  }
  else{
    Communication_Error(COMMUNICATION_ERRORS::DELIVERY_FAIL);
  }
};

void Communication_Error(COMMUNICATION_ERRORS error){
  if (error == COMMUNICATION_ERRORS::PROTOCOL_INIT_FAIL){
    Serial.println("ESP-NOW Init Failed");
    delay(100);
    ESP.restart();
  }
  // TODO
  Serial.printf("Communication Error: %d \n", error);
};
#pragma endregion