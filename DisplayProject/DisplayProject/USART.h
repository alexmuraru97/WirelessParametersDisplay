/*
 * USART.h
 *
 * Created: 10/30/2021 2:21:49 PM
 *  Author: Wobberr
 */ 


#include "Env.h"

#ifndef USART_H_
#define USART_H_


#define BAUD_RATE(BAUD) (F_CPU/16/BAUD - 1)


void USART_Init(unsigned int baudrate);
void USART_Write(unsigned char data);
unsigned char USART_Read(void);

void USART_Write_Integer(int number);
void USART_Write_String(char* char_arr, uint8_t size);
void USART_Write_Hex(uint16_t hex_number);

#endif /* USART_H_ */