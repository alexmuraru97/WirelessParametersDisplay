/*
 * I2C.c
 *
 * Created: 11/1/2021 11:43:07 AM
 *  Author: Wobberr
 */ 

#include "I2C.h"

void I2C_Init(void){
	//OUTPUT+PULLUP PC5+PC4 (SDA/SCL)
	DDRC&=~((1<<DDC4)|(1<<DDC5));
	PORTC|=(1<<PORTC4)|(1<<PORTC5);
	
	//Enable PULLUP configuration
	MCUCR&=~(1<<PUD);
	

	//TODO set frq
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

uint8_t I2C_Write_Slave_Addr(uint8_t addr_op)
{
	TWDR = addr_op<<1;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
	{
		//Error code - slave did not receive salve addr
		return TW_STATUS;
	}

	return 0;
}

uint8_t I2C_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		//If data was not acknowledged
		return TW_STATUS;
	}
	return 0;
}
	
	
uint8_t I2C_Read(bool isAcknowledgeable)
{
	//if isAcknowledgeable -> respond to slave module with an ACK signal
	if (isAcknowledgeable)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_ACK)
		{
			return TW_STATUS;
		}
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_NACK)
		{
			return TW_STATUS;
		}
	}
	uint8_t received_data = TWDR;
	return received_data;
}