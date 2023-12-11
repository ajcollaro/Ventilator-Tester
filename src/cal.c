#include "main.h"

void calibrate(union dac *mcp4725, struct i2c *bus, struct cal *setting)
{
    uint8_t *ptr = &setting->buffer;

    lcd_tx_cmd(0x01);

    forward_bit_address(ptr);

    mcp4725->value = setting->size;
    mcp4725_tx(mcp4725, bus);

    _delay_ms(10000);
}