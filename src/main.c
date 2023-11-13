#include "main.h"
#include "adc/adc.h"
#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "lcd/lcd1602.h"
#include "sensors/sensors.h"
#include "usart/usart.h"

static uint8_t cycle_count;

int main(void)
{
    /* Init flow sensor. */
    struct flowsensor f1031v;
    struct flowsensor *sensor = &f1031v;

    /* 100ms delay after power-on for LCD initialisation. */
    _delay_ms(100);
    lcd_init();

    /* Turn on fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Bring up USART and ADC. */
    adc_init();
    i2c_init();
    usart_init(BAUD_RATE);

    /* Send calibration signal (10 secs at 5V and 0V). */
    mcp4725_bypass(0xFF, 0xFF); /* Send low. */
    calibration(1);

    _delay_ms(10000);

    mcp4725_bypass(0x00, 0x00); /* Send low. */
    calibration(0);

    _delay_ms(10000);

    while(1) 
    {
        mcp4725_update(sensor);
        cycle_count++;
        switch(cycle_count)
        {
            case REPORT_WAITS:
            report_data(sensor); /* USART and LCD refresh. */
            cycle_count = 0;
            break;
        }  

        _delay_ms(WAIT_TIME_MS);
    }
}