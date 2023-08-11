/* Report data via USART and LCD interfaces. */

#include "main.h"
#include "i2c/i2c.h"
#include "lcd/lcd1602.h"
#include "sensors/f1031v.h"
#include "usart/usart.h"

#define UNITS " L/min (STP) "

/* Holds one line of text. */
static char buffer[16];

void report_data(void)
{
    /* Address of line. */
    uint8_t *ptr = buffer;

    /* Blank LCD (slow). */
    lcd_tx_cmd(0x01);

    /* Sample sensor. */
    uint16_t f1031v = sample_f1031v();

    /* Convert flow to string. */
    itoa(f1031v, buffer, 10);

    write_usart(ptr); /* Write over I2C while updating LCD. */
    forward_bit_address(&buffer); /* Send address for writing to LCD. */

    /* Send units. */
    memcpy(buffer, UNITS, 16);
    
    write_usart(ptr);
    forward_bit_address(&buffer);

    /* Write debug data if enabled. */
    if (DEBUG_OUTPUT)
    {
        report_debug();
    }
}

void write_usart(uint8_t *ptr)
{
    while(*ptr > 0)
    {
        usart_tx(*ptr);
        ptr++;
    }
}

void write_lcd(uint8_t *ptr)
{
    while(*ptr > 0)
    {
        lcd_tx(0, 0, *ptr);
        ptr++;
    }
}

