/*
 * DisplayProject.c
 *
 * Created: 10/30/2021 1:49:42 PM
 * Author : Wobberr
 */ 

#define F_CPU 12000000UL
#include <util/delay.h>
#include "USART.h"
#include "I2C.h"
#include "SPI.h"
#include "Env.h"

int main(void)
{
	I2C_Init(10000UL,I2C_Prescaler_64);
	uint8_t addr=0x50;
	uint8_t i=0;
    while (1) 
    {	

		_delay_ms(100);
		
		I2C_Start();
		I2C_Write_Slave_Addr(TW_SLA_WRITE_ADDR(addr));
		I2C_Write(0x00);
		I2C_Write(0x00);
		I2C_Write((i++)%255);
		I2C_Stop();
		
		_delay_ms(5);
		//Set address to 0x0000
		I2C_Start();
		I2C_Write_Slave_Addr(TW_SLA_WRITE_ADDR(addr));
		I2C_Write(0x00);
		I2C_Write(0x00);
		
		//Start I2C comm again, with read address
		I2C_Start();
		I2C_Write_Slave_Addr(TW_SLA_READ_ADDR(addr));
		I2C_Read(false);
		I2C_Stop();



	
    }
}

