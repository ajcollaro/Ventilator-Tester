#include "main.h"
#include "adc/adc.h"
#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "lcd/lcd1602.h"
#include "usart/usart.h"

static uint8_t cycle_count;

int main(void)
{
    /* Generous 100ms delay for LCD initialisation. */
    _delay_ms(50);
    /* Turn display on. */
    lcd_init();

    /* Load fan defaults. */
    fan_init();

    /* Bring up USART and ADC. */
    adc_init();
    i2c_init();
    usart_init(BAUD_RATE);

    /* Delay for inits (probably not needed). */
    _delay_ms(1000);

    sei(); /* Enable global interrupts. */

    while(1) 
    {
        /* Update analog voltage out. */
        mcp4725_tx();
        cycle_count++;

        switch(cycle_count)
        {
            case REPORT_WAITS:
                report_data(); /* USART and LCD refresh. */
                cycle_count = 0;
                break;
        }
        
        _delay_ms(WAIT_TIME_MS);
    }
}