#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
   0xC2 works in Proteus sim.
*/

/* Avoid EPAP underflow. */
#define OFFSET 20

void mcp4725_tx(dac_t *dac, i2c_t *i2c)
{
    /* Start. */
    i2c_tx_start();

    /* Send two bytes of sensor data. */
    uint8_t data[] = { dac->byte_big, dac->byte_little };
    memcpy(&i2c->data_bytes, data, sizeof(data));
    
    i2c_tx(i2c);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(dac_t *dac, sensor_t *sensor, i2c_t *i2c)
{
    dac->value = sensor->flow + OFFSET;
    mcp4725_tx(dac, i2c);
}