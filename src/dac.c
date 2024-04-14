#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
   0xC2 works in Proteus sim.
*/

enum MAGIC_NUMBERS {
    OFFSET = 50 /* Avoid EPAP underflow. */
};

void mcp4725_tx(dac_t *dac, i2c_t *i2c)
{
    /* Start. */
    i2c_tx_start();

    /* Send only the two updated bytes of data. */
    uint8_t data[] = { dac->byte_hi, dac->byte_lo };
    memcpy(&i2c->bytes[2], data, sizeof(data));
    
    i2c_tx(i2c);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(dac_t *dac, sensor_t *sensor, i2c_t *i2c)
{
    static const uint8_t offset = OFFSET;
    dac->value = sensor->flow + offset;

    mcp4725_tx(dac, i2c);
}