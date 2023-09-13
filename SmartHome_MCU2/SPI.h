/*
 * SPI.h
 *
 *  Created on: Aug 24, 2023
 *      Author: yasmeen
 */

#ifndef SPI_H_
#define SPI_H_

#include"STD_TYPES.h"


void SPI_MasterInit(void);
u8 SPI_u8MasterTrancieve(u8 Data);
void SPT_SlaveInit(void);
u8 SPI_u8SlaveTrancieve(u8 Data);

#endif /* SPI_H_ */
