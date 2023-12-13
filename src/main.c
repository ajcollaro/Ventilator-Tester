#include "main.h"

#define CAL_5V " 5V Calibration"
#define CAL_0V " 0V Calibration"

int main(void)
{
    static uint16_t cycle;

    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    adc_init();
    i2c_init();
    lcd_init();

    dac_t dac, *mcp4725 = &dac;
    usart_t usart, *serial = &usart;
    i2c_t i2c, *bus = &i2c;
    sensor_t sensor, *f1031v = &sensor;
    cal_t cal, *setting = &cal;

    /* Open serial connection at 9600 baud. */
    serial->baud = 9600;
    usart_init(serial);

    /* Send calibration signal. */
    memcpy(setting->buffer, CAL_5V, sizeof(CAL_5V));
    setting->size = 0xFFFF;
    calibrate(mcp4725, bus, setting);

    memcpy(setting->buffer, CAL_0V, sizeof(CAL_0V));
    setting->size = 0x0000;
    calibrate(mcp4725, bus, setting);

    while(1) 
    {
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(f1031v);
        mcp4725_update(f1031v, mcp4725, bus);

        /* Update LCD at lower tick (else worse aliasing of analog signal). */
        cycle++;
        
        if (cycle == 5000)
        {
            report_data(f1031v, mcp4725, serial);
            cycle = 0;
        }
    }

    return 0;
}