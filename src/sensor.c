#include "main.h"

void sample_f1031v(sensor_t *sensor)
{
    const float slope = 36.463;
    const float intercept = -18.036;

    /* Get value from register and convert to flow. */
    sensor->flow = ((float)ADC / 1023) * 5;
    sensor->flow = slope * sensor->flow + intercept; 
}