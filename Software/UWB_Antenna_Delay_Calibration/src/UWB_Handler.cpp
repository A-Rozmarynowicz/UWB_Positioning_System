#include "UWB_Handler.h"

void Init_UWB()
{
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(New_Range);
    DW1000Ranging.attachBlinkDevice(New_Blink);
    DW1000Ranging.attachInactiveDevice(Inactive_Device);
    DW1000.setAntennaDelay(16384);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);

    //we start the module as an anchor
    DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
    DW1000.setChannel(DW1000.CHANNEL_2);

        // 3. Add your manual power overrides here
    uint32_t maxPower = 0x1F1F1F1F;
    DW1000.writeBytes(0x1E, 0x00, (byte*)&maxPower, 4);
    DW1000.useSmartPower(false);

    uint16_t ldeCfg2 = 0x1607;
    DW1000.writeBytes(0x2E, 0x1806, (byte*)&ldeCfg2, 2);

    DW1000.commitConfiguration(); // Commit changes to the register
}

void New_Range() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
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
