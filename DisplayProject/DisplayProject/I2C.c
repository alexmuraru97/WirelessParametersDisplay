/*
 * I2C.c
 *
 * Created: 11/1/2021 11:43:07 AM
 *  Author: Wobberr
 */ 

#include "I2C.h"

void I2C_Init(unsigned long SCL,enum I2C_Prescaler prescaler){
	//OUTPUT+PULLUP PC5+PC4 (SDA/SCL)
	DDRC&=~((1<<DDC4)|(1<<DDC5));
	PORTC|=(1<<PORTC4)|(1<<PORTC5);
	
	//Enable PULLUP configuration
	MCUCR&=~(1<<PUD);
	
	switch(prescaler){
		case I2C_Prescaler_1:
			//Prescaler 1->TWPS1 =0, TWPS0=0
			TWSR&=~((1<<TWPS1)|(1<<TWPS0));
		break;
		case I2C_Prescaler_4:
			//Prescaler 1->TWPS1 =0, TWPS0=1
			TWSR&=~((1<<TWPS1)|(1<<TWPS0));
			TWSR|=(1<<TWPS0);
		break;
		case I2C_Prescaler_16:
			//Prescaler 1->TWPS1 =1, TWPS0=0
			TWSR&=~((1<<TWPS1)|(1<<TWPS0));	
			TWSR|=(1<<TWPS1);	
		break;
		case I2C_Prescaler_64:
			//Prescaler 1->TWPS1 =1, TWPS0=1
			TWSR&=~((1<<TWPS1)|(1<<TWPS0));	
			TWSR|=(1<<TWPS1)|(1<<TWPS0);
		break;
		default:
			//default case-> prescaler 1
			TWSR&=~((1<<TWPS1)|(1<<TWPS0));
		break;
	}
	
	//Set Baud Rate
	TWBR=TWBR_CALC_NO_PRSC(F_CPU,SCL);
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
	TWDR = addr_op;
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
		return TW_STATUS;
	}
	return 0;
}
	
	
uint8_t I2C_Read(uint8_t * return_data, bool is_acknowlegeable)
{
	//if isAcknowledgeable -> respond to slave module with an ACK signal
	if (is_acknowlegeable)
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
	*return_data=TWDR;
	return 0;
}