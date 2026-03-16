#include "sailor_comm.h"
#include <string.h>

/**
 * @brief Initializes the UART interface used for sailor communication.
 *
 * @details
 * Sets up the Serial2 port with 9600 baud rate and 8N1 configuration.
 */
void Initialize_Sailor_Comm(){
    Serial2.begin(9600, SERIAL_8N1);
}

/**
 * @brief Sends the current position to the observer via UART.
 *
 * @param current_pos Pointer to the Position structure containing x, y, z coordinates.
 *
 * @details
 * The function creates a fixed-size message buffer, copies the Position
 * structure into the correct offset, and sends the full message via Serial2.
 */
void Send_Current_Position(Position* current_pos) {
    uint8_t message[SAILOR_MESSAGE_SIZE] = {0};
    memcpy(&(message[OBS_POSITION_STRUCT]), current_pos, sizeof(Position));
    Serial2.write(message, SAILOR_MESSAGE_SIZE);
}
