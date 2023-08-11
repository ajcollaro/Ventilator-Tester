#include "main.h"

void fan_init()
{
    /* Turn on until EEPROM defaults finished. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);
}