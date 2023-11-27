#include "main.h"

int main(void)
{
    uint8_t cycle;

    /* Turn on cooling fan. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    /* Bring up features. */
    adc_init();
    i2c_init();
    lcd_init();

    struct i2c_t i2c, *i2c_ptr = &i2c;
    struct usart_t serial, *serial_ptr = &serial;
    struct dac_t mcp4725, *dac = &mcp4725;
    struct sensor_t f1031v, *sensor = &f1031v;

    /* Open serial connection at 9600 baud. */
    serial_ptr->baud = 9600;
    usart_init(serial_ptr);

    /* Send calibration signal (10 secs at 5V and 0V). */
    dac->byte_high = 0xFF, dac->byte_low = 0xFF;
    mcp4725_tx(dac, i2c_ptr); /* Send high. */
    calibration(1);

    _delay_ms(10000);

    dac->byte_high = 0x00, dac->byte_low = 0x00;
    mcp4725_tx(dac, i2c_ptr); /* Send low. */
    calibration(0);

    _delay_ms(10000);

    while(1) 
    {
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(sensor);
        mcp4725_update(sensor, dac, i2c_ptr);

        /* Update LCD at lower tick (else DAC performance is effected). */
        cycle++;
        switch(cycle)
        {
            case REPORT_WAITS:
                report_data(sensor, dac, serial_ptr, i2c_ptr);
                cycle = 0;
            break;
        }  
    }
}