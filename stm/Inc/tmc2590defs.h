#pragma once

typedef struct
{
	unsigned short MSTEP : 10;
}tmc2590_rxBuff_RDSEL00_t;

typedef struct
{
	unsigned short SG : 10;
}tmc2590_rxBuff_RDSEL01_t;

typedef struct
{
	unsigned short SG_MSB : 10;
	unsigned short SE : 10;
}tmc2590_rxBuff_RDSEL10_t;

typedef struct
{
	unsigned char OT100 : 1;
	unsigned char OT120 : 1;
	unsigned char OT136 : 1;
	unsigned char OT150 : 1;
	unsigned char S2GA : 1;
	unsigned char S2VSA : 1;
	unsigned char S2GB : 1;
	unsigned char S2VSB : 1;
	unsigned char ENN_input : 1;
	unsigned char UV_7V : 1;
}tmc2590_rxBuff_RDSEL11_t;

typedef union
{
	struct
	{
		unsigned char SG : 1;
		unsigned char OT : 1;
		unsigned char OTPW : 1;
		unsigned char SHORTA : 1;
		unsigned char SHORTB : 1;
		unsigned char OLA : 1;
		unsigned char OLB : 1;
		unsigned char STST : 1;
		unsigned char : 2;
		unsigned short RDSELdata : 10;
	}b;
	unsigned int w;
}tmc2590_rxBuff_t;

#ifdef __cplusplus_cli
public enum class tmc2590regs_enum
{
#else
typedef enum tmc2590regs_enum 
{
#endif // __cplusplus_cli
	tmc2590_DRVCTRL = 0b000,
	tmc2590_CHOPCONF = 0b100,
	tmc2590_SMARTEN = 0b101,
	tmc2590_SGCSCONF = 0b110,
	tmc2590_DRVCONF = 0b111
}tmc2590regs_enum;

typedef union DRVCTRL_SDOFF_1_t {
	struct
	{
		/*Current B
		Magnitude of current flow through coil B. The range is
	0 to 248, if hysteresis or offset are used up to their full
	extent. The resulting value after applying hysteresis or
	offset must not exceed 255.*/
		unsigned char  CB;
		/*Polarity B
		Sign of current flow through coil B:
	0: Current flows from OB1 pins to OB2 pins.
	1: Current flows from OB2 pins to OB1 pins.*/
		unsigned char  PHB : 1;
		/*Current A
		Magnitude of current flow through coil A. The range is
	0 to 248, if hysteresis or offset are used up to their full
	extent. The resulting value after applying hysteresis or
	offset must not exceed 255.*/
		unsigned char  CA;
		/*Polarity A
		Sign of current flow through coil A:
	0: Current flows from OA1 pins to OA2 pins.
	1: Current flows from OA2 pins to OA1 pins.*/
		unsigned char  PHA : 1;
	}b;
	unsigned int w : 17;
}DRVCTRL_SDOFF_1_t;
typedef union DRVCTRL_SDOFF_0_t {
	struct
	{
		/*Microstep resolution for STEP/DIR mode
		Microsteps per fullstep:
		%0000: 256
		%0001: 128
		%0010: 64
		%0011: 32
		%0100: 16
		%0101: 8
		%0110: 4
		%0111: 2 (halfstep)
		%1000: 1 (fullstep)*/
		unsigned char MRES : 8;
		unsigned char : 4;
		/*Enable double edge STEP pulses
		0: Rising STEP pulse edge is active, falling edge is inactive.
		1: Both rising and falling STEP pulse edges are active.*/
		unsigned char DEDGE : 1;
		/*Enable STEP interpolation
		0: Disable STEP pulse interpolation
		1: Enable MicroPlyer STEP pulse multiplication by 16.*/
		unsigned char INTPOL : 1;
		unsigned char : 7;
	}b;
	unsigned int w : 17;
}DRVCTRL_SDOFF_0_t;
typedef union CHOPCONF_t {
	struct
	{
		/*Off time / MOSFET disable*/
		unsigned char TOFF : 4;
		/*Hysteresis start value or Fast decay time setting*/
		unsigned char HSTRT : 3;
		/*Hysteresis end (low) value or Sine wave offset */
		unsigned char HEND : 4;
		/*Hysteresis decrement interval or Fast decay mode
		CHM=0 => Hysteresis decrement period setting, in system clock periods:
		%00: 16
		%01: 32
		%10: 48
		%11: 64
		CHM=1 =>
		HDEC.1=0: current comparator can terminate the fast decay phase before timer expires.
		HDEC.1=1: only the timer terminates the fast decay phase.
		HDEC.0: MSB of fast decay time setting.*/
		unsigned char HDEC : 2;
		/*Random TOFF time
		Enable randomizing the slow decay phase duration:
		0: Chopper off time is fixed as set by bits tOFF
		1: Random mode, tOFF is random modulated by dNCLK= -12 … +3 clocks*/
		unsigned char RNDTF : 1;
		/*Chopper mode
		This mode bit affects the interpretation of the HDEC, HEND, and HSTRT
		parameters shown below. 0: Standard mode (SpreadCycle) 1: Constant tOFF with
		current is reached. Fast decay is after on time.*/
		unsigned char CHM : 1;
		/*Blanking time
		Blanking time interval, in system clock periods:
		%00: 16
		%01: 24
		%10: 36
		%11: 54*/
		unsigned char TBL : 2;
	}b;
	unsigned int w : 17;
}CHOPCONF_t;
typedef union SMARTEN_t {
	struct
	{
		/*Lower CoolStep threshold/CoolStep disable*/
		unsigned char SEMIN : 4;
		unsigned char : 1;
		/*Current increment size*/
		unsigned char SEUP : 2;
		unsigned char : 1;
		/*Upper CoolStep threshold as an offset from the lower threshold*/
		unsigned char SEMAX : 4;
		unsigned char : 1;
		/*Current decrement speed*/
		unsigned char SEDN : 2;
		/*Minimum CoolStep current*/
		unsigned char  SEIMIN : 1;
		unsigned char : 1;
	}b;
	unsigned int w : 17;
}SMARTEN_t;
/*SGCSCONF*/
typedef union {
	struct
	{
		/*Current scale (scales digital currents A and B)*/
		unsigned char  CS : 5;
		unsigned char : 3;
		/*StallGuard2 threshold value*/
		unsigned char  SGT : 7;
		unsigned char : 1;
		/*StallGuard2 filter enable*/
		unsigned char  SFILT : 1;
	}b;
	unsigned int w : 17;
}SGCSCONF_t;
typedef union DRVCONF_t {
	struct
	{
		/*Short to VS protection / CLK failsafe enable*/
		unsigned char  EN_S2VS : 1;
		/*Enable Passive fast decay / 5V undervoltage threshold*/
		unsigned char  EN_PFD : 1;
		/*Short to GND detection sensitivity*/
		unsigned char  SHRTSENS : 1;
		/*Overtemperature sensitivity*/
		unsigned char  OTSENS : 1;
		/*Select value for read out (RD bits)*/
		unsigned char  RDSEL : 2;
		/*Sense resistor voltage-based current scaling*/
		unsigned char  VSENSE : 1;
		/*STEP/DIR interface disable*/
		unsigned char  SDOFF : 1;
		/*Short detection delay for high-side and low-side FETs*/
		unsigned char  TS2G : 2;
		/*Short to GND protection disable*/
		unsigned char  DIS_S2G : 1;
		/*Slope control MSB for high side and low side*/
		unsigned char  SLP : 1;
		/*Slope control, low side*/
		unsigned char  SLPL : 2;
		/*Slope control, high side*/
		unsigned char  SLPH : 2;
		/*Reserved TEST mode
		Must be cleared for normal operation. When set, the
		SG_TST output exposes digital test values, and the
		TEST_ANA output exposes analog test values. */
		unsigned char  TST : 1;
	}b;
	unsigned int w : 17;
}DRVCONF_t;