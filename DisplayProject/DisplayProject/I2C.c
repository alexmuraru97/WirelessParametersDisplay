/*
 * I2C.c
 *
 * Created: 11/1/2021 11:43:07 AM
 *  Author: Wobberr
 */ 

#include "I2C.h"

void I2C_Init(void){
	//TODO OUTPUT+PULLUP PC5+PC4
	DDRC&=~((1<<DDC4)|(1<<DDC5));
	PORTC|=(1<<PORTC4)|(1<<PORTC5);
	
	//Enable PULLUP configuration
	MCUCR&=~(1<<PUD);
}

uint8_t I2C_Start(void){
	
	//Sets the interrupt flag, enables I2C module, and then sends the start condition
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);	
	
	//Waits for Twint flag to be set;
	while (!(TWCR & (1<<TWINT)));
	if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
	{
		return TW_STATUS;
	}
	return 0;
}

void I2C_Stop(void){
	
	//Set interrupt flag, enable I2C module and sends the STOP condition
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}