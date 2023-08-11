/* USART Driver. */

#include "usart.h"

ISR(USART_RX_vect)
{
    /* ISR driven USART Rx. */
    process_input(UDR0);
}

void usart_tx(uint8_t byte)
{
    UDR0 = byte;

    /* Wait for Tx finish. */
    while(!(UCSR0A & (1 << UDRE0)));
}

void usart_disable()
{
    UCSR0B &= ~(1 << RXEN0)|(1 << TXEN0);
}

void usart_init(uint16_t baud_rate)
{
    /* Enable Tx and Rx. */
    uint16_t baud_prescale = (F_CPU/16/baud_rate)-1;
    UBRR0L = (uint8_t)(baud_prescale & 0xFF);
    UBRR0H = (uint8_t)(baud_prescale >> 8);

    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
} 