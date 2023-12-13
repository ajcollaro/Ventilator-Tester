#include "main.h"

void calibrate(dac_t *mcp4725, i2c_t *bus, cal_t *setting)
{
    uint8_t *ptr = &setting->buffer;

    lcd_tx_cmd(0x01);

    forward_bit_address(ptr);

    mcp4725->value = setting->size;
    mcp4725_tx(mcp4725, bus);

    _delay_ms(10000);
}