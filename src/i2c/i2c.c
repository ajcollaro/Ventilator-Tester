/* I2C Driver. */

#include "i2c.h"

static volatile uint8_t i2c_status;
static volatile uint8_t i2c_data;

void i2c_status_blank(void)
{
    i2c_status = 0;
}

void i2c_status_increment(void)
{
    i2c_status++;
}

uint8_t i2c_status_return(void)
{
    return i2c_status;
}

uint8_t i2c_tx(uint8_t byte)
{
    /* Send byte of data to slave device. */
    TWDR = byte;
    TWCR = (1 << TWINT)|(1 << TWEN);

    while(!(TWCR & (1 << TWINT)));

    return TWSR;
}

void i2c_tx_stop(void)
{
    /* Send Stop signal to slave device. */
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);

    while(TWCR & (1 << TWSTO));
}

uint8_t i2c_tx_start(void)
{
    /* Send Start signal to slave device. */
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);

    while(!(TWCR & (1 << TWINT)));

    return TWSR;
}

void i2c_init(void)
{
    /* I2C using two-wire interface. Operating @ 100KHz */
    TWBR = 0x0C; /* 0x48 for 100KHz, 0x0C for 400KHz */
}