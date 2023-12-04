#ifndef __MAIN_H__
#define __MAIN_H__

#include "avr.h"
#include <string.h>

struct dac {
    uint8_t byte_high, byte_low;
    uint16_t value;
};

struct usart {
    uint8_t byte;
    uint16_t baud, prescale;
};

struct i2c {
    uint8_t status, byte;
};

struct sensor {
    float flow;
};

void adc_init(void);

void sample_f1031v(struct sensor *);

void mcp4725_update(struct sensor *, struct dac *, struct i2c *);
void mcp4725_tx(struct dac *, struct i2c *);
void mcp4725_bypass(struct dac *);

void i2c_tx(struct i2c *);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(void);

void forward_bit_address(uint8_t *);
void lcd_tx_data(uint8_t byte);
void lcd_tx_cmd(uint8_t byte);
void lcd_init(void);

void usart_tx(struct usart *);
void usart_init(struct usart *);

void write_usart(uint8_t *);
void report_data(struct sensor *, struct dac *, struct usart *);
void calibration(struct dac *, struct i2c *);

#endif