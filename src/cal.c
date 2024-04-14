#include "main.h"

#define CAL_VOLTS_5 "5V Calibration"
#define CAL_VOLTS_0 "0V Calibration"

enum MAGIC_NUMBERS {
    OUT_5V = 0xFFFF,
    OUT_0V = 0x0000
};

void calibrate(dac_t *dac, i2c_t *i2c, cal_t *cal)
{
    uint8_t *ptr = cal->buffer;

    lcd_blank();
    lcd_write(ptr);

    dac->value = cal->level;
    mcp4725_tx(dac, i2c);

    _delay_ms(10000);
}

void calibration_setup(dac_t *dac, i2c_t *i2c, cal_t *cal)
{
    /* Send high. */
    memcpy(cal->buffer, CAL_VOLTS_5, sizeof(CAL_VOLTS_5));
    cal->level = OUT_5V;
    calibrate(dac, i2c, cal);

    /* Send low. */
    memcpy(cal->buffer, CAL_VOLTS_0, sizeof(CAL_VOLTS_0));
    cal->level = OUT_0V;
    calibrate(dac, i2c, cal);
}