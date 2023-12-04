#include "main.h"

int main(void)
{
    static uint8_t cycle;

    /* Turn on cooling fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Bring up features. */
    adc_init();
    i2c_init();
    lcd_init();

    struct i2c i2c, *bus = &i2c;
    struct usart usart, *serial = &usart;
    struct dac dac, *mcp4725 = &dac;
    struct sensor sensor, *f1031v = &sensor;

    /* Open serial connection at 9600 baud. */
    serial->baud = 9600;
    usart_init(serial);

    /* Send calibration signal. */
    calibration(mcp4725, bus);

    while(1) 
    {
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(f1031v);
        mcp4725_update(f1031v, mcp4725, bus);

        /* Update LCD at lower tick (else DAC performance is effected). */
        cycle++;

        if (cycle == 255)
            report_data(f1031v, mcp4725, serial);
    }

    return 0;
}