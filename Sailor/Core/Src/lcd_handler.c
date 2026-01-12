#include "lcd_handler.h"

I2C_HandleTypeDef* h_lcd_i2c = 0;
uint8_t tx_queue[QUEUE_SIZE] = {0};
uint16_t head_pointer = 0;
uint16_t tail_pointer = 0;
uint8_t transmission_going = 0;

const uint8_t X_LCD_COORDS[2] = {0, 0};
const uint8_t Y_LCD_COORDS[2] = {0, 9};
const uint8_t Z_LCD_COORDS[2] = {1, 0};

LCD_Status Initialize_LCD_Handler(I2C_HandleTypeDef* i2c_handle){
	h_lcd_i2c = i2c_handle;
	return lcd_init();
};

LCD_Status Put_Cursor(uint8_t row, uint8_t column){
	switch (row)
	{
		case 0:
			column |= 0x80;
			break;
		case 1:
			column |= 0xC0;
			break;
	}
	return add_command_to_queue(column);
}

LCD_Status Print_String(char* txt, uint8_t size){
	if (has_queue_space(size) == 0){
		return LCD_QUEUE_FULL;
	}
	for (uint8_t i=0;i<size;i++){
		LCD_Status result = add_data_to_queue(txt[i]);
		if (result != LCD_OK){
			return result;
		}
	}
	begin_transmission();
	return LCD_OK;
}

LCD_Status Print_String_At_Pos(char* txt, uint8_t size, uint8_t row, uint8_t column){
	Put_Cursor(row, column);
	return Print_String(txt, size);
}

LCD_Status Print_Whole_Position(float x, float y, float z){
	char buffer[12];
	uint8_t size = 0;
	size = sprintf(buffer, "x=%.2fm", x);
	Print_String_At_Pos(buffer, size, X_LCD_COORDS[0], X_LCD_COORDS[1]);
	size = sprintf(buffer, "y=%.2fm", y);
	Print_String_At_Pos(buffer, size, Y_LCD_COORDS[0], Y_LCD_COORDS[1]);
	size = sprintf(buffer, "z=%.2fm", z);
	Print_String_At_Pos(buffer, size, Z_LCD_COORDS[0], Z_LCD_COORDS[1]);
	return LCD_OK;
}


HAL_StatusTypeDef begin_transmission(){
	if (tail_pointer == head_pointer){
		return LCD_QUEUE_EMPTY;
	}
	if (is_transmission_going()){
		return LCD_OK;
	}
	HAL_StatusTypeDef result = send_one_byte();
	if (result != HAL_OK){
		return result;
	}
	transmission_going = 1;
	return HAL_OK;
}

uint8_t is_transmission_going(){
	return transmission_going;
}

void stop_transmission(){
	transmission_going = 0;
}

void increase_tail_pointer(uint16_t inc){
	if (tail_pointer == head_pointer){
		return;
	}
	uint8_t is_tail_smaller = tail_pointer < head_pointer;
	uint16_t new_tail_pointer = tail_pointer + inc;
	if (new_tail_pointer >= QUEUE_SIZE){
		new_tail_pointer = new_tail_pointer - QUEUE_SIZE;
	}
	if (is_tail_smaller && tail_pointer > head_pointer){
		new_tail_pointer = head_pointer;
	}
	tail_pointer = new_tail_pointer;
}

LCD_Status copy_buffer_to_queue(uint8_t* buffer){
	uint16_t data_size = sizeof(buffer);
	if (has_queue_space(data_size) == 0){
		return LCD_QUEUE_FULL;
	}
	uint16_t head_to_end_distance = QUEUE_SIZE - head_pointer;
	if (head_to_end_distance < data_size){
		memcpy(&(tx_queue[head_pointer]), &(buffer[0]), head_to_end_distance);
		memcpy(&(tx_queue[0]), &(buffer[head_to_end_distance]), data_size-head_to_end_distance);
		head_pointer = data_size-head_to_end_distance;
		return LCD_OK;
	}
	else if (head_to_end_distance == data_size){
		memcpy(&(tx_queue[head_pointer]), buffer, data_size);
		head_pointer = 0;
		return LCD_OK;
	}
	else {
		memcpy(&(tx_queue[head_pointer]), buffer, data_size);
		head_pointer = head_pointer + data_size;
		return LCD_OK;
	}
}

uint8_t has_queue_space(uint16_t data_size){
	if (head_pointer == tail_pointer){
		return 1;
	}
	if (head_pointer > tail_pointer){
		return ((QUEUE_SIZE - head_pointer + tail_pointer) >= data_size);
	}
	if (head_pointer < tail_pointer){
		return ((tail_pointer - head_pointer) >= data_size);
	}
	return 0;
}

LCD_Status add_command_to_queue(char cmd){
	if (has_queue_space(COMMAND_SIZE) == 0){
		return LCD_QUEUE_FULL;
	}

	char data_u, data_l;
	data_u = (cmd & 0xF0);           // extract upper 4 bits
	data_l = ((cmd << 4) & 0xF0);    // extract lower 4 bits
	uint8_t data_t[4];
	// send upper 4 bits with enable pulse
	data_t[0] = data_u | 0x0C;   // EN=1, RS=0  -> bxxxx1100
	data_t[1] = data_u | 0x08;   // EN=0, RS=0  -> bxxxx1000
	// send lower 4 bits with enable pulse
	data_t[2] = data_l | 0x0C;   // EN=1, RS=0  -> bxxxx1100
	data_t[3] = data_l | 0x08;   // EN=0, RS=0  -> bxxxx1000
	return copy_buffer_to_queue(data_t);
}

LCD_Status add_data_to_queue(char data) {
	if (has_queue_space(COMMAND_SIZE) == 0){
		return LCD_QUEUE_FULL;
	}
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[1] = data_u|0x09;  //en=0, rs=1 -> bxxxx1001
	data_t[2] = data_l|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[3] = data_l|0x09;  //en=0, rs=1 -> bxxxx1001
	return copy_buffer_to_queue(data_t);
}

LCD_Status lcd_send_cmd (char cmd)
{
    char data_u, data_l;
    data_u = (cmd & 0xF0);           // extract upper 4 bits
    data_l = ((cmd << 4) & 0xF0);    // extract lower 4 bits

    uint8_t data_t[4];

    // send upper 4 bits with enable pulse
    data_t[0] = data_u | 0x0C;   // EN=1, RS=0  -> bxxxx1100
    data_t[1] = data_u | 0x08;   // EN=0, RS=0  -> bxxxx1000

    // send lower 4 bits with enable pulse
    data_t[2] = data_l | 0x0C;   // EN=1, RS=0  -> bxxxx1100
    data_t[3] = data_l | 0x08;   // EN=0, RS=0  -> bxxxx1000

    if (HAL_I2C_Master_Transmit(h_lcd_i2c, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100) == HAL_OK){
    	return LCD_OK;
    }
    return LCD_HAL_ERROR;
}

HAL_StatusTypeDef send_one_byte(){
	if (tail_pointer == head_pointer){
		return HAL_ERROR;
	}
	HAL_StatusTypeDef result = HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, &tx_queue[tail_pointer], 1);
	if (result != HAL_OK){
		return result;
	}
	increase_tail_pointer(1);
	return HAL_OK;
}

HAL_StatusTypeDef lcd_i2c_transmit_it_callback(I2C_HandleTypeDef *hi2c){
	if (!is_transmission_going()){
		return HAL_OK;
	}
	if (tail_pointer == head_pointer){
		stop_transmission();
		return HAL_OK;
	}
	return send_one_byte();

	//	if (hi2c != h_lcd_i2c){
//		return;
//	}

}
HAL_StatusTypeDef lcd_i2c_receive_it_callback(I2C_HandleTypeDef *hi2c){
	return HAL_OK;
}

LCD_Status lcd_init (void) {
  LCD_Status result = LCD_OK;
  // 4 bit initialization
  HAL_Delay(50);  // wait for >40ms
  result += lcd_send_cmd (0x30);
  HAL_Delay(5);  // wait for >4.1ms
  result += lcd_send_cmd (0x30);
  HAL_Delay(1);  // wait for >100us
  result += lcd_send_cmd (0x30);
  HAL_Delay(10);
  result += lcd_send_cmd (0x20);  // 4bit mode
  HAL_Delay(10);

  if (result != LCD_OK){
	  return LCD_INIT_FAIL;
  }

  // display initialization
  result += lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
  HAL_Delay(1);
  result += lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
  HAL_Delay(1);
  result += lcd_send_cmd (0x01);  // clear display
  HAL_Delay(2);
  result += lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
  HAL_Delay(1);
  result += lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

  if (result != LCD_OK){
	  return LCD_INIT_FAIL;
  }

  return LCD_OK;
};
