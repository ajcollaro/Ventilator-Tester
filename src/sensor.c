#include "main.h"

void sample_f1031v(struct sensor *f1031v)
{
    static const float slope = 36.463;
    static const float intercept = -18.036;

    /* Initiate conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion. */
    while((ADCSRA & (1 << ADSC)));

    /* Get value from register and convert to flow. */
    f1031v->flow = ((float)ADC * 5) / 1023;
    f1031v->flow = slope * f1031v->flow + intercept; 
}