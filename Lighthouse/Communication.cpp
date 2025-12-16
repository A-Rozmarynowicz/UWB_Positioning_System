#include "Communication.h"

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
};

void Send_ESP(const uint8_t* buffer){
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
  uint8_t receiver_id = data[DS_RECEIVER_ID];
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