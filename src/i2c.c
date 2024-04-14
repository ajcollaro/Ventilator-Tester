#include "main.h"

enum BUS_SPEED {
    SPEED_ONE = 0x48, /* 100KHz. */
    SPEED_TWO = 0x0C /* 400KHz. */
};

void i2c_tx(i2c_t *bus)
{
    /* Send bytes of data to slave device. */
    for(uint8_t i = 0; i <= sizeof(bus->bytes); i++)
    {
        TWDR = bus->bytes[i];
        TWCR = (1 << TWINT)|(1 << TWEN);

        while(!(TWCR & (1 << TWINT)));
    };
}

void i2c_tx_stop(void)
{
    /* Send Stop signal to slave device. */
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);

    while(TWCR & (1 << TWSTO));
}

void i2c_tx_start(void)
{
    /* Send Start signal to slave device. */
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);

    while(!(TWCR & (1 << TWINT)));
}

void i2c_init(void)
{
    /* I2C using two-wire interface. */
    TWBR = SPEED_TWO;
}