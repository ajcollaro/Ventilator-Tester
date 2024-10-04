#pragma once

#include <avr/io.h>

typedef union {
    struct {
        uint8_t addr;
        uint8_t cmd;
        uint16_t data;
    };
    uint8_t bytes[4];
} i2c_t;

void i2c_tx(i2c_t *);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(i2c_t *);