#pragma once

#include "avr.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    struct {
        uint8_t byte_big;
        uint8_t byte_little;
    };
    uint16_t value;
} dac_t;

typedef struct {
    uint8_t byte;
    uint16_t baud, prescale;
} usart_t;

typedef union {
    struct {
        uint8_t device;
        uint8_t command;
        uint8_t byte_big;
        uint8_t byte_little;
    };
    uint8_t bytes[4];
} i2c_t;

typedef struct {
    float flow;
} sensor_t;

typedef struct {
    char buffer[16];
    uint16_t level;
} cal_t;

void adc_init(void);

void calibrate(dac_t *, i2c_t *, cal_t *);
void calibration_setup(dac_t *, i2c_t *, cal_t *);

void sample_f1031v(sensor_t *);

void mcp4725_update(dac_t *, sensor_t *, i2c_t *);
void mcp4725_tx(dac_t *, i2c_t *);
void mcp4725_bypass(dac_t *);

void i2c_tx(i2c_t *);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(i2c_t *);

void lcd_write(char *);
void lcd_tx_data(uint8_t);
void lcd_tx_cmd(uint8_t);
void lcd_blank(void);
void lcd_init(void);

void report_data(sensor_t *);