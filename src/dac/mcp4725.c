#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "sensors/f1031v.h"

static uint16_t measurement;
static uint8_t byte_high;
static uint8_t byte_low;

uint8_t mcp4725_return_byte_high(void)
{
    return byte_high;
}

uint8_t mcp4725_return_byte_low(void) 
{
    return byte_low;
}

uint16_t return_measurement(void)
{
    return measurement;
}

void mcp4725_tx(void)
{
     /* Rescale value */
    measurement = sample_f1031v() * 24.9;
     /* Grab MSBs. */
    byte_high = measurement / 16;
     /* Grab LSBs. */
    byte_low = (measurement % 16) << 4;
 
    /* Start -> SLA+W -> CO -> MSBs -> LSBs = 5 bytes total. */
    i2c_tx_start();
    i2c_tx(MCP4725_SLAVE_ADDRESS);
    i2c_tx(0x40);
    i2c_tx(byte_high);
    i2c_tx(byte_low);

    /* Release SCK and SDA lines. */
    i2c_tx_stop();
}

