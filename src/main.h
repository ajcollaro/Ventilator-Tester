#include "avr.h"
#include <string.h>

#define BAUD_RATE 9600
#define WAIT_TIME_MS 20 /* Wait time in milliseconds. */
#define REPORT_WAITS 25 /* LCD and USART waits before refresh. */
#define DEBUG_OUTPUT 1 /* Output additional data via USART (debug.c). */

void fan_init();

void write_usart(uint8_t *ptr);

void report_data(void);
void report_debug(void);

void process_input(uint8_t byte);

void eeprom_write(uint16_t address, uint8_t byte);
uint8_t eeprom_read(uint16_t address);