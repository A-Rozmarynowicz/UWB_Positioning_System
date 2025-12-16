#include "LighthouseConfig.h"

#define DATA_SIZE (uint8_t) 20
#define STATUS_BUTTON (uint8_t) 4
char receiver = 1;

const uint8_t BROADCAST_RECEIVER_ID = 255;
const uint32_t CYCLE_COUNT_MAX = 4294967295;
const uint32_t RESPONSE_TIMING_BIAS = 0;

enum DATA_SETUP {
  DS_RECEIVER_ID = 0,
  DS_TRANSMITTER_ID = 1,
  DS_MODE = 2,
  DS_MESSAGE = 3,
  DS_EXECUTION_TIME = 4,
  DS_X_POS = 8,
  DS_Y_POS = 12,
  DS_Z_POS = 16,
};

enum DATA_MODES {
  DM_DISTANCE_MEASURE_QUERY,
  DM_DISTANCE_MEASURE_ANSWER,
};

uint32_t message_received_time = 0;
uint32_t message_sent_time = 0;
uint64_t last_message_sending_duration = 0;

uint8_t buffer_transmit[DATA_SIZE] = {0};

volatile uint8_t button_press_counter = 0;

void ICACHE_RAM_ATTR buttonISR() {
  button_press_counter++;
}
 
void receiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen)
{
 
  uint32_t local_receive_time = ESP.getCycleCount();
  uint8_t receiver_id = data[DS_RECEIVER_ID];
  if ((receiver_id != LIGHTHOUSE_ID) & (receiver_id != BROADCAST_RECEIVER_ID)){
    Serial.println("This is NOT Me...");
    return;
  }
  Serial.printf("DATA LEN: %d \n", dataLen);
  message_received_time = local_receive_time;
  uint8_t sender_ID = data[DS_TRANSMITTER_ID];
  buffer_transmit[DS_RECEIVER_ID] = sender_ID;
  memcpy(&(buffer_transmit[DS_EXECUTION_TIME]), &last_message_sending_duration, sizeof(last_message_sending_duration));
  if (data[DS_MODE] == DM_DISTANCE_MEASURE_QUERY){
    buffer_transmit[DS_MODE] = DM_DISTANCE_MEASURE_ANSWER;
    broadcast(buffer_transmit);
  }
  else if (data[DS_MODE] == DM_DISTANCE_MEASURE_ANSWER){
    uint32_t exe = 0;
    uint64_t total = 0;
    memcpy(&exe, &(data[DS_EXECUTION_TIME]), sizeof(last_message_sending_duration));
    memcpy(&(buffer_transmit[DS_EXECUTION_TIME]), &last_message_sending_duration, sizeof(last_message_sending_duration));
    if (message_received_time < message_sent_time){
       total = (CYCLE_COUNT_MAX + message_received_time - message_sent_time - exe); 
    }
    else {
       total = (message_received_time - message_sent_time - exe); 
    }
    if (message_received_time - message_sent_time < exe){
      Serial.println("TIME ERROR");
    }
    Serial.printf("%u  :Send time: \n", message_sent_time);
    Serial.printf("%u  :Receive time: \n", message_received_time);
    Serial.printf("%u  :Exe time: \n", exe);
   
    Serial.printf("Measured time: %u \n", total);
  }
}
 
void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status){
  message_sent_time = ESP.getCycleCount();
  if (message_sent_time < message_received_time){
    last_message_sending_duration = (CYCLE_COUNT_MAX + message_sent_time - message_received_time - RESPONSE_TIMING_BIAS);
  }
  else {
    last_message_sending_duration = (message_sent_time - message_received_time - RESPONSE_TIMING_BIAS);
  }
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void broadcast(const uint8_t* buffer)
// Emulates a broadcast
{
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }
  // Send message
  esp_err_t result = esp_now_send(broadcastAddress, buffer, DATA_SIZE);
  if (result == ESP_OK) {
    Serial.println("Broadcast message success");
    }
  else {
    Serial.println("Broadcast message fail");
  }
}
 
void setup()
{
  buffer_transmit[DS_TRANSMITTER_ID] = LIGHTHOUSE_ID;

  Serial.begin(115200);
  delay(1000);
 
  // Set ESP32 in STA mode
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Broadcast Demo");
 
  // Serial.println(WiFi.macAddress());
  WiFi.disconnect();
 
  // Initialize ESP-NOW
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Init Success");
    esp_now_register_recv_cb(receiveCallback);
    esp_now_register_send_cb(sentCallback);
  }
  else {
    Serial.println("ESP-NOW Init Failed");
    delay(300);
    ESP.restart();
  }
 
  pinMode(STATUS_BUTTON, INPUT_PULLUP);
  attachInterrupt(STATUS_BUTTON, buttonISR, RISING);

}
 
void loop(){
  if (button_press_counter>4){
      buffer_transmit[DS_RECEIVER_ID] = receiver;
      buffer_transmit[DS_MODE] = DM_DISTANCE_MEASURE_QUERY;
      button_press_counter = 0;
      broadcast(buffer_transmit);
  }
}