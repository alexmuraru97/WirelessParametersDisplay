/*
 * DisplayProject.c
 *
 * Created: 10/30/2021 1:49:42 PM
 * Author : Wobberr
 */ 


#include "Env.h"
#include <util/delay.h>
#include "USART.h"
#include "I2C.h"
#include "SPI.h"


int main(void)
{
	I2C_Init();
	
    while (1) 
    {	
		_delay_ms(50);
		I2C_Start();
		_delay_ms(200);
		I2C_Stop();
    }
}

