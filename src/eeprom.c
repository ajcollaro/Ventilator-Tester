/* EEPROM Driver.
 * 4KB on board the ATmega2560 (100,000 write cycles).
 */

#include "main.h"

void eeprom_write(uint16_t address, uint8_t byte)
{
    /* Ensure previous write has finished. */ 
    while(EECR & (1<<EEPE));

    EEAR = address;
    EEDR = byte; /* Data to write. */

    EECR |= (1 << EEMPE);

    /* Start write. */
    EECR |= (1 << EEPE);
}

uint8_t eeprom_read(uint16_t address)
{
    /* Ensure previous write has finished. */ 
    while(EECR & (1<<EEPE));

    EEAR = address;

    EECR |= (1 << EERE);

    /* Return data from register. */
    return EEDR;
}
