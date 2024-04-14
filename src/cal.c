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

void calibration_setup(dac_t *mcp4725, i2c_t *bus, cal_t *settings)
{
    /* Send high. */
    memcpy(settings->buffer, CAL_5V, sizeof(CAL_5V));
    settings->size = OUT_5V;
    calibrate(settings->buffer, &bus, &settings);

    /* Send low. */
    memcpy(settings->buffer, CAL_0V, sizeof(CAL_0V));
    settings->size = OUT_0V;
    calibrate(settings->buffer, &bus, &settings);
}