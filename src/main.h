#ifndef __MAIN_H__
#define __MAIN_H__

#include "avr.h"
#include "dac/dac.h"
#include "i2c/i2c.h"
#include "sensors/sensors.h"
#include "usart/usart.h"
#include <string.h>

#define BAUD_RATE 9600
#define WAIT_TIME_MS 20 /* Wait time in milliseconds. */
#define REPORT_WAITS 25 /* LCD and USART waits before refresh. */
#define DEBUG_OUTPUT 0 /* Output additional data via USART. Disable unless testing. */

void write_usart(uint8_t *ptr);
void report_data(struct flowsensor *sensor, struct dac *dac, struct usart *usart, struct i2c *i2c);
void calibration(uint8_t mode);

void report_debug(struct dac *dac, struct usart *usart, struct i2c *i2c);

#endif