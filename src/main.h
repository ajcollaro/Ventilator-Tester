#pragma once

#include "avr.h"
#include <avr/interrupt.h>
#include <string.h>

typedef union {
    struct {
        uint8_t byte_hi;
        uint8_t byte_lo;
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
        uint8_t byte2;
        uint8_t byte3;
    };
    uint8_t bytes[3];
} i2c_t;

typedef struct {
    float flow;
} sensor_t;

typedef struct {
    char buffer[15];
    uint16_t size;
} cal_t;

void adc_init(void);

void calibrate(dac_t *, i2c_t *, cal_t *);

void sample_f1031v(sensor_t *);

void mcp4725_update(sensor_t *, dac_t *, i2c_t *);
void mcp4725_tx(dac_t *, i2c_t *);
void mcp4725_bypass(dac_t *);

void i2c_tx(i2c_t *);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(void);

void lcd_write(uint8_t *);
void lcd_tx_data(uint8_t);
void lcd_tx_cmd(uint8_t);
void lcd_blank(void);
void lcd_init(void);

void usart_tx(usart_t *);
void usart_init(usart_t *);

void write_usart(uint8_t *);
void report_data(sensor_t *, dac_t *);
void calibration(dac_t *, i2c_t *);