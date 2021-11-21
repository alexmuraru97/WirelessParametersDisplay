/*
 * USART.c
 *
 * Created: 10/30/2021 2:21:59 PM
 *  Author: Wobberr
 */ 
#include "USART.h"

void USART_Init(unsigned long baudrate, bool isFast, enum USART_Parity parity, enum USART_Stop_Bits stop_bits)
{
	//Set USART registers to initial data sheet values
	UCSR0A=0x20;
	UCSR0B=0x00;
	UCSR0C=0x06;
	
	switch(stop_bits){
		case USART_Stop_Bits_1:
			//1 Stop Bit-> USBS0 = 0
			UCSR0C &= ~(1<<USBS0);
		break;
		
		case USART_Stop_Bits_2:
			//2 Stop Bits-> USBS0 = 1
			UCSR0C |= (1<<USBS0);
		break;
		
		default:
			//default case->  1 stop bit
			UCSR0C &= ~(1<<USBS0);
		break;
	}
	
	switch(parity){
		case USART_Parity_Disabled:
			//UPM01 = 0 && UPM00 = 0
			UCSR0C &= ~((1<<UPM01)|(1<<UPM01));
		break;
		
		case USART_Parity_Even:
			//UPM01 = 1 && UPM00 = 0
			UCSR0C &= ~(1<<UPM00);
			UCSR0C |= (1<<UPM01);
		break;
		
		case USART_Parity_Odd:
			//UPM01 = 1 && UPM00 = 1
			UCSR0C |= (1<<UPM00);
			UCSR0C |= (1<<UPM01);
		break;
		
		default:
			//default case -> no parity
			UCSR0C &= ~((1<<UPM01)|(1<<UPM01));
		break;
	}
	
	if(isFast){
		UBRR0H = (unsigned char)(BAUD_FAST_RATE(baudrate) >> 8);
		UBRR0L = (unsigned char)(BAUD_FAST_RATE(baudrate) & 0xFF);	
		UCSR0A|= (1<<U2X0);
	}else{
		UBRR0H = (unsigned char)(BAUD_RATE(baudrate) >> 8);
		UBRR0L = (unsigned char)(BAUD_RATE(baudrate) & 0xFF);
		UCSR0A &= ~(1<<U2X0);
	}

	UCSR0B = (1 << RXEN0) | (1 << TXEN0); 
	DDRD |= (1 << DDD1);
	DDRD &= ~(1 << DDD0);
	
	//Enable interrupt for received data
	UCSR0B |= (1<<RXCIE0);
}

void USART_Write(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0))){;}
	UDR0=data;	
}

uint8_t USART_Read(unsigned char* read_data)
{
	
	unsigned char return_data=0;
	while(!(UCSR0A&(1<<RXC0))){;}
	
	//if parity flag is set, check for error
	if((UCSR0C&(1<<UPM01))&&(UCSR0A&(1<<UPE0))){
		return USART_Error_Parity;
	}
	
	//check for frame error
	if(UCSR0A&(1<<FE0)){
		return USART_Error_Frame;
	}
	
	//check for data overrun error
	if(UCSR0A&(1<<DOR0)){
		return USART_Error_Data_Overrun;
	}
	
	return_data=UDR0;
	*read_data=return_data;
	return USART_Error_Ok;
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


void USART_Write_Hex(uint8_t hex_number)
{
	int index=0;
	bool is_initial=true;
	char aux[4];
	USART_Write('0');
	USART_Write('x');
	while((hex_number!=0)||(is_initial)){
		if(is_initial)
		{
			is_initial=false;
		}
		uint8_t nibble=0;
		if((hex_number&0x0F)<=9){
			nibble=(hex_number&0x0F)+'0';
		}else{
			nibble=(hex_number&0x0F)+'A'-10;
		}
		aux[index]=nibble;
		hex_number>>=4;
		index++;
		if((hex_number&0x0F)<=9){
			nibble=(hex_number&0x0F)+'0';
		}else{
			nibble=(hex_number&0x0F)+'A'-10;
		}
		hex_number>>=4;
		aux[index]=nibble;
		index++;
		

		
	}
	while(index>0){
		USART_Write(aux[index-1]);
		index--;
	}
}

void USART_Write_String(char* char_arr, uint8_t size)
{
	for(uint8_t i=0;i<size;++i){
		USART_Write(char_arr[i]);
	}
}

void USART_Write_New_Line(void){
	USART_Write('\n');
}

void USART_Write_Hex_Data(void* data, unsigned int size_bytes)
{
	char *p=(char *) data;
	for(unsigned int i=0;i<size_bytes;i++){
		USART_Write_Hex((unsigned char)(*(p+i)));
		USART_Write(' ');
	}
}