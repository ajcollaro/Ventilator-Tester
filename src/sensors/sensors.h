#ifndef __SENSORS_H__
#define __SENSORS_H__

struct flowsensor {
    float raw; /* ADC return. */
    float flow;
};

#endif