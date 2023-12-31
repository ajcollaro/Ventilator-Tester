#include "main.h"

void usart_tx(usart_t *serial)
{
    UDR0 = serial->byte;

    /* Wait for Tx finish. */
    while(!(UCSR0A & (1 << UDRE0)));
}

void usart_init(usart_t *serial)
{
    /* Enable Tx and Rx, and Rx ISRs. */
    serial->prescale = (F_CPU / 16 / serial->baud) - 1;
    UBRR0L = (uint8_t)(serial->prescale & 0xFF);
    UBRR0H = (uint8_t)(serial->prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 