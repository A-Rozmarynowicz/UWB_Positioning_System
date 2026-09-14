#include "UWB_Handler.h"

uint8_t UWB_mode = ANCHOR;
uint16_t antenna_value = 0;
const byte* UWB_TRANSMIT_MODE = DW1000Class::MODE_SHORTDATA_FAST_ACCURACY;

void Set_Antenna_Value(uint16_t new_val)
{
    antenna_value = new_val;
}


void Init_UWB()
{
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin

    DW1000Ranging.attachNewRange(New_Range);
    DW1000Ranging.attachBlinkDevice(New_Blink);
    DW1000Ranging.attachInactiveDevice(Inactive_Device);
    DW1000.setAntennaDelay(antenna_value);

    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);

    if (UWB_mode == ANCHOR)
    {
        DW1000Ranging.startAsAnchor((char*)"82:17:5B:D5:A9:9A:E2:9C", UWB_TRANSMIT_MODE);
    }
    else
    {
        DW1000Ranging.startAsTag((char*)"7D:00:22:EA:82:60:3B:9C", UWB_TRANSMIT_MODE);
    }

    DW1000.setChannel(CHANNEL);

    DW1000.useSmartPower(false);

    // uint32_t maxPower = 0x25466767;
    uint32_t maxPower = 0x26486A6A;
    DW1000.writeBytes(0x1E, 0x00, (byte*)&maxPower, 4);


    // uint16_t ldeCfg2 = 0x1607;
    // DW1000.writeBytes(0x2E, 0x1806, (byte*)&ldeCfg2, 2);

    DW1000.commitConfiguration();
}

void New_Range() {
    float range = DW1000Ranging.getDistantDevice()->getRange();
    Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
    Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
    New_Measurement(range);
}

void New_Blink(DW1000Device* device) {
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void Inactive_Device(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

void Disable_UWB() {
    DW1000.idle();
}