#include "main.h"

#define UNITS " L/min (STP) "
#define CALIBRATION_LOW " 0V Calibration"
#define CALIBRATION_HIGH " 5V Calibration"

void write_usart(uint8_t *ptr)
{
    while(!(*ptr == '\0'))
    {
        usart_tx(ptr);
        ptr++;
    }
}

void report_data(struct sensor *f1031v, struct dac *mcp4725, struct usart *serial, struct i2c *bus)
{
    /* Holds one line of text. */
    char buffer[16];
    uint8_t *ptr = &buffer;

    /* Blank LCD (slow). */
    lcd_tx_cmd(0x01);

    /* Convert flow to string. */
    itoa((uint16_t)f1031v->flow, buffer, 10);
    write_usart(ptr);
    forward_bit_address(ptr); /* Send address for writing to LCD. */
    
    /* Send units. */
    memcpy(buffer, UNITS, sizeof(UNITS));
    write_usart(ptr);
    forward_bit_address(ptr);
}

void calibration(struct dac *mcp4725, struct i2c *bus)
{
    /* Holds one line of text. */
    char buffer[16];
    uint8_t *ptr = &buffer;

    lcd_tx_cmd(0x01);
    
    /* Update LCD and send 5V via DAC. */
    memcpy(buffer, CALIBRATION_HIGH, sizeof(CALIBRATION_HIGH));
    forward_bit_address(ptr);
    mcp4725->byte_high = 0xFF, mcp4725->byte_low = 0xFF;
    mcp4725_tx(mcp4725, bus);

    /* Wait 10 sec. */
    _delay_ms(10000);

    lcd_tx_cmd(0x01);

    /* Update LCD and send 0V via DAC. */
    memcpy(buffer, CALIBRATION_LOW, sizeof(CALIBRATION_LOW));
    forward_bit_address(ptr);
    mcp4725->byte_high = 0x00, mcp4725->byte_low = 0x00;
    mcp4725_tx(mcp4725, bus);

    /* Wait 10 sec. */
    _delay_ms(10000);
}