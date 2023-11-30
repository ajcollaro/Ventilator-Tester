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

    /* Send calibration signal. */
    calibrate(dac, i2c_ptr);

    while(1) 
    {
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(sensor);
        mcp4725_update(sensor, dac, i2c_ptr);

        /* Update LCD at lower tick (else DAC performance is effected). */
        cycle++;

        if (cycle == REPORT_WAITS)
        {
            report_data(sensor, dac, serial_ptr, i2c_ptr);
            cycle = 0;
        }  
    }

    return 0;
}