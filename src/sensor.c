#include "main.h"

#define F1031V_M 36.463 
#define F1031V_INTERCEPT -18.036
#define F1031V_OFFSET 90

void sample_f1031v(struct sensor *f1031v)
{
    /* Initiate conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion. */
    while((ADCSRA & (1 << ADSC)));

    /* Get value from register and convert to flow. */
    f1031v->flow = ((float)ADC * 5) / 1023;
    f1031v->flow = F1031V_M*f1031v->flow+F1031V_INTERCEPT; 

    /* Avoid integer underflow during EPAP. */
    f1031v->processed = f1031v->flow + F1031V_OFFSET;
}