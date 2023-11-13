/* LCD1602 4-bit Driver. */

#include "lcd/lcd1602.h"

static void write_nibble(uint8_t byte)
{
    /* Test most significant 4-bits and set each pin. */
    if(byte & 0x10)
        LCD_DATA_PORT1 |=  (1 << LCD_DATA_PIN1);
    else
        LCD_DATA_PORT1 &= ~(1 << LCD_DATA_PIN1);

    if(byte & 0x20)
        LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN2);
    else
        LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN2);

    if(byte & 0x40)
        LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN3);
    else
        LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN3);

    if(byte & 0x80)
        LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN4);
    else
        LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN4);
}

void forward_bit_address(uint8_t *byte)
{
    /* Forward address of each bit to the LCD. */
    while((*byte)!='\0')
    {
        lcd_tx_data(*byte);
        byte++; /* Next byte. */
    }
} 

void lcd_tx_data(uint8_t byte)
{
    /* Send data to LCD. */
    write_nibble(byte);
    
    LCD_CONTROL_PORT |=  (1 << LCD_RS_PIN)|(1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(2);

    byte <<= 4; /* Shift LSBs to MSBs. */

    write_nibble(byte);

    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(50);
}

void lcd_tx_cmd(uint8_t byte)
{
    /* Send command to LCD. */
    write_nibble(byte);

    LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN);
    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);  
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_ms(1);

    byte <<= 4;  /* Shift LSBs to MSBs. */

    write_nibble(byte);
    
    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_ms(2);
}

void lcd_init(void)
{
    /* Set data pins. */
    DDRC = 0xFF;
    DDRD = 0xFF;
    DDRL = 0xFF;

    _delay_ms(1000);
    
    /* Enable 4-bit mode with 2-lines. */
    lcd_tx_cmd(0x02);
    lcd_tx_cmd(0x28);
    lcd_tx_cmd(0x0C);
    lcd_tx_cmd(0x01);
}