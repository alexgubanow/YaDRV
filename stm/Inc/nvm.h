#pragma once
#include "tmc2590defs.h"

typedef enum Params_enum 
{
	DRVCTRLp = tmc2590_DRVCTRL,
	validParams,
	CHOPCONFp = tmc2590_CHOPCONF,
	SMARTENp = tmc2590_SMARTEN,
	SGCSCONFp = tmc2590_SGCSCONF,
	DRVCONFp = tmc2590_DRVCONF,
}Params_enum;

extern uint16_t Params[];

void saveParams();
void loadParams(int writeDefault);
void loadDefaultParams();