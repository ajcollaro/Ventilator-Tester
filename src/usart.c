#include "main.h"

void usart_tx(struct usart *usart_ptr)
{
    UDR0 = usart_ptr->byte;

    /* Wait for Tx finish. */
    while(!(UCSR0A & (1 << UDRE0)));
}

void usart_init(struct usart *usart_ptr)
{
    /* Enable Tx and Rx, and Rx ISRs. */
    usart_ptr->prescale = (F_CPU/16/usart_ptr->baud)-1;
    UBRR0L = (uint8_t)(usart_ptr->prescale & 0xFF);
    UBRR0H = (uint8_t)(usart_ptr->prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 