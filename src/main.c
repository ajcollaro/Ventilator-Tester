#include "main.h"

int main(void)
{
    uint8_t cycle;

    /* Delay after power-on for LCD initialisation. */
    _delay_ms(1000);
    lcd_init();

    /* Bring up ADC. */
    adc_init();

    /* I2C bus for connection to DAC. */
    struct i2c bus, *bus_ptr = &bus;
    i2c_init();

    /* Serial connection, 9600 baud. */
    struct usart serial, *usart_ptr = &serial;
    usart_ptr->baud = 9600;
    usart_init(usart_ptr);

    /* Init flow sensor. */
    struct flowsensor f1031v, *sensor = &f1031v;

    /* Init DAC. */
    struct dac mcp4725, *dac_ptr = &mcp4725;

    /* Turn on cooling fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Send calibration signal (10 secs at 5V and 0V). */
    dac_ptr->byte_high = 0xFF, dac_ptr->byte_low = 0xFF;
    mcp4725_tx(dac_ptr, bus_ptr); /* Send high. */
    calibration(1);

    _delay_ms(1000);

    dac_ptr->byte_high = 0x00, dac_ptr->byte_low = 0x00;
    mcp4725_tx(dac_ptr, bus_ptr); /* Send low. */
    calibration(0);

    _delay_ms(1000);

    while(1) 
    {
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(sensor);
        mcp4725_update(sensor, dac_ptr, bus_ptr);

        /* Update USART and LCD at lower tick (else DAC performance is effected). */
        cycle++;
        switch(cycle)
        {
            case REPORT_WAITS:
                report_data(sensor, dac_ptr, usart_ptr, bus_ptr); /* USART and LCD refresh. */
                cycle = 0;
            break;
        }  

        _delay_ms(WAIT_TIME_MS);
    }
}