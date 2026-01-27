#include "uwb_handler.h"


const uint8_t uwb_addresses_from_LGH[NUMBER_OF_LIGHTHOUSES][UWB_ADDRESS_LENGTH] = {
    {0x82, 0x17, 0x5B, 0xD5, 0xA9, 0x9A, 0xE2, 0x9C},
    {0x7D, 0x00, 0x22, 0xEA, 0x82, 0x60, 0x3B, 0x9C},
    {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18},
    {0x3C, 0x9A, 0x44, 0x10, 0xFE, 0x02, 0x8D, 0x6F}
};

uint8_t uwb_enable = 0;
char uwb_address[24] = "6F:2D:91:8A:C4:73:5E:B0";

/**
 * @brief Initializes UWB hardware and starts the device as a tag.
 *
 * This function:
 * - Resets the DW1000 module
 * - Configures SPI interface
 * - Attaches UWB callbacks
 * - Starts the UWB module as a tag
 */
void Initialize_UWB(){
    pinMode(PIN_RST, OUTPUT);
    digitalWrite(PIN_RST, LOW);
    delay(10);
    digitalWrite(PIN_RST, HIGH);
    delay(10);

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_SS);
    SPI.setFrequency(1000000);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(_new_range);
    DW1000Ranging.attachBlinkDevice(_new_device);
    DW1000Ranging.attachInactiveDevice(_inactive_device);

    DW1000Ranging.startAsTag(uwb_address, DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);
}

/**
 * @brief Processes UWB ranging events.
 *
 * Must be called regularly in the main loop to keep the UWB stack running.
 */
void Update_UWB(){
    DW1000Ranging.loop();
}

/**
 * @brief Returns whether UWB is currently enabled.
 *
 * @return 1 if enabled, 0 otherwise.
 */
uint8_t Is_UWB_Enabled(){return uwb_enable;}

/**
 * @brief Disables UWB ranging.
 */
void Disable_UWB(){
    uwb_enable = 0;
}

/**
 * @brief Enables UWB ranging.
 */
void Enable_UWB(){
    uwb_enable = 1;
}

/**
 * @brief Callback invoked when a new UWB range is received.
 *
 * Reads the device short address, range, and RX power, then forwards
 * the data to the state machine.
 */
void _new_range() {
    uint16_t device = DW1000Ranging.getDistantDevice()->getShortAddress();
    float range = DW1000Ranging.getDistantDevice()->getRange();
    float rx_power = DW1000Ranging.getDistantDevice()->getRXPower();
    State_UWB_New_Range(device, range, rx_power);
}

/**
 * @brief Callback invoked when a new UWB device is detected.
 *
 * @param device Pointer to the detected DW1000 device.
 */
void _new_device(DW1000Device* device) {}

/**
 * @brief Callback invoked when a previously detected UWB device becomes inactive.
 *
 * @param device Pointer to the inactive DW1000 device.
 */
void _inactive_device(DW1000Device* device) {}