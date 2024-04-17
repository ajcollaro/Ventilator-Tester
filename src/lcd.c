#include "main.h"

/* Physical connections to LCD. */
#define LCD_CONTROL_PORT    PORTL
#define LCD_RS_PIN          PORTL2
#define LCD_EN_PIN          PORTL4
#define LCD_DATA_PORT1      PORTD
#define LCD_DATA_PORT2      PORTC
#define LCD_DATA_PIN1       PORTD7
#define LCD_DATA_PIN2       PORTC1
#define LCD_DATA_PIN3       PORTC3
#define LCD_DATA_PIN4       PORTC5

enum LCD1602_MAGIC_NUMBERS {
    LCD_CLEARDISPLAY = 0x01,
    LCD_INIT4BIT = 0x02,
    LCD_DISPLAYONCURSOROFF = 0x0C
};

static void write_nibble(uint8_t byte)
{
    /* Test most significant 4-bits and set each pin. */
    (byte & 0x10) ? (LCD_DATA_PORT1 |=  (1 << LCD_DATA_PIN1)) : (LCD_DATA_PORT1 &= ~(1 << LCD_DATA_PIN1));
    (byte & 0x20) ? (LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN2)) : (LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN2));
    (byte & 0x40) ? (LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN3)) : (LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN3));
    (byte & 0x80) ? (LCD_DATA_PORT2 |=  (1 << LCD_DATA_PIN4)) : (LCD_DATA_PORT2 &= ~(1 << LCD_DATA_PIN4));
}

void lcd_write(char *byte)
{
    while((*byte)!='\0')
    {
        lcd_tx_data(*byte);
        byte++;
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

    byte <<= 4;

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

    byte <<= 4;

    write_nibble(byte);
    
    LCD_CONTROL_PORT |=  (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_CONTROL_PORT &= ~(1 << LCD_EN_PIN);
    _delay_ms(2);
}

void lcd_blank(void)
{
    lcd_tx_cmd(LCD_CLEARDISPLAY);
}

void lcd_init(void)
{
    /* Set data direction. */
    DDRC = 0xFF;
    DDRD = 0xFF;
    DDRL = 0xFF;

    _delay_ms(15);
    
    /* 4-bit mode, 1-line. */
    lcd_tx_cmd(LCD_INIT4BIT);
    lcd_tx_cmd(LCD_DISPLAYONCURSOROFF);
    lcd_tx_cmd(LCD_CLEARDISPLAY);
}