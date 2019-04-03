#pragma once
#include "tmc2160REGS.h"
typedef struct SPI_STATUS_t
{
	unsigned int reset_flag : 1;
	unsigned int driver_error : 1;
	unsigned int sg2 : 1;
	unsigned int standstill : 1;
	unsigned int : 4;
}SPI_STATUS;
extern SPI_STATUS tmc2160status;
void tmc2160_init(void);
int tmc2160_SPI_read(unsigned int addr);
int tmc2160_SPI_write(unsigned int addr, int val);