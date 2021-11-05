/*
 * I2C.h
 *
 * Created: 11/1/2021 11:42:59 AM
 *  Author: Wobberr
 */ 

#include <avr/io.h>
#include <util/twi.h>

#ifndef I2C_H_
#define I2C_H_


void I2C_Init(void);
uint8_t I2C_Start(void);
void I2C_Stop(void);

#endif /* I2C_H_ */