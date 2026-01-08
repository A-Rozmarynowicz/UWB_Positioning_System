#include "lcd_handler.h"

I2C_HandleTypeDef* h_lcd_i2c = 0;

void initialize_handler(I2C_HandleTypeDef* i2c_handle){
	h_lcd_i2c = i2c_handle;
};

void lcd_init (void)
{
  // 4 bit initialisation
  HAL_Delay(50);  // wait for >40ms
  lcd_send_cmd (0x30);
  HAL_Delay(5);  // wait for >4.1ms
  lcd_send_cmd (0x30);
  HAL_Delay(1);  // wait for >100us
  lcd_send_cmd (0x30);
  HAL_Delay(10);
  lcd_send_cmd (0x20);  // 4bit mode
  HAL_Delay(10);

  // display initialisation
  lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
  HAL_Delay(1);
  lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
  HAL_Delay(1);
  lcd_send_cmd (0x01);  // clear display
  HAL_Delay(2);
  lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
  HAL_Delay(1);
  lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
};

uint64_t cipa = 0;

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[1] = data_u|0x09;  //en=0, rs=1 -> bxxxx1001
	data_t[2] = data_l|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[3] = data_l|0x09;  //en=0, rs=1 -> bxxxx1001
	cipa = 1;
	if (HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, &data_t[0], 1) != 0x00){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	}
//	HAL_I2C_Master_Transmit (h_lcd_i2c, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
};

void lcd_send_string (char *str)
{
  while (*str) lcd_send_data (*str++);
};

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    lcd_send_cmd (col);
};

void lcd_send_cmd (char cmd)
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
//    HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, data_t, sizeof(data_t));
    HAL_I2C_Master_Transmit(h_lcd_i2c, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
};

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	char data = 'C';
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[1] = data_u|0x09;  //en=0, rs=1 -> bxxxx1001
	data_t[2] = data_l|0x0D;  //en=1, rs=1 -> bxxxx1101
	data_t[3] = data_l|0x09;
	if (cipa == 1) {
		if (HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, &data_t[1], 1) != 0x00){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		}
	}
	else if (cipa == 2){
		if (HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, &data_t[2], 1) != 0x00){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		}
	}
	else if (cipa == 3){
		if (HAL_I2C_Master_Transmit_IT(h_lcd_i2c, SLAVE_ADDRESS_LCD, &data_t[3], 1) != 0x00){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		}
	}

	cipa++;

    if (hi2c->Instance == h_lcd_i2c)
    {

    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {

    }
}
