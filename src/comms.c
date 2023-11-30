#include "main.h"

#define UNITS " L/min (STP) "
#define CALIBRATION_LOW " 0V Calibration"
#define CALIBRATION_HIGH " 5V Calibration"

/* Holds one line of text. */
static char buffer[16];
static uint8_t *ptr = buffer;

void write_usart(uint8_t *ptr)
{
    while(!(*ptr == '\0'))
    {
        usart_tx(ptr);
        ptr++;
    }
}

void report_data(struct sensor_t *sensor, struct dac_t *dac, struct usart_t *serial, struct i2c_t *i2c)
{
    /* Blank LCD (slow). */
    lcd_tx_cmd(0x01);

    /* Convert flow to string. */
    itoa((uint16_t)sensor->flow, buffer, 10);
    write_usart(ptr);
    forward_bit_address(ptr); /* Send address for writing to LCD. */
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    write_usart(ptr);
    forward_bit_address(ptr);
}

void calibration(uint8_t mode)
{
    lcd_tx_cmd(0x01);
    
    switch(mode)
    {
        case 0:
            memcpy(buffer, CALIBRATION_LOW, sizeof(CALIBRATION_LOW));
            forward_bit_address(ptr);
            break;
        case 1:
            memcpy(buffer, CALIBRATION_HIGH, sizeof(CALIBRATION_LOW));
            forward_bit_address(ptr);
            break;
    }
}