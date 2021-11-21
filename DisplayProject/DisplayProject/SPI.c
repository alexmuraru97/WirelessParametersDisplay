/*
 * SPI.c
 *
 * Created: 11/4/2021 10:32:15 PM
 *  Author: Wobberr
 */ 

#include "SPI.h"

uint8_t SPI_Init(enum SPI_Transmission_Mode transmissionMode, bool isSPI2X, enum SPI_Prescaler prescaler, enum SPI_Data_Mode dataMode, bool isLSBFirst, bool isMaster)
{
	SPCR=0x00;
	SPSR=0x00;
	
	/* Set MOSI and SCK output, all others input */  //PB2=SS PB3=MOSI PB4=MISO PB5=SCK
	switch(transmissionMode)
	{
		case SPI_MODE_TX:
			//Set SCK and MOSI
			DDRB|= (1<< DDB5) | (1<<DDB3);
		break;
		
		case SPI_MODE_RX:
			//Set SCK and MISO
			DDRB|= (1<< DDB5) | (1<<DDB4);
		break;
		
		case SPI_MODE_TX_RX:
			//Set SCK, MOSI and MISO
			DDRB|= (1<< DDB5) | (1<<DDB4) | (1<<DDB3);
		break;
		
		default:
			return SPI_Error_Init;
		break;
	}
	if(isMaster)
	{
		SPCR |= (1<<MSTR);
		DDRB |= (1<<DDB2);
	}
	else
	{
		//If not a master node, then SS pin shall be pulled-up High, and set as Input
		DDRB &= ~(1<<DDB2);
		PORTB |= (1<<PORTB2);	
	}
	
	//Set SPI2X if double speed SPI transmission SCK
	if(isSPI2X)
	{
		SPSR|= (1<<SPI2X);
	}
	
	//Set transmission SCK speed according to prescaler
	SPCR|= ((prescaler&0x02)<<SPR1) | ((prescaler&0x01)<<SPR0);	
	
	
	//Set Data Mode
	SPCR |= ((dataMode&0x02)<<CPOL) | ((dataMode&0x01)<<CPHA);
	
	//Set data receiving bits order
	if(isLSBFirst)
	{
		SPCR|= (1<<DORD);
	}
	
	return SPI_Error_Ok;
}

void SPI_Write(uint8_t  cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_Read(void) {
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void SPI_WriteArray(uint8_t* send_data, uint8_t size)
{
	while(size--)
	{
		SPI_Write(*send_data++);
	}
}

void SPI_ReadArray(uint8_t* receive_data, uint8_t size)
{
	while(size--)
	{
		*receive_data++ = SPI_Read();
	}
}