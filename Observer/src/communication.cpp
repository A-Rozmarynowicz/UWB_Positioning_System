#include "string.h"
#include "communication.h"

uint8_t transmit_buffer[DATA_SIZE] = {0};

#pragma region Message Functions
void MESSAGES::Send_Query_Position(uint8_t lgh_index){
    transmit_buffer[Data_Setup::RECEIVER_ID] = lgh_index;
    transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_QUERY_POSITION;
    _send_esp();
    Start_Ack_Timer();
}
#pragma endregion

#pragma region Other Functions
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

void _receive_callback(const uint8_t* macAddr, const uint8_t* data, int dataLen){
  uint8_t receiver_id = data[RECEIVER_ID];
  if ((receiver_id != SAILOR_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    Serial.printf("This is NOT Me...: %d\n", receiver_id);
    return;
  }
  State_ReceiveCallback(data, dataLen);
};

void _sent_callback(const uint8_t *macAddr, esp_now_send_status_t status){
  if (status == ESP_NOW_SEND_SUCCESS){
    State_SentCallback();
  }
  else {
    _communication_error(Communication_Errors::DELIVERY_FAIL);
  }
};

void _communication_error(Communication_Errors error){
  if (error == Communication_Errors::PROTOCOL_INIT_FAIL){
    Serial.println("ESP-NOW Init Failed");
    delay(100);
    ESP.restart();
  }
  // TODO
  Serial.printf("Communication Error: %d \n", error);
};
#pragma endregion