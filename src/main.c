#include "main.h"

#define CAL_5V " 5V Calibration"
#define CAL_0V " 0V Calibration"

enum MAGIC_NUMBERS {
    OUT_5V = 0xFFFF,
    OUT_0V = 0x0000,
    LCD_REFRESH_CYCLES = 255
};

ISR(ADC_vect)
{
    /* Re-enter loop to increment cycle counter.
       Avoid static variable held in SRAM. */
}

int main(void)
{
    /* Bring up hardware. */
    DDRA = 0xFF;
    PORTA |= (1 << PORTA7);

    adc_init();
    lcd_init();
    i2c_init();

    dac_t dac;
    i2c_t i2c;
    sensor_t sensor;
    cal_t cal, *settings = &cal;

    /* Send calibration signal. */
    memcpy(settings->buffer, CAL_5V, sizeof(CAL_5V));
    settings->size = OUT_5V;
    calibrate(settings->buffer, &i2c, &cal);

    memcpy(settings->buffer, CAL_0V, sizeof(CAL_0V));
    settings->size = OUT_0V;
    calibrate(settings->buffer, &i2c, &cal);

    /* Enable interrupts. */
    sei();

    /* ADC noise reduction mode. */
    SMCR |= (1 << SE);

    /* Cycle counter. */
    uint8_t cycle = 0;

    while(1) 
    {       
        cycle++;
        
        /* Sample flow sensor and send updated data to DAC. */
        sample_f1031v(&sensor);
        mcp4725_update(&sensor, &dac, &i2c);

        /* Update display at slower tic. */
        (cycle == LCD_REFRESH_CYCLES) ? report_data(&sensor, &dac) : 0;

        /* Sleep and begin conversion. */
        asm("sleep \n\t");
    }
}