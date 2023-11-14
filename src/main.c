#include "main.h"
#include "adc/adc.h"
#include "dac/mcp4725.h"
#include "i2c/i2c.h"
#include "sensors/f1031v.h"

static uint8_t cycle_count;

int main(void)
{
    /* 100ms delay after power-on for LCD initialisation. */
    _delay_ms(100);
    lcd_init();

    /* Turn on fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Bring up ADC and comms. */
    adc_init();

    /* I2C bus for connection to DAC. */
    struct i2c i2c, *bus = &i2c;
    i2c_init();

    /* Serial connection, 9600 baud. */
    struct usart usart, *serial = &usart;
    serial->baud = 9600;
    usart_init(serial);

    /* Init flow sensor. */
    struct flowsensor f1031v, *sensor = &f1031v;

    /* Init DAC. */
    struct dac mcp4725, *dac = &mcp4725;

    /* Send calibration signal (10 secs at 5V and 0V). */
    dac->byte_high = 0xFF, dac->byte_low = 0xFF;
    mcp4725_tx(dac); /* Send low. */
    calibration(1);

    _delay_ms(10000);

    dac->byte_low = 0x00, dac->byte_low = 0x00;
    mcp4725_tx(dac); /* Send low. */
    calibration(0);

    _delay_ms(10000);

    while(1) 
    {
        mcp4725_update(sensor, dac);
        cycle_count++;
        switch(cycle_count)
        {
            case REPORT_WAITS:
                report_data(sensor, dac, serial, bus); /* USART and LCD refresh. */
                cycle_count = 0;
            break;
        }  

        _delay_ms(WAIT_TIME_MS);
    }
}