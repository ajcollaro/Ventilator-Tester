#include "main.h"

#define CAL_VOLTS_0 "0V Calibration"
#define CAL_VOLTS_5 "5V Calibration"

enum MAGIC_NUMBERS {
    VOLTS_0 = 0x0000,
    VOLTS_5 = 0xFFFF,
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
    cal_t cal, *cal_settings = &cal;

    /* Send calibration signal. */
    memcpy(cal_settings->buffer, CAL_VOLTS_5, sizeof(CAL_VOLTS_5));
    cal_settings->level = VOLTS_5;
    calibrate(cal_settings->buffer, &i2c, &cal);

    memcpy(cal_settings->buffer, CAL_VOLTS_0, sizeof(CAL_VOLTS_0));
    cal_settings->level = VOLTS_0;
    calibrate(cal_settings->buffer, &i2c, &cal);

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