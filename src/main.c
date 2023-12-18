#include "main.h"

#define CAL_5V " 5V Calibration"
#define CAL_0V " 0V Calibration"

enum MAGIC_NUMBERS {
    OUT_5V = 0xFFFF,
    OUT_0V = 0x0000,
    LCD_REFRESH_CYCLES = 255,
    NOISE_REDUCTION_MODE = 0x03
};

static uint8_t cycle;
static dac_t dac, *mcp4725 = &dac;
static i2c_t i2c, *bus = &bus;
static sensor_t sensor, *f1031v = &sensor;

ISR(ADC_vect)
{
    cycle++;

    /* Sample flow sensor and send updated data to DAC. */
    sample_f1031v(f1031v);
    mcp4725_update(f1031v, mcp4725, bus);

    (cycle == LCD_REFRESH_CYCLES) ? report_data(f1031v, mcp4725) : 0;
}

int main(void)
{
    asm("ldi %0, %2 \n\t"
        "ldi %1, %3 \n\t"
        : "=r" (DDRA), "=r" (PORTA) : "M" (0xFF), "M" (0x80)
    );
    
    adc_init();
    i2c_init();
    lcd_init();

    cal_t cal, *setting = &cal;

    /* Send calibration signal. */
    memcpy(setting->buffer, CAL_5V, sizeof(CAL_5V));
    setting->size = OUT_5V;
    calibrate(mcp4725, bus, setting);

    memcpy(setting->buffer, CAL_0V, sizeof(CAL_0V));
    setting->size = OUT_0V;
    calibrate(mcp4725, bus, setting);

    asm("sei \n\t");

    asm("ldi %0, %1 \n\t"
            : "=r" (SMCR) : "M" (NOISE_REDUCTION_MODE)
    );

    while(1) 
    {       
        asm("sleep \n\t");
    }
    
    asm("jmp 0 \n\t");
}