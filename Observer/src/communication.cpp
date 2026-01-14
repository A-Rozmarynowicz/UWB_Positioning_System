#include "string.h"
#include "communication.h"

uint8_t transmit_buffer[DATA_SIZE] = {0};

#pragma region Message Functions
void MESSAGES::Send_Query_Position(uint8_t lgh_index){
    transmit_buffer[Data_Setup::RECEIVER_ID] = lgh_index;
    transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_QUERY_POSITION;
    Send_ESP();
    Start_Ack_Timer();
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
  transmit_buffer[Data_Setup::TRANSMITTER_ID] = SAILOR_ID;
};

void Send_ESP(){
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_err_t result = esp_now_send(broadcastAddress, transmit_buffer, DATA_SIZE);
  if (result == ESP_OK) {}
  else {
    Communication_Error(COMMUNICATION_ERRORS::MESSAGE_SEND_FAIL);
  }
};

void Receive_Callback(const uint8_t* macAddr, const uint8_t* data, int dataLen){
  uint8_t receiver_id = data[RECEIVER_ID];
  if ((receiver_id != SAILOR_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    Serial.printf("This is NOT Me...: %d\n", receiver_id);
    return;
  }
  State_ReceiveCallback(data, dataLen);
};

void Sent_Callback(const uint8_t *macAddr, esp_now_send_status_t status){
  if (status == ESP_NOW_SEND_SUCCESS){
    State_SentCallback();
  }
  else {
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