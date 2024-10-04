#include "i2c.h"
#include "lcd.h"
#include "main.h"

#define CAL_NOTIFY "Cal test signal"

#define OUT_5V 0xFFFF
#define OUT_0V 0x0000

static void calibrate(dac_t *dac, i2c_t *i2c, cal_t *cal)
{
    lcd_blank();
    lcd_tx(&cal->buffer[0]);

    dac->value = cal->level;
    mcp4725_tx(dac, i2c);

    _delay_ms(10000);
}

void calibration_setup(dac_t *dac, i2c_t *i2c, cal_t *cal)
{
    /* Notify user of cal test signal. */
    memcpy(cal->buffer, CAL_NOTIFY, sizeof(CAL_NOTIFY));

    /* Send high. */
    cal->level = OUT_5V;
    calibrate(dac, i2c, cal);

    /* Send low. */
    cal->level = OUT_0V;
    calibrate(dac, i2c, cal);
}