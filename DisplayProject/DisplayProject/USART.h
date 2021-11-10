/*
 * USART.h
 *
 * Created: 10/30/2021 2:21:49 PM
 *  Author: Wobberr
 */ 


#include "Env.h"
#include <stdbool.h>

#ifndef USART_H_
#define USART_H_

#define BAUD_RATE(BAUD) (F_CPU/16/BAUD - 1)
#define BAUD_FAST_RATE(BAUD) (F_CPU/8/BAUD - 1)

enum USART_Parity{USART_Parity_Disabled=0, USART_Parity_Even=1, USART_Parity_Odd=2};
enum USART_Stop_Bits{USART_Stop_Bits_1=1, USART_Stop_Bits_2=2};
enum USART_Error {USART_Error_Ok=0, USART_Error_Parity=1, USART_Error_Frame=2, USART_Error_Data_Overrun=3};
	
void USART_Init(unsigned long baudrate, bool isFast, enum USART_Parity parity, enum USART_Stop_Bits stop_bits);
void USART_Write(unsigned char data);
uint8_t USART_Read(unsigned char* read_data);
void USART_Write_Integer(int number);
void USART_Write_String(char* char_arr, uint8_t size);
void USART_Write_Hex(uint8_t hex_number);
void USART_Write_Hex_Data(void* data, unsigned int size_bytes);
void USART_Write_New_Line(void);


#endif /* USART_H_ */