#include "main.h"

void calibrate(dac_t *mcp4725, i2c_t *bus, cal_t *cal_setting)
{
    uint8_t *ptr = &cal_setting->buffer;

    lcd_blank();
    lcd_write(ptr);

    mcp4725->value = cal_setting->level;
    mcp4725_tx(mcp4725, bus);

    _delay_ms(10000);
}