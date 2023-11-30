#include "main.h"

void calibrate(struct dac_t *dac, struct i2c_t *i2c)
{
    /* Send calibration signal (10 secs at 5V and 0V). */
    dac->byte_high = 0xFF, dac->byte_low = 0xFF;
    mcp4725_tx(dac, i2c);
    calibration(1);

    _delay_ms(1000);

    dac->byte_high = 0x00, dac->byte_low = 0x00;
    mcp4725_tx(dac, i2c);
    calibration(0);

    _delay_ms(1000);
}