/*
 * I2C.h
 *
 * Created: 11/1/2021 11:42:59 AM
 *  Author: Wobberr
 */ 

#include "Env.h"
#include <util/twi.h>
#include <stdbool.h>

#ifndef I2C_H_
#define I2C_H_



void I2C_Init(void);
uint8_t I2C_Start(void);
void I2C_Stop(void);

uint8_t I2C_Write_Slave_Addr(uint8_t addr_op);
uint8_t I2C_Write(uint8_t data);

uint8_t I2C_Read(bool isAcknowledgeable);

#endif /* I2C_H_ */