#include "avr.h"
#include "sensors/sensors.h"
#include <string.h>

#define BAUD_RATE 9600
#define WAIT_TIME_MS 20 /* Wait time in milliseconds. */
#define REPORT_WAITS 25 /* LCD and USART waits before refresh. */
#define DEBUG_OUTPUT 0 /* Output additional data via USART. Disable unless testing. */

void write_usart(uint8_t *ptr);
void report_data(struct flowsensor *sensor);
void calibration(uint8_t mode);

void report_debug(void);