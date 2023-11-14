#include "main.h"
#include "dac/dac.h"
#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "lcd/lcd1602.h"
#include "sensors/f1031v.h"
#include "usart/usart.h"

#define UNITS " L/min (STP) "
#define CALIBRATION_LOW " 0V Calibration "
#define CALIBRATION_HIGH " 5V Calibration "

/* Holds one line of text. */
static char buffer[16];
static uint8_t *ptr = buffer;

void write_usart(uint8_t *ptr)
{
    while(!(*ptr == '\0'))
    {
        usart_tx(*ptr);
        ptr++;
    }
}

void report_data(struct flowsensor *sensor, struct dac *dac, struct usart *usart, struct i2c *i2c)
{
    /* Blank LCD (slow). */
    lcd_tx_cmd(0x01);

    /* Sample F1031V. */
    sample_f1031v(sensor);

    /* Convert flow to string. */
    itoa(sensor->flow, buffer, 10);
    write_usart(ptr); /* Write over I2C while updating LCD. */
    forward_bit_address(ptr); /* Send address for writing to LCD. */

    /* Send units. */
    memcpy(buffer, UNITS, 16);
    write_usart(ptr);
    forward_bit_address(ptr);

    /* Write debug data if enabled.
     * Fair timing, flash and memory costs so leave disabled unless testing.
     */
    if (DEBUG_OUTPUT) {
        report_debug(dac, usart, i2c);
    }
}

void calibration(uint8_t mode)
{
    lcd_tx_cmd(0x01);
    
    switch(mode)
    {
        case 0:
            memcpy(buffer, CALIBRATION_LOW, 16);
            write_usart(ptr);
            forward_bit_address(ptr);
            break;
        case 1:
            memcpy(buffer, CALIBRATION_HIGH, 16);
            write_usart(ptr);
            forward_bit_address(ptr);
            break;
    }
}