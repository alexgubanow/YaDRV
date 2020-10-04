#pragma once
#include "tmc2590defs.h"

struct Params_t
{
	unsigned short isParamsValid;
	DRVCTRL_SDOFF_0_t DRVCTRL_r;
	CHOPCONF_t CHOPCONF_r;
	SMARTEN_t SMARTEN_r;
	SGCSCONF_t SGCSCONF_r;
	DRVCONF_t DRVCONF_r;
}Params;

void saveParams();
void loadParams(int writeDefault);
void loadDefaultParams();