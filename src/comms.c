#include "main.h"

#define UNITS " L/min (STP)"

void report_data(sensor_t *sensor)
{
    char buffer[16];
    char *ptr = &buffer[0];

    lcd_blank();

    /* Convert flow to string. */
    itoa((uint16_t)sensor->flow, buffer, 10);
    lcd_write(ptr);
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    lcd_write(ptr);
}