#include "main.h"

void calibrate(struct dac *mcp4725, struct i2c *bus)
{
    /* Send calibration signal (10 secs at 5V and 0V). */
    mcp4725->byte_high = 0xFF, mcp4725->byte_low = 0xFF;
    mcp4725_tx(mcp4725, bus);
    calibration(1);

    _delay_ms(10000);

    mcp4725->byte_high = 0x00, mcp4725->byte_low = 0x00;
    mcp4725_tx(mcp4725, bus);
    calibration(0);

    _delay_ms(10000);
}