#include "UWB_Handler.h"

uint8_t uwb_enable = 0;

const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH] = {
    {0x82, 0x17, 0x5B, 0xD5, 0xA9, 0x9A, 0xE2, 0x9C},
    {0x7D, 0x00, 0x22, 0xEA, 0x82, 0x60, 0x3B, 0x9C},
    {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18},
    {0x3C, 0x9A, 0x44, 0x10, 0xFE, 0x02, 0x8D, 0x6F}
};

/**
 * @brief Initialize UWB hardware pins and reset line.
 *
 * This function configures the reset pin for the DW1000 module and sets it to HIGH.
 */
void Initialize_UWB(){
    pinMode(PIN_RST, OUTPUT);
    digitalWrite(PIN_RST, HIGH);
}

/**
 * @brief Execute the UWB ranging loop.
 *
 * Should be called periodically to process UWB events and update ranging data.
 */
void Update_UWB(){
    DW1000Ranging.loop();
}

/**
 * @brief Get whether UWB is currently enabled.
 *
 * @return uint8_t 1 if UWB is enabled, 0 otherwise.
 */
uint8_t Is_UWB_Enabled(){return uwb_enable;}

/**
 * @brief Convert a long (8-byte) UWB address to a short (2-byte) address.
 *
 * @param address Pointer to an 8-byte long address.
 * @return uint16_t Short address derived from the first two bytes.
 */
uint16_t Get_Short_Address_From_Long(const uint8_t* address){
    uint16_t short_address = address[1]*256 + address[0];
    return short_address;
}

/**
 * @brief Get lighthouse index from short address.
 *
 * @param short_address Short UWB address to match.
 * @return int8_t Lighthouse index if found, -1 if not found.
 */
int8_t Get_LGH_From_Short_Address(const uint16_t short_address){
    for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        const uint8_t* potential_address = uwb_addresses_from_LGH[i];
        if (Get_Short_Address_From_Long(potential_address) == short_address){
            return i;
        }
    }
    return -1;
}

/**
 * @brief Get lighthouse index from full long address.
 *
 * @param address Pointer to an 8-byte long address.
 * @return int8_t Lighthouse index if found, -1 if not found.
 */
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

/**
 * @brief Restart UWB module in TAG mode.
 *
 * Performs hardware reset, reinitializes SPI and DW1000, attaches callbacks and starts
 * DW1000 ranging as a TAG.
 */
void Restart_UWB_As_Tag(){
    _reset_DW1000();

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    SPI.setFrequency(4000000);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);

    DW1000Ranging.attachNewRange(_new_range);
    DW1000Ranging.attachNewDevice(_new_device);
    DW1000Ranging.attachInactiveDevice(_inactive_device);

    char address_str[24] = {0};
    _format_address_to_string(LIGHTHOUSE_ID, address_str);
    DW1000Ranging.startAsTag(
        address_str,
        DW1000.MODE_LONGDATA_RANGE_ACCURACY,
        false
    );
}

/**
 * @brief Restart UWB module in ANCHOR mode.
 *
 * Performs hardware reset, reinitializes SPI and DW1000, attaches callbacks and starts
 * DW1000 ranging as an ANCHOR.
 */
void Restart_UWB_As_Anchor(){
    _reset_DW1000();

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    SPI.setFrequency(4000000);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);

    DW1000Ranging.setReplyTime(900);
    DW1000Ranging.attachNewRange(_new_range);
    DW1000Ranging.attachBlinkDevice(_new_blink);
    DW1000Ranging.attachNewDevice(_new_device);
    DW1000Ranging.attachInactiveDevice(_inactive_device);

    char address_str[24] = {0};
    _format_address_to_string(LIGHTHOUSE_ID, address_str);
    DW1000Ranging.startAsAnchor(
        address_str,
        DW1000.MODE_LONGDATA_RANGE_ACCURACY,
        false
    );
}

/**
 * @brief Disable UWB processing.
 */
void Disable_UWB(){
    uwb_enable = 0;
}

/**
 * @brief Enable UWB processing.
 */
void Enable_UWB(){
    uwb_enable = 1;
}

/**
 * @brief Compare two UWB addresses for equality.
 *
 * @param first Pointer to the first address array.
 * @param second Pointer to the second address array.
 * @return true if both addresses match, false otherwise.
 */
bool Are_Addresses_Equal(uint8_t* first, uint8_t* second){
    for (uint8_t i =0; i<UWB_ADDRESS_LENGTH; i++){
        if (first[i] != second[i]){
            return false;
        }
    }
    return true;
}

/**
 * @brief Reset DW1000 hardware using the reset pin.
 */
void _reset_DW1000(){
    digitalWrite(PIN_RST, LOW);
    delay(50); // Konieczne
    digitalWrite(PIN_RST, HIGH);
    delay(50); // Konieczne
}


/**
 * @brief Callback invoked when a new blink device is detected.
 *
 * @param device Pointer to the detected DW1000 device.
 */
void _new_blink(DW1000Device* device) {}

/**
 * @brief Callback invoked when a new ranging device is detected.
 *
 * @details Triggers a state machine update with new range data.
 */
void _new_range() {
    uint16_t device = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rx_power = DW1000Ranging.getDistantDevice()->getRXPower();
    State_UWB_New_Range(device, range, rx_power);
}

/**
 * @brief Callback invoked when a device becomes inactive.
 *
 * @param device Pointer to the inactive DW1000 device.
 */
void _new_device(DW1000Device* device) {}

/**
 * @brief Callback invoked when a device is removed due to inactivity.
 *
 * @param device Pointer to the inactive DW1000 device.
 */
void _inactive_device(DW1000Device* device) {}

/**
 * @brief Format a lighthouse long address into a readable string.
 *
 * @param lgh_index Index of lighthouse to format address from.
 * @param address_str Output buffer to store formatted string (at least 24 bytes).
 */
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