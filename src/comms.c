#include "main.h"

#define UNITS " L/min (STP)"

void write_usart(uint8_t *ptr)
{
    while(!(*ptr == '\0'))
    {
        usart_tx(ptr);
        ptr++;
    }
}

void report_data(sensor_t *sensor)
{
    char buffer[15];
    uint8_t *ptr = &buffer;

    lcd_blank();

    /* Convert flow to string. */
    itoa((uint16_t)sensor->flow, buffer, 10);
    lcd_write(ptr);
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    lcd_write(ptr);
}