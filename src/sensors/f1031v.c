#include "f1031v.h"

static float F1031V; /* Set as volatile if ISR to update this. */ 

ISR(ADC_vect) /* If using ISRs. */
{
    /* Interrupt when ADC conversion is complete. */
    F1031V = ADC;

    /* Start conversion again. */
    ADCSRA |= (1 << ADSC);
}

uint16_t sample_f1031v(void)
{
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion. */
    while((ADCSRA & (1 << ADSC)));

    /* Grab value from register. */
    F1031V = ADC;

    /* Convert ADC output to a voltage and solve for y. */
    float flow = (F1031V * 5) / 1024;
    flow = (F1031V_M*flow+F1031V_INTERCEPT); 

    return flow;
}