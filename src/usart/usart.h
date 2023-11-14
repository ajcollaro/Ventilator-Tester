#ifndef __USART_H__
#define __USART_H__

#include "main.h"

struct usart {
    uint8_t byte;
    uint16_t baud;
    uint16_t prescale;
};

void usart_tx(struct usart *usart);
void usart_init(struct usart *usart);

#endif