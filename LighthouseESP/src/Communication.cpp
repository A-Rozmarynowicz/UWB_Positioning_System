#include "string.h"
#include "Communication.h"

AckStatus current_ack_status = {0};
uint8_t transmit_buffer[DATA_SIZE] = {0};

#pragma region Message Functions
void MESSAGES::Send_Ack(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::ACK_COM;
  _send_esp();
}

void MESSAGES::Send_Change_To_UWB_Response(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::CHANGE_STATE_COM;
  transmit_buffer[Data_Setup::SINGLE_0] = States::UWB_RESPONSE;
  _send_esp();
}

void MESSAGES::Send_UWB_Start_Anchoring(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::UWB_START_ANCHORING;
  _send_esp();
}

void MESSAGES::Send_UWB_Query(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::UWB_QUERY_COM;
  _send_esp();
};

void MESSAGES::Send_UWB_Response(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::UWB_RESPONSE_COM;
  _send_esp();
}

void MESSAGES::Send_Relay_UWB_Response(uint8_t new_uwber_id){
  transmit_buffer[Data_Setup::RECEIVER_ID] = new_uwber_id;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::CHANGE_STATE_COM;
  transmit_buffer[Data_Setup::SINGLE_0] = States::UWB_QUERY;
  _send_esp();
}

void MESSAGES::Send_End_Of_Config_Message(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::CHANGE_STATE_COM;
  transmit_buffer[Data_Setup::SINGLE_0] = States::DISTANCE_MEASURE_RESPONSE;
  _send_esp();
}

void MESSAGES::Send_Query_Avg_Response_Time(uint8_t receiver){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::QUERY_AVG_RESPONSE_TIME;
  _send_esp();
}

void MESSAGES::Send_Response_Avg_Response_Time(uint8_t receiver, double avg){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::RESPOND_AVG_RESPONSE_TIME;
  memcpy(&transmit_buffer[Data_Setup::QUAD_0], &avg, sizeof(double));
  _send_esp();
}

void MESSAGES::Send_Master_LHG_Reset(){
  transmit_buffer[Data_Setup::RECEIVER_ID] = BROADCAST_RECEIVER_ID;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::MASTER_LGH_RESET;
  _send_esp();
}

void MESSAGES::Send_Query_Distance(uint8_t receiver, uint8_t target){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::QUERY_DISTANCE;
  transmit_buffer[Data_Setup::SINGLE_0] = target;
  _send_esp();
  Start_Ack_Timer();
}

void MESSAGES::Send_Response_Distance(uint8_t receiver, uint8_t target, float distance){
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::RESPONSE_DISTANCE;
  transmit_buffer[Data_Setup::SINGLE_0] = target;
  memcpy(&transmit_buffer[QUAD_0], &distance, sizeof(float));
  _send_esp();
}

void MESSAGES::Send_Set_Position(uint8_t receiver){
  Start_Ack_Timer();
  transmit_buffer[Data_Setup::RECEIVER_ID] = receiver;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::SET_POSITION;
  memcpy(&transmit_buffer[QUAD_0], &master_all_positions[receiver].x, sizeof(float));
  memcpy(&transmit_buffer[QUAD_1], &master_all_positions[receiver].y, sizeof(float));
  memcpy(&transmit_buffer[QUAD_2], &master_all_positions[receiver].z, sizeof(float));
  _send_esp();
}

void MESSAGES::Send_Observer_Ready(){
  transmit_buffer[Data_Setup::RECEIVER_ID] = OBSERVER_ID;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::READY_FOR_OBSERVER;
  _send_esp();
}

void MESSAGES::Send_Observer_Position_Response(){
  transmit_buffer[Data_Setup::RECEIVER_ID] = OBSERVER_ID;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_RESPONSE_POSITION;
  memcpy(&(transmit_buffer[Data_Setup::QUAD_0]), &(position.x), sizeof(float));
  memcpy(&(transmit_buffer[Data_Setup::QUAD_1]), &(position.y), sizeof(float));
  memcpy(&(transmit_buffer[Data_Setup::QUAD_2]), &(position.z), sizeof(float));
  _send_esp();
}

void MESSAGES::Send_Observer_UWB_Address_Response(){
  transmit_buffer[Data_Setup::RECEIVER_ID] = OBSERVER_ID;
  transmit_buffer[Data_Setup::COMMAND] = Data_Commands::OBSERVER_RESPONSE_UWB_ADDRESS;
  memcpy(&(transmit_buffer[Data_Setup::QUAD_0]), (&uwb_addresses_from_LGH[LIGHTHOUSE_ID][0]), 4);
  memcpy(&(transmit_buffer[Data_Setup::QUAD_1]), (&uwb_addresses_from_LGH[LIGHTHOUSE_ID][4]), 4);
  _send_esp();
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
  transmit_buffer[Data_Setup::TRANSMITTER_ID] = LIGHTHOUSE_ID;
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
  uint32_t message_receive_time = ESP.getCycleCount();
  uint8_t receiver_id = data[RECEIVER_ID];
  if ((receiver_id != LIGHTHOUSE_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    return;
  }
  State_ReceiveCallback(data, dataLen, message_receive_time);
  if (data[Data_Setup::COMMAND] == Data_Commands::MASTER_LGH_RESET){
    Serial.printf("REMOTE RESTART\n");
    ESP.restart();
  }
};

void _sent_callback(const uint8_t *macAddr, esp_now_send_status_t status){
  uint32_t message_sent_time = ESP.getCycleCount();
  if (status == ESP_NOW_SEND_SUCCESS){
    State_SentCallback(message_sent_time);
  }
  else{
    _communication_error(Communication_Errors::DELIVERY_FAIL);
  }
};

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