#include "main.h"

#define F1031V_M 36.463 
#define F1031V_INTERCEPT -18.036
#define F1031V_OFFSET 50

void sample_f1031v(struct flowsensor *f1031v)
{
    /* Initiate conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion. */
    while((ADCSRA & (1 << ADSC)));

    /* Grab value from register. */
    f1031v->raw = ADC;

    /* Convert ADC output to a voltage and solve for y. */
    f1031v->flow = (f1031v->raw * 5) / 1024;
    f1031v->flow = (F1031V_M*f1031v->flow+F1031V_INTERCEPT+F1031V_OFFSET); 
}