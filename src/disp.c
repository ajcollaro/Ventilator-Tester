#include "lcd.h"
#include "main.h"

#define UNITS " L/min (STP)"

void report_data(sensor_t *sensor)
{
    char buffer[16];

    lcd_blank();

    /* Convert flow to string. */
    itoa((uint16_t)sensor->flow, buffer, 10);
    lcd_tx(&buffer[0]);
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    lcd_tx(&buffer[0]);
}