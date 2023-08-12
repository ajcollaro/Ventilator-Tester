#include "main.h"
#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "sensors/f1031v.h"
#include "usart/usart.h"

#define I2C_STATUS " \tI2C debug: "
#define DAC_INPUT_HIGH " \tDAC input h: "
#define DAC_INPUT_LOW " \tDAC input l: "
#define DAC_SENSOR_MEASUREMENT " \tValue: "
#define NEW_LINE " \n"

/* Holds one line of text. */
static char buffer[16];

void report_debug(void)
{
    /* Address of line. */
    uint8_t *ptr = buffer;

    /* Values to output. */
    uint8_t i2c = TWSR;
    uint8_t dac_input_high = mcp4725_return_byte_high();
    uint8_t dac_input_low = mcp4725_return_byte_low();
    uint16_t measurement = return_measurement();
    
    memcpy(buffer, I2C_STATUS, 16);
    write_usart(ptr);

    itoa(i2c, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_INPUT_HIGH, 16);
    write_usart(ptr);

    itoa(dac_input_high, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_INPUT_LOW, 16);
    write_usart(ptr);

    itoa(dac_input_low, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, DAC_SENSOR_MEASUREMENT, 16);
    write_usart(ptr);

    itoa(measurement, buffer, 10);
    write_usart(ptr);

    memcpy(buffer, NEW_LINE, 16);
    write_usart(ptr);
}