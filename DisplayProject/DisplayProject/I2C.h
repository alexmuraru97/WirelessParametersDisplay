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

enum I2C_Prescaler{I2C_Prescaler_1=1,I2C_Prescaler_4=4,I2C_Prescaler_16=16,I2C_Prescaler_64=64};
	
#define TW_SLA_WRITE_ADDR(ADDR)		((ADDR << 1) | TW_WRITE)
#define TW_SLA_READ_ADDR(ADDR)		((ADDR << 1) | TW_READ)
#define TWBR_CALC_NO_PRSC(FRQ,SCL) ((FRQ/(2*SCL))-8)

void I2C_Init(unsigned long SCL,enum I2C_Prescaler prescaler);
uint8_t I2C_Start(void);
void I2C_Stop(void);

uint8_t I2C_Write_Slave_Addr(uint8_t addr_op);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_Read(uint8_t * return_data, bool is_acknowlegeable);

#endif /* I2C_H_ */