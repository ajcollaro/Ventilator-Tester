#ifndef __MCP4725_H__
#define __MCP4725_H__

#include "main.h"

/* Device Address:
   1100010 (0x62) or 1100011 (0x63)
   (depending on whether A0 wired to GND or VCC)
*/

#define MCP4725_SLAVE_ADDRESS 0x63<<1

void mcp4725_update(struct flowsensor *sensor, struct dac *mcp4725);
void mcp4725_tx(struct dac *mcp4725);
void mcp4725_bypass(struct dac *mcp4725);

#endif