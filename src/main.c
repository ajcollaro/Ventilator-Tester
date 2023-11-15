#include "main.h"

static uint8_t cycle_count;

int main(void)
{
    /* Delay after power-on for LCD initialisation. */
    _delay_ms(1000);
    lcd_init();

    /* Turn on fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Bring up ADC and comms. */
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

    /* Send calibration signal (10 secs at 5V and 0V). */
    dac_ptr->byte_high = 0xFF, dac_ptr->byte_low = 0xFF;
    mcp4725_tx(dac_ptr, bus_ptr); /* Send low. */
    calibration(1);

    _delay_ms(10000);

    dac_ptr->byte_low = 0x00, dac_ptr->byte_low = 0x00;
    mcp4725_tx(dac_ptr, bus_ptr); /* Send low. */
    calibration(0);

    _delay_ms(10000);

    while(1) 
    {
        mcp4725_update(sensor, dac_ptr, bus_ptr);
        cycle_count++;
        switch(cycle_count)
        {
            case REPORT_WAITS:
                report_data(sensor, dac_ptr, usart_ptr, bus_ptr); /* USART and LCD refresh. */
                cycle_count = 0;
            break;
        }  

        _delay_ms(WAIT_TIME_MS);
    }
}