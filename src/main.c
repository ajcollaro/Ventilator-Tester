#include "main.h"

#define LCD_REFRESH_CYCLES 255

ISR(ADC_vect)
{
    /* Re-enter loop to increment cycle counter. */
}

int main(void)
{
    /* Bring up hardware. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    adc_init();
    lcd_init();

    dac_t dac;
    i2c_t i2c;
    i2c_init(&i2c);
    sensor_t sensor;
    cal_t cal;

    /* Send calibration signal. */
    calibration_setup(&dac, &i2c, &cal);

    /* Enable interrupts. */
    asm("sei \n\t");

    /* ADC noise reduction mode. */
    SMCR |= (1 << SE);

    /* Cycle counter. */
    uint8_t cycle = 0;

    while(1) 
    {       
        cycle++;
        
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(&sensor);
        mcp4725_update(&dac, &sensor, &i2c);

        /* Update display at slower tic. */
        (cycle == LCD_REFRESH_CYCLES) ? report_data(&sensor) : 0;

        /* Sleep and begin conversion. */
        asm("sleep \n\t");
    }
}