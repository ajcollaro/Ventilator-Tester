#include "main.h"

enum BUS_SPEED {
    SPEED_ONE = 0x48, /* 100KHz. */
    SPEED_TWO = 0x0C /* 400KHz. */
};

enum MCP4725_MAGIC_NUMBERS {
    DEVICE_ADDRESS = 0x63<<1,
    DEVICE_ADDRESS_SIM = 0xC2,
    CO = 0x40
};

void i2c_tx(i2c_t *i2c)
{
    /* Send bytes of data to slave device. */
    for(uint8_t i = 0; i <= sizeof(i2c->bytes); i++)
    {
        TWDR = i2c->bytes[i];
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

void i2c_init(i2c_t *i2c)
{
    /* I2C using two-wire interface. */
    TWBR = SPEED_TWO;

    /* Setup data to be transmitted. */
    i2c->device = DEVICE_ADDRESS;
    i2c->command = CO;
}