#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
*/

#define MCP4725_SLAVE_ADDRESS 0x63<<1 /* Works in real life! */
#define MCP4725_SLAVE_ADDRESS_SIMULATION 0xC2 /* Works in Proteus simulation. */

void mcp4725_tx(struct dac_t *mcp4725, struct i2c_t *i2c)
{
    /* Start -> SLA+W -> CO -> MSBs -> LSBs = 5 bytes total. */
    i2c_tx_start();

    i2c->byte = MCP4725_SLAVE_ADDRESS_SIMULATION;
    i2c_tx(i2c); /* Send SLA+W. */

    i2c->byte = 0x40;
    i2c_tx(i2c); /* Send CO. */

    i2c->byte = mcp4725->byte_high;
    i2c_tx(i2c);

    i2c->byte = mcp4725->byte_low;
    i2c_tx(i2c);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(struct sensor_t *sensor, struct dac_t *mcp4725, struct i2c_t *i2c)
{
    /* Rescale value. */
    mcp4725->measurement = sensor->flow * 24;

    mcp4725->byte_high = mcp4725->measurement / 16;
    mcp4725->byte_low = (mcp4725->measurement % 16) << 4;

    /* Send. */
    mcp4725_tx(mcp4725, i2c);
}
