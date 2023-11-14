#include "main.h"
#include "dac/mcp4725.h"

void mcp4725_tx(struct dac *mcp4725)
{
    /* Start -> SLA+W -> CO -> MSBs -> LSBs = 5 bytes total. */
    i2c_tx_start();
    i2c_tx(MCP4725_SLAVE_ADDRESS);
    i2c_tx(0x40);
    i2c_tx(mcp4725->byte_high);
    i2c_tx(mcp4725->byte_low);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

void mcp4725_update(struct flowsensor *sensor, struct dac *mcp4725)
{
    /* Sample sensor and rescale value. */
    mcp4725->measurement = sensor->flow * 24;

     /* Grab MSBs. */
    mcp4725->byte_high = mcp4725->measurement / 16;
    
     /* Grab LSBs. */
    mcp4725->byte_low = (mcp4725->measurement % 16) << 4;

    /* Send. */
    mcp4725_tx(mcp4725);
}
