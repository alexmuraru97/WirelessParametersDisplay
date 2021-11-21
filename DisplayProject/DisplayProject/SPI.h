/*
 * SPI.h
 *
 * Created: 11/4/2021 10:32:06 PM
 *  Author: Wobberr
 */ 

#include "Env.h"
#include <stdbool.h>

#ifndef SPI_H_
#define SPI_H_

enum SPI_Transmission_Mode {SPI_MODE_TX=0, SPI_MODE_RX=1, SPI_MODE_TX_RX=2};
enum SPI_Prescaler {SPI_Prescaler_4=0, SPI_Prescaler_16=1, SPI_Prescaler_64=2, SPI_Prescaler_128=3};
enum SPI_Data_Mode {SPI_Data_Mode_LSampRise_TSetFall=0, SPI_Data_Mode_LSetRise_TSampFall=1,	SPI_Data_Mode_LSampFall_TSetRise=2, SPI_Data_Mode_LSetFall_TSampRise=3 };
enum SPI_Error {SPI_Error_Ok=0, SPI_Error_Init=1};


uint8_t SPI_Init(enum SPI_Transmission_Mode transmissionMode, bool isSPI2X, enum SPI_Prescaler prescaler, enum SPI_Data_Mode dataMode, bool isLSBFirst, bool isMaster);
void SPI_Write(char cData);
char SPI_Read(void);


#endif /* SPI_H_ */