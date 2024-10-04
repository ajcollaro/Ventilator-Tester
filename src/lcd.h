#pragma once

#include <avr/io.h>
#include <util/delay.h>

void lcd_tx(char *);
void lcd_blank(void);
void lcd_init(void);