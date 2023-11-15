#include "main.h"

#define I2C_STATUS " \tI2C debug: "
#define DAC_INPUT_HIGH " \tDAC input h: "
#define DAC_INPUT_LOW " \tDAC input l: "
#define DAC_SENSOR_MEASUREMENT " \tValue: "
#define NEW_LINE " \n"

/* Holds one line of text. */
static char buffer[16];
static uint8_t *ptr = buffer;

void report_debug(struct dac *dac, struct usart *usart, struct i2c *bus)
{
    /* Values to output. */
    bus->status = TWSR;
    
    memcpy(buffer, I2C_STATUS, 16);
    write_usart(ptr);

    itoa(bus->status, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_INPUT_HIGH, 16);
    write_usart(ptr);

    itoa(dac->byte_high, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_INPUT_LOW, 16);
    write_usart(ptr);

    itoa(dac->byte_low, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_SENSOR_MEASUREMENT, 16);
    write_usart(ptr);

    itoa(dac->measurement, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, NEW_LINE, 16);
    write_usart(ptr);
}