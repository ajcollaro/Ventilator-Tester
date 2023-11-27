#include "main.h"

void sample_f1031v(struct sensor_t *f1031v)
{
    /* Initiate conversion. */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion. */
    while((ADCSRA & (1 << ADSC)));

    /* Get value from register and convert to flow. */
    f1031v->flow = ADC / (1023 / 5);
    f1031v->flow = 150 * (f1031v->flow - 0.5) / (4.5 - 0.5);
}