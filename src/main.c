#include "main.h"

#define CAL_5V " 5V Calibration"
#define CAL_0V " 0V Calibration"

enum MAGIC_NUMBERS {
    OUT_5V = 0xFFFF,
    OUT_0V = 0x0000,
    LCD_REFRESH_CYCLES = 255,
    NOISE_REDUCTION_MODE = 0x03
};

static volatile uint8_t cycle;

ISR(ADC_vect)
{
    cycle++;
}

int main(void)
{
    /* Bring up hardware. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);
    
    adc_init();
    i2c_init();
    lcd_init();

    dac_t dac, *mcp4725 = &dac;
    i2c_t i2c, *bus = &bus;
    sensor_t sensor, *f1031v = &sensor;
    cal_t cal, *setting = &cal;

    /* Send calibration signal. */
    memcpy(setting->buffer, CAL_5V, sizeof(CAL_5V));
    setting->size = OUT_5V;
    calibrate(mcp4725, bus, setting);

    memcpy(setting->buffer, CAL_0V, sizeof(CAL_0V));
    setting->size = OUT_0V;
    calibrate(mcp4725, bus, setting);

    /* Enable interrupts. */
    sei();

    /* ADC noise reduction mode. */
    SMCR |= (1 << SE);

    while(1) 
    {       
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(f1031v);
        mcp4725_update(f1031v, mcp4725, bus);

        /* Update display at slower tic. */
        (cycle == LCD_REFRESH_CYCLES) ? report_data(f1031v, mcp4725) : 0;

        /* Sleep and begin conversion. */
        asm("sleep \n\t");
    }
}