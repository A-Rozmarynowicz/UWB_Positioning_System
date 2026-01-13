#include "uwb_handler.h"

uint8_t uwb_enable = 0;
char uwb_address[24] = "6F:2D:91:8A:C4:73:5E:B0";

void Initialize_UWB(){
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    DW1000Ranging.startAsTag(uwb_address, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void Update_UWB(){
    DW1000Ranging.loop();
}

uint8_t Is_UWB_Enabled(){return uwb_enable;}

void Disable_UWB(){
    uwb_enable = 0;
}

void Enable_UWB(){
    uwb_enable = 1;
}

void newRange() {
    uint8_t device = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rx_power = DW1000Ranging.getDistantDevice()->getRXPower();
    State_UWB_New_Range(device, range, rx_power);
    Serial.print("from: "); Serial.printf("%x\n", device);
    Serial.print("\t Range: "); Serial.printf("%0.2f", range); Serial.print(" m");
    Serial.print("\t RX power: "); Serial.printf("%0.2f", rx_power); Serial.println(" dBm");
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}