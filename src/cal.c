#include "main.h"

#define CAL_5V " 5V Calibration"
#define CAL_0V " 0V Calibration"

enum MAGIC_NUMBERS {
    OUT_5V = 0xFFFF,
    OUT_0V = 0x0000
};

void calibrate(dac_t *mcp4725, i2c_t *bus, cal_t *setting)
{
    uint8_t *ptr = &setting->buffer;

    lcd_blank();
    lcd_write(ptr);

    mcp4725->value = setting->size;
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