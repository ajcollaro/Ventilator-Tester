#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

struct i2c {
    uint8_t status;
    uint8_t byte;
};

void i2c_tx(struct i2c *i2c);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(void);

#endif