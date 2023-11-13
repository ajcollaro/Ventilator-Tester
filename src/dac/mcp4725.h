#include "main.h"
#include "sensors/sensors.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
*/

#define MCP4725_SLAVE_ADDRESS 0x63<<1

uint16_t return_measurement(void);
uint8_t mcp4725_return_byte_high(void);
uint8_t mcp4725_return_byte_low(void);

void mcp4725_update(struct flowsensor *sensor);
void mcp4725_tx(void);
void mcp4725_bypass(uint8_t high, uint8_t low);