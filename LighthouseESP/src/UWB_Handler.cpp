#include "UWB_Handler.h"

uint8_t uwb_enable = 0;

const char* uwb_addresses_from_LGH[] = {
    "82:17:5B:D5:A9:9A:E2:9C",
    "7D:00:22:EA:82:60:3B:9C",
    "A1:B2:C3:D4:E5:F6:07:18",
    "3C:9A:44:10:FE:02:8D:6F"
};

void Initialize_UWB(){
    pinMode(PIN_RST, OUTPUT);
}

void Update_UWB(){
    DW1000Ranging.loop();
}

uint8_t Is_UWB_Enabled(){return uwb_enable;}

void resetDW1000(){
    digitalWrite(PIN_RST, LOW);
    delay(5);
    digitalWrite(PIN_RST, HIGH);
    delay(5);
}

void Restart_UWB_As_Tag(){
    resetDW1000();
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);

    char euiBuffer[24];
    strncpy(euiBuffer, uwb_addresses_from_LGH[LIGHTHOUSE_ID], sizeof(euiBuffer));
    euiBuffer[sizeof(euiBuffer) - 1] = '\0';  // safety

    DW1000Ranging.startAsTag(euiBuffer, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void Restart_UWB_As_Anchor(){
    resetDW1000();
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    DW1000Ranging.useRangeFilter(true);

    char euiBuffer[24];
    strncpy(euiBuffer, uwb_addresses_from_LGH[LIGHTHOUSE_ID], sizeof(euiBuffer));
    euiBuffer[sizeof(euiBuffer) - 1] = '\0';  // safety
    DW1000Ranging.startAsAnchor(euiBuffer, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

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