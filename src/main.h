#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

/* Speed of MCU in Hz. */
#ifndef F_CPU
#define F_CPU 16000000
#endif

/* Structures. */
typedef union {
    struct {
        uint8_t byte_big;
        uint8_t byte_little;
    };
    uint16_t value;
} dac_t;

typedef struct {
    uint8_t data;
    uint16_t baud;
    uint16_t prescale;
} usart_t;

typedef struct {
    float flow;
} sensor_t;

typedef struct {
    char buffer[16];
    uint16_t level;
} cal_t;

/* Function declarations. */
void adc_init(void);

void calibration_setup(dac_t *, i2c_t *, cal_t *);

void sample_f1031v(sensor_t *);

void mcp4725_update(dac_t *, sensor_t *, i2c_t *);
void mcp4725_tx(dac_t *, i2c_t *);

void report_data(sensor_t *);