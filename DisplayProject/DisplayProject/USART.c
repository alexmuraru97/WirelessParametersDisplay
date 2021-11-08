/*
 * USART.c
 *
 * Created: 10/30/2021 2:21:59 PM
 *  Author: Wobberr
 */ 
#include "USART.h"

void USART_Init(unsigned int baudrate)
{
	UBRR0H = (unsigned char)(BAUD_RATE(baudrate) >> 8);
	UBRR0L = (unsigned char)(BAUD_RATE(baudrate) & 0xFF);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); 
	DDRD |= (1 << DDD1);
	DDRD &= ~(1 << DDD0);
}

void USART_Write(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0))){;}
	UDR0=data;	
}

unsigned char USART_Read(void)
{
	while(!(UCSR0A&(1<<RXC0))){;}
	return UDR0;	
}