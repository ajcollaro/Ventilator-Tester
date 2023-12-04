#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
   0xC2 works in Proteus sim.
*/

void mcp4725_tx(struct dac *mcp4725, struct i2c *bus)
{
    /* Start -> SLA+W -> CO -> MSBs -> LSBs = 5 bytes total. */
    i2c_tx_start();

    bus->byte = 0x63 << 1;
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

void mcp4725_update(struct sensor *f1031v, struct dac *mcp4725, struct i2c *bus)
{
    /* Scale value so to output a maximum of ~4.8V,
     * and a minimum of 0.25V to avoid integer underflow during EPAP.
     */
    static const uint8_t offset = 90;
    mcp4725->value = (f1031v->flow + offset) * 3;

    /* Split high and low bytes. */
    mcp4725->byte_high = (uint8_t)(mcp4725->value >> 4);
    mcp4725->byte_low = (uint8_t)(mcp4725->value & 0xFF);

    /* Send. */
    mcp4725_tx(mcp4725, bus);
}
