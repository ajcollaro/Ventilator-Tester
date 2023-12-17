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

void report_data(sensor_t *f1031v, dac_t *mcp4725)
{
    char buffer[16];
    uint8_t *ptr = &buffer;

    lcd_blank();

    /* Convert flow to string. */
    itoa((uint16_t)f1031v->flow, buffer, 10);
    forward_bit_address(ptr);
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    forward_bit_address(ptr);
}