#ifndef __DAC_H__
#define __DAC_H__

#include "main.h"

struct dac {
    uint8_t byte_high;
    uint8_t byte_low;
    uint16_t measurement;
};

#endif