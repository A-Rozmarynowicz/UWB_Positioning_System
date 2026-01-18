#include "UWB_Handler.h"

uint8_t uwb_enable = 0;

const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH] = {
    {0x82, 0x17, 0x5B, 0xD5, 0xA9, 0x9A, 0xE2, 0x9C},
    {0x7D, 0x00, 0x22, 0xEA, 0x82, 0x60, 0x3B, 0x9C},
    // {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18},
    // {0x3C, 0x9A, 0x44, 0x10, 0xFE, 0x02, 0x8D, 0x6F}
};

void Initialize_UWB(){
    pinMode(PIN_RST, OUTPUT);
}

void Update_UWB(){
    DW1000Ranging.loop();
}

uint8_t Is_UWB_Enabled(){return uwb_enable;}

uint16_t Get_Short_Address_From_Long(const uint8_t* address){
    uint16_t short_address = address[1]*256 + address[0];
    return short_address;
}

int8_t Get_LGH_From_Short_Address(const uint16_t short_address){
    for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        const uint8_t* potential_address = uwb_addresses_from_LGH[i];
        Serial.printf("Potentail address: %x\n", Get_Short_Address_From_Long(potential_address));
        if (Get_Short_Address_From_Long(potential_address) == short_address){
            return i;
        }
    }
    return -1;
}

int8_t Get_LGH_From_Address(const uint8_t* address){
    for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        const uint8_t* potential_address = uwb_addresses_from_LGH[i];
        bool same_address = true;
        for (uint8_t j=0;j<UWB_ADDRESS_LENGTH;j++){
            if (potential_address[j] != address[j]){
                same_address = false;
                break;
            }
        }
        if (same_address){
            return i;
        }
    }
    return -1;
}

void Restart_UWB_As_Tag(){
    Serial.println("Switching from ANCHOR to TAG...");

    // 2. Hardware reset of DW1000 (IMPORTANT)
    _reset_DW1000();

    // 3. Re-init SPI & DW1000
    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);

    // 4. Reattach callbacks
    DW1000Ranging.attachNewRange(_new_range);
    DW1000Ranging.attachNewDevice(_new_device);
    DW1000Ranging.attachInactiveDevice(_inactive_device);

    // 5. Start as ANCHOR
    char address_str[24] = {0};
    _format_address_to_string(LIGHTHOUSE_ID, address_str);
    DW1000Ranging.startAsTag(
        address_str,
        DW1000.MODE_LONGDATA_RANGE_ACCURACY,
        false
    );

    Serial.println("Now running as TAg");
}

void Restart_UWB_As_Anchor(){
    Serial.println("Switching from TAG to ANCHOR...");

    // 2. Hardware reset of DW1000 (IMPORTANT)
    _reset_DW1000();

    // 3. Re-init SPI & DW1000
    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);

    // 4. Reattach callbacks
    DW1000Ranging.attachBlinkDevice(_new_blink);
    DW1000Ranging.attachNewDevice(_new_device);
    DW1000Ranging.attachInactiveDevice(_inactive_device);

    // 5. Start as ANCHOR
    char address_str[24] = {0};
    _format_address_to_string(LIGHTHOUSE_ID, address_str);
    DW1000Ranging.startAsAnchor(
        address_str,
        DW1000.MODE_LONGDATA_RANGE_ACCURACY,
        false
    );

    Serial.println("Now running as Ancho");
}


void Disable_UWB(){
    uwb_enable = 0;
}

void Enable_UWB(){
    uwb_enable = 1;
}

bool Are_Addresses_Equal(uint8_t* first, uint8_t* second){
    for (uint8_t i =0; i<UWB_ADDRESS_LENGTH; i++){
        if (first[i] != second[i]){
            return false;
        }
    }
    return true;
}


void _reset_DW1000(){
    digitalWrite(PIN_RST, LOW);
    delay(5);
    digitalWrite(PIN_RST, HIGH);
    delay(5);
}

void _new_blink(DW1000Device* device) {
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void _new_range() {
    uint16_t device = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rx_power = DW1000Ranging.getDistantDevice()->getRXPower();
    State_UWB_New_Range(device, range, rx_power);
    // Serial.print("from: "); Serial.printf("%x\n", device);
    // Serial.print("\t Range: "); Serial.printf("%0.2f", range); Serial.print(" m");
    // Serial.print("\t RX power: "); Serial.printf("%0.2f", rx_power); Serial.println(" dBm");
}

void _new_device(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void _inactive_device(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

void _format_address_to_string(uint8_t lgh_index, char address_str[24]) {
    snprintf(
        address_str,
        24,
        "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
        uwb_addresses_from_LGH[lgh_index][0],
        uwb_addresses_from_LGH[lgh_index][1],
        uwb_addresses_from_LGH[lgh_index][2],
        uwb_addresses_from_LGH[lgh_index][3],
        uwb_addresses_from_LGH[lgh_index][4],
        uwb_addresses_from_LGH[lgh_index][5],
        uwb_addresses_from_LGH[lgh_index][6],
        uwb_addresses_from_LGH[lgh_index][7]
    );
}