#ifndef __MAIN_H__
#define __MAIN_H__

#include "avr.h"
#include <string.h>

#define BAUD_RATE 9600
#define REPORT_WAITS 255 /* LCD and USART waits before refresh. */

struct dac_t {
    uint8_t byte_high, byte_low;
    uint16_t value;
};

struct usart_t {
    uint8_t byte;
    uint16_t baud, prescale;
};

struct i2c_t {
    uint8_t status, byte;
};

struct sensor_t {
    float flow, processed;
};

void adc_init(void);

void calibrate(struct dac_t *, struct i2c_t *);

void report_debug(struct sensor_t *, struct dac_t *, struct usart_t *, struct i2c_t *);

void sample_f1031v(struct sensor_t *);

void mcp4725_update(struct sensor_t *, struct dac_t *, struct i2c_t *);
void mcp4725_tx(struct dac_t *, struct i2c_t *);
void mcp4725_bypass(struct dac_t *);

void i2c_tx(struct i2c_t *);
void i2c_tx_stop(void);
void i2c_tx_start(void);
void i2c_init(void);

void forward_bit_address(uint8_t *);
void lcd_tx_data(uint8_t byte);
void lcd_tx_cmd(uint8_t byte);
void lcd_init(void);

void usart_tx(struct usart_t *);
void usart_init(struct usart_t *);

void write_usart(uint8_t *);
void report_data(struct sensor_t *, struct dac_t *, struct usart_t *, struct i2c_t *);
void calibration(uint8_t mode);

#endif