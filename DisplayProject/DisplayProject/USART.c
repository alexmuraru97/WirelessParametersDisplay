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

void USART_Write_Integer(int number)
{
	int index=0;
	char aux[11];
	if(number<0){
		USART_Write('-');
		number*=-1;
	}
	while(number!=0){
		aux[index]=number%10+'0';
		index++;
		number=number/10;
	}

	while(index>0){
		USART_Write(aux[index-1]);
		index--;
	}
}


void USART_Write_Hex(uint16_t hex_number)
{
	int index=0;
	char aux[4];
	USART_Write('0');
	USART_Write('x');
	while(hex_number!=0){
		if((hex_number&0x0F)<=9){
			aux[index]=(hex_number&0x0F)+'0';
		}else{
			aux[index]=(hex_number&0x0F)+'A'-10;
		}
		hex_number>>=4;
		index++;
	}
	while(index>0){
		USART_Write(aux[index-1]);
		index--;
	}
}

void USART_Write_String(char* char_arr, uint8_t size)
{
	for(uint8_t i=size;i>=0;--i){
		USART_Write(char_arr[i]);
	}
}