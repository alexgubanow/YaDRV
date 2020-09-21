#pragma once
#include "..\stm\Inc\tmc2590defs.h"

public ref class tmc2590Converter
{
public:
	static void getSGCSCONFbits(int regValue, int% CS, int% SGT, int% SFILT)
	{
		SGCSCONF_t tmp{};
		tmp.w = regValue;
		CS = tmp.b.CS;
		SGT = tmp.b.SGT;
		SFILT = tmp.b.SFILT;
	}
	static int getSGCSCONF(int CS, int SGT, int SFILT)
	{
		SGCSCONF_t tmp{};
		tmp.b.CS = CS;
		tmp.b.SGT = SGT;
		tmp.b.SFILT = SFILT;
		return tmp.w;
	}
};

