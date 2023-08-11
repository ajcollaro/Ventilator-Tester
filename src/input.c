#include "main.h"
#include "usart/usart.h"

void process_input(uint8_t byte)
{
    /* Check input (0-255). */
    switch(byte)
    {
        case 0:
            usart_disable();
            break;
        case 1:
            usart_init(BAUD_RATE);
            break;
    }
}