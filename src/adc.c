#include "main.h"

void adc_init(void)
{
    /* Set pin modes and init ADC. Reference voltage is AVCC (5V), 
     * ADC operating in 10-bit mode with pre-scalar at 128 (125KHz).
     * Interrupts enabled.
     */
    asm("ldi %0, %2 \n"
        "ldi %1, %3 \n"
        : "=r" (ADMUX), "=r" (ADCSRA) : "M" (0x40), "M" (0x8F)
    );
}