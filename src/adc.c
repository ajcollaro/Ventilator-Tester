#include "main.h"

void adc_init(void)
{
    /* Set pin modes and init ADC. Reference voltage is AVCC (5V), 
     * ADC operating in 10-bit mode with pre-scalar at 128 (125KHz).
     * Interrupts enabled.
     */
    ADMUX |= (1 << REFS0); /* AVCC, single ended input into AD0 pin. */
    ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2)|(1 << ADEN)|(1 << ADIE);
}