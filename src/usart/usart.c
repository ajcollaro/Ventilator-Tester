#include "usart.h"

void usart_tx(struct usart *usart)
{
    UDR0 = usart->byte;

    /* Wait for Tx finish. */
    while(!(UCSR0A & (1 << UDRE0)));
}

void usart_init(struct usart *usart)
{
    /* Enable Tx and Rx, and Rx ISRs. */
    usart->prescale = (F_CPU/16/usart->baud)-1;
    UBRR0L = (uint8_t)(usart->prescale & 0xFF);
    UBRR0H = (uint8_t)(usart->prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 