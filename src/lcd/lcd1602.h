#ifndef __LCD_H__
#define __LCD_H__

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

void forward_bit_address(uint8_t *byte);
void lcd_tx_data(uint8_t byte);
void lcd_tx_cmd(uint8_t byte);
void lcd_init(void);

#endif