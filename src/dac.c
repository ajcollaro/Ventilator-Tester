#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
   0xC2 works in Proteus sim.
*/

enum MCP4725_MAGIC_NUMBERS {
    DEVICE_ADDRESS = 0x63<<1,
    DEVICE_ADDRESS_SIM = 0xC2,
    CO = 0x40,
    OFFSET = 50 /* Avoid EPAP underflow. */
};

void mcp4725_tx(dac_t *mcp4725, i2c_t *bus)
{
    /* Start. */
    i2c_tx_start();

    /* SLA+W -> CO -> MSBs -> LSBs = 4 bytes total. */
    uint8_t cmds[4] = {DEVICE_ADDRESS, CO, mcp4725->byte_hi, mcp4725->byte_lo};
    memcpy(bus->bytes, cmds, sizeof(cmds));
    
    i2c_tx(bus);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(sensor_t *f1031v, dac_t *mcp4725, i2c_t *bus)
{
    static const uint8_t offset = OFFSET;
    mcp4725->value = f1031v->flow + offset;

    mcp4725_tx(mcp4725, bus);
}