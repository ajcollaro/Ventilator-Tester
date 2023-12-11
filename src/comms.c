#include "main.h"

#define UNITS " L/min (STP) "

void write_usart(uint8_t *ptr)
{
    while(!(*ptr == '\0'))
    {
        usart_tx(ptr);
        ptr++;
    }
}

void report_data(struct sensor *f1031v, union dac *mcp4725, struct usart *serial)
{
    /* Holds one line of text. */
    char buffer[16];
    uint8_t *ptr = &buffer;

    /* Blank LCD (slow). */
    lcd_tx_cmd(0x01);

    /* Convert flow to string. */
    itoa((uint16_t)f1031v->flow, buffer, 10);
    write_usart(ptr);
    forward_bit_address(ptr); /* Send address for writing to LCD. */
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    write_usart(ptr);
    forward_bit_address(ptr);
}