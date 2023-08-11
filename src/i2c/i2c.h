#include "main.h"

void i2c_status_blank(void);
void i2c_status_increment(void);
uint8_t i2c_status_return(void);

void i2c_tx(uint8_t byte);
void i2c_tx_stop(void);
void i2c_tx_start(void);

void i2c_init(void);