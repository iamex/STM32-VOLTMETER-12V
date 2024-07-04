#include "main.h"


//
// ************************START OF LCD CODE *************************
//
// In the following LCD code it is assumed that the LCD is connected to the NUCLEO-f303ret6
// as follows in 4 bit mode:
//
// RS to PA6
// E to PA7
// D4 to PA8
// D5 to pa9
// D6 TO PA10
// D6 to PA10
// D7 to PA11
//
// LCD Header Code:
#define LCD_EN GPIO_PIN_7
#define LCD_RS GPIO_PIN_6
#define LCD_D4 GPIO_PIN_8
#define LCD_D5 GPIO_PIN_9
#define LCD_D6 GPIO_PIN_10
#define LCD_D7 GPIO_PIN_11


//
// Send clock pulse to the LCD
//

void LCD_STROBE()
{
	HAL_GPIO_WritePin(GPIOA,LCD_EN,GPIO_PIN_SET);
	HAL_Delay(0.1);
	HAL_GPIO_WritePin(GPIOA,LCD_EN,GPIO_PIN_RESET);
	HAL_Delay(0.1);
}

//
// Send a command to the LCD
//
void lcd_write_cmd(unsigned char c)
{
	unsigned int d;
	d = c;
	d = (d << 4) & 0x0F00;					// Extract upper nibble
	GPIOA->ODR = d;						// Output to GPIOA
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_RESET);		// Clear RS
	LCD_STROBE();						// Clock enable bit
	d = c;
	d = (d << 8) & 0x0F00;					// Extract lower nibble
	GPIOA->ODR = d;						// Output to GPIOA
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_RESET);		// Clear RS
	LCD_STROBE();						// Clock enable bit
	HAL_Delay(0.1);
}

//
// Send data to LCD
//

void lcd_write_data(unsigned char c)
{
	unsigned int d;

	d = c;
	d = (d << 4) & 0x0F00;					// Extract upper nibble
	GPIOA->ODR = d;						// Output to GPIOA
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_SET);		// Set RS HIGH
	LCD_STROBE();						// Clock enable bit
	d = c;
	d = (d << 8) & 0x0F00;					// Extract lower nibble
	GPIOA->ODR = d;						// Output to GPIOA
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_SET);		// Set RS HIGH
	LCD_STROBE();
}

//
// Clear LCD
//

void lcd_clear(void)
{
	lcd_write_cmd(0x1);
	HAL_Delay(5);
}

//
// Display text message on LCD
//
void lcd_puts(const char *s)
{
	while(*s)
		lcd_write_data(*s++);
}


//
// Display single character on LCD
//

void lcd_putch(char c)
{

	unsigned int d;
	d = c;
	d = (d << 4) & 0x0F00;
	GPIOA->ODR = d;
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_SET);
	LCD_STROBE();
	d = c;
	d = (d << 8) & 0x0F00;
	GPIOA->ODR = d;
	HAL_GPIO_WritePin(GPIOA,LCD_RS,GPIO_PIN_SET);
	LCD_STROBE();
}

// Position the cursor at column, row
//

void lcd_goto(int col, int row)
{
	char address;
	if(row == 0) address = 0;
	if(row == 1) address = 0x40;
	address += col - 1;
	lcd_write_cmd(0x80 | address);
}

//
// Initialize the LCD
//
void lcd_init(void)
{
	GPIOA->ODR = 0;
	HAL_Delay(50);
	GPIOA->ODR = 0X0300;
	LCD_STROBE();
	HAL_Delay(30);
	LCD_STROBE();
	HAL_Delay(20);
	LCD_STROBE();
	HAL_Delay(20);
	GPIOA->ODR = 0X0200;
	LCD_STROBE();
	HAL_Delay(5);
	lcd_write_cmd(0x28);
	HAL_Delay(5);
	lcd_write_cmd(0x0F);
	HAL_Delay(5);
	lcd_write_cmd(0x01);
	HAL_Delay(5);
	lcd_write_cmd(0x06);
	HAL_Delay(5);
}







