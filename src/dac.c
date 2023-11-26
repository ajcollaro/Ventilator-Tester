#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
*/

#define MCP4725_SLAVE_ADDRESS 0x63<<1 /* Works in real life! */
#define MCP4725_SLAVE_ADDRESS_SIMULATION 0xC2 /* Works in Proteus simulation. */

void mcp4725_tx(struct dac *mcp4725, struct i2c *bus)
{
    /* Start -> SLA+W -> CO -> MSBs -> LSBs = 5 bytes total. */
    i2c_tx_start();

    bus->byte = MCP4725_SLAVE_ADDRESS_SIMULATION;
    i2c_tx(bus); /* Send SLA+W. */

    bus->byte = 0x40;
    i2c_tx(bus); /* Send CO. */

    bus->byte = mcp4725->byte_high;
    i2c_tx(bus);

    bus->byte = mcp4725->byte_low;
    i2c_tx(bus);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(struct flowsensor *sensor, struct dac *mcp4725, struct i2c *bus)
{
    /* Rescale value. */
    mcp4725->measurement = (uint16_t)sensor->flow * 24;

    /* Grab MSBs and LSBs. Pointers faster than shifting. */
    mcp4725->byte_high = (uint8_t *)mcp4725->measurement + 1;
    mcp4725->byte_low = (uint8_t *)mcp4725->measurement; /* LSBS. */

    /* Send. */
    mcp4725_tx(mcp4725, bus);
}
