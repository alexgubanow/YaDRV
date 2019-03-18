#pragma once
/*GCONF – Global configuration flags*/
struct GCONF_t
{
	/*1: Zero crossing recalibration during driver disable(via ENN or via TOFF setting)*/
	unsigned int recalibrate : 1;
	/*Timeout for step execution until standstill detection:
1: Short time: 2^18 clocks
0: Normal time: 2^20 clocks*/
	unsigned int faststandstill : 1;
	/*1: StealthChop voltage PWM mode enabled
(depending on velocity thresholds). Switch from
off to on state while in stand-still and at IHOLD=
nominal IRUN current, only.*/
	unsigned int en_pwm_mode : 1;
	/*1: Enable step input filtering for StealthChop
optimization with external step source (default=1)*/
	unsigned int multistep_filt : 1;
	/*1: Inverse motor direction*/
	unsigned int shaft : 1;
	/*1: Enable DIAG0 active on driver errors:
Over temperature (ot), short to GND (s2g),
undervoltage chargepump (uv_cp)
DIAG0 always shows the reset-status, i.e. is active low
during reset condition.*/
	unsigned int diag0_error : 1;
	/*1: Enable DIAG0 active on driver over temperature
prewarning (otpw)*/
	unsigned int diag0_otpw : 1;
	/*1: Enable DIAG0 active on motor stall (set
TCOOLTHRS before using this feature)*/
	unsigned int diag0_stall : 1;
	/*1: Enable DIAG1 active on motor stall (set
TCOOLTHRS before using this feature)*/
	unsigned int diag1_stall : 1;
	/*1: Enable DIAG1 active on index position (microstep
look up table position 0)*/
	unsigned int diag1_index : 1;
	/*1: Enable DIAG1 active when chopper is on (for the
coil which is in the second half of the fullstep)*/
	unsigned int diag1_onstate : 1;
	/*1: Enable output toggle when steps are skipped in
DcStep mode (increment of LOST_STEPS). Do not
enable in conjunction with other DIAG1 options.*/
	unsigned int diag1_steps_skipped : 1;
	/*0: DIAG0 is open collector output (active low)
1: Enable DIAG0 push pull output (active high)*/
	unsigned int diag0_int_pushpull : 1;
	/*0: DIAG1 is open collector output (active low)
1: Enable DIAG1 push pull output (active high)*/
	unsigned int diag1_pushpull : 1;
	/*0: Hysteresis for step frequency comparison is 1/16
1: Hysteresis for step frequency comparison is 1/32*/
	unsigned int small_hysteresis : 1;
	/*0: Normal operation
1: Emergency stop: ENCA_DCIN stops the sequencer
when tied high (no steps become executed by
the sequencer, motor goes to standstill state).*/
	unsigned int stop_enable : 1;
	/*0: Normal operation
1: Motor coil currents and polarity directly
programmed via serial interface: Register XDIRECT
(0x2D) specifies signed coil A current (bits 8..0)
and coil B current (bits 24..16). In this mode, the
current is scaled by IHOLD setting. Velocity based
current regulation of StealthChop is not available
in this mode. The automatic StealthChop current
regulation will work only for low stepper motor
velocities.*/
	unsigned int direct_mode : 1;
	/*0: Normal operation
1: Enable analog test output on pin DCO.
IHOLD[1..0] selects the function of DCO:
0…2: T120, DAC, VDDH
Hint: Not for user, set to 0 for normal operation!*/
	unsigned int test_mode : 1;
};

/*GSTAT – Global status flags
(Re-Write with ‘1’ bit to clear respective flags)*/
struct GSTAT_t
{
	/*1: Indicates that the IC has been reset. All registers
have been cleared to reset values.*/
	unsigned int reset : 1;
	/*1: Indicates, that the driver has been shut down
due to overtemperature or short circuit detection.
Read DRV_STATUS for details. The flag can only
be cleared when the temperature is below the
limit again.*/
	unsigned int drv_err : 1;
	/*1: Indicates an undervoltage on the charge pump.
The driver is disabled during undervoltage. This
flag is latched for information. */
	unsigned int uv_cp : 1;
};
/*IO INPUT Reads the state of all input pins available*/
struct IOIN
{
	/*STEP pin*/
	unsigned int STEP : 1;
	/*DIR pin*/
	unsigned int DIR : 1;
	/*DCEN_CFG4 pin*/
	unsigned int DCEN_CFG4 : 1;
	/*DCIN_CFG5 pin*/
	unsigned int DCIN_CFG5 : 1;
	/*DRV_ENN pin*/
	unsigned int DRV_ENN : 1;
	/*DCO_CFG6 pin*/
	unsigned int DCO_CFG6 : 1;
	/*1 pin, i dont know what does it mean(datasheet, page#26)*/
	unsigned int first : 1;
	/*VERSION: 0x30=first version of the IC
Identical numbers mean full digital compatibility.*/
	unsigned int VERSION : 8;
};
/*OTP_PROGRAM – OTP programming
Write access programs OTP memory (one bit at a time),
Read access refreshes read data from OTP after a write*/
struct OTP_PROG_t
{
	/*OTPBIT Selection of OTP bit to be programmed to the selected
byte location (n=0..7: programs bit n to a logic 1)*/
	unsigned int OTPBIT : 3;
	/*gap*/
	unsigned int : 1;
	/*OTPBYTE Set to 00*/
	unsigned int OTPBYTE : 2;
	/*gap*/
	unsigned int : 2;
	/*OTPMAGIC Set to 0xbd to enable programming. A programming
time of minimum 10ms per bit is recommended (check
by reading OTP_READ). */
	unsigned int OTPMAGIC : 8;
};

/*OTP_READ (Access to OTP memory result and update)
The OTP memory holds power up defaults for certain registers. All OTP memory bits are cleared to 0
by default. Programming only can set bits, clearing bits is not possible. Factory tuning of the clock
frequency affects OTP_FCLKTRIM. The state of these bits therefore may differ between individual ICs.*/
struct OTP_READ_t
{
	/*OTP_FCLKTRIM Reset default for FCLKTRIM
0: lowest frequency setting
31: highest frequency setting
Attention: This value is pre-programmed by factory clock
trimming to the default clock frequency of 12MHz and
differs between individual ICs! It should not be altered.*/
	unsigned int OTP_FCLKTRIM : 5;
	/*otp_S2_LEVEL Reset default for Short detection Levels:
0: S2G_LEVEL = S2VS_LEVEL = 6
1: S2G_LEVEL = S2VS_LEVEL = 12*/
	unsigned int otp_S2_LEVEL : 1;
	/*Reset default for DRVCONF.BBMCLKS
0: BBMCLKS=4
1: BBMCLKS=2*/
	unsigned int otp_BBM : 1;
	/*Reset default for TBL:
0: TBL=%10 (~3µs)
1: TBL=%01 (~2µs)*/
	unsigned int otp_TBL : 1;
};
/*FACTORY_CONF*/
struct FACTORY_CONF_t
{
	/*FCLKTRIM (Reset default: OTP)
0…31: Lowest to highest clock frequency. Check at
charge pump output. The frequency span is not
guaranteed, but it is tested, that tuning to 12MHz
internal clock is possible. The devices come preset to
12MHz clock frequency by OTP programming.
(Reset Default: OTP)*/
	unsigned int FCLKTRIM : 5;
};

/*SHORT_CONF*/
struct SHORT_CONF
{
	/*S2VS_LEVEL: Short to VS detector level for lowside FETs. Checks for
voltage drop in LS MOSFET and sense resistor.
4 (highest sensitivity) … 15 (lowest sensitivity)
Hint: Settings from 1 to 3 will trigger during normal
operation due to voltage drop on sense resistor.
(Reset Default: OTP 6 or 12)*/
	unsigned int S2VS_LEVEL : 4;
	/*gap*/
	unsigned int : 4;
	/*S2G_LEVEL: Short to GND detector level for highside FETs. Checks
for voltage drop on high side MOSFET
2 (highest sensitivity) … 15 (lowest sensitivity)
Attention: Settings below 6 not recommended at >52V
operation – false detection might result
(Reset Default: OTP 6 or 12)*/
	unsigned int S2G_LEVEL : 4;
	/*gap*/
	unsigned int : 4;
	/* SHORTFILTER: Spike filtering bandwidth for short detection
0 (lowest, 100ns), 1 (1µs), 2 (2µs) 3 (3µs)
Hint: A good PCB layout will allow using setting 0.
Increase value, if erroneous short detection occurs.
(Reset Default = %01)*/
	unsigned int SHORTFILTER : 2;
	/*shortdelay: Short detection delay
0=750ns: normal, 1=1500ns: high
The short detection delay shall cover the bridge
switching time. 0 will work for most applications.
(Reset Default = 0)*/
	unsigned int shortdelay : 1;
};
/*DRV_CONF*/
struct DRV_CONF_t
{
	/*BBMTIME: Break-Before make delay
0=shortest (100ns) … 16 (200ns) … 24=longest (375ns)
>24 not recommended, use BBMCLKS instead
Hint: Choose the lowest setting safely covering the
switching event in order to avoid bridge crossconduction. Add roughly 30% of reserve.
(Reset Default = 0)*/
	unsigned int BBMTIME : 5;
	/*gap*/
	unsigned int : 3;
	/*BBMCLKS: 0..15: Digital BBM time in clock cycles (typ. 83ns).
The longer setting rules (BBMTIME vs. BBMCLKS).
(Reset Default: OTP 4 or 2)*/
	unsigned int BBMCLKS : 4;
	/*gap*/
	unsigned int : 4;
	/*OTSELECT: Selection of over temperature level for bridge disable,
switch on after cool down to 120°C / OTPW level.
00: 150°C
01: 143°C
10: 136°C (not recommended when VSA > 24V)
11: 120°C (not recommended, no hysteresis)
Hint: Adapt overtemperature threshold as required to
protect the MOSFETs or other components on the PCB.
(Reset Default = %00)*/
	unsigned int OTSELECT : 2;
	/*DRVSTRENGTH: Selection of gate driver current. Adapts the gate driver
current to the gate charge of the external MOSFETs.
00: weak
01: weak+TC (medium above OTPW level)
10: medium
11: strong
Hint: Choose the lowest setting giving slopes <100ns.
(Reset Default = %10)*/
	unsigned int DRVSTRENGTH : 2;
	/*FILT_ISENSE: Filter time constant of sense amplifier to suppress
ringing and coupling from second coil operation
00: low – 100ns
01: – 200ns
10: – 300ns
11: high– 400ns
Hint: Increase setting if motor chopper noise occurs
due to cross-coupling of both coils.
(Reset Default = %00)*/
	unsigned int FILT_ISENSE : 2;
};
/*GLOBAL SCALER*/
struct GLOBAL_SCALER_t
{
	/*Global scaling of Motor current. This value is multiplied
to the current scaling in order to adapt a drive to a
certain motor type. This value should be chosen before
tuning other settings, because it also influences
chopper hysteresis.
0: Full Scale (or write 256)
1 … 31: Not allowed for operation
32 … 255: 32/256 … 255/256 of maximum current.
Hint: Values >128 recommended for best results
(Reset Default = 0)*/
	unsigned int scale : 8;
};
/*OFFSET_READ
look in datasheet, probably it has to be reversed*/
struct OFFSET_READ_t
{
	/*Offset calibration result phase B (signed)*/
	int offsetPhB : 8;
	/*Offset calibration result phase A (signed)*/
	int offsetPhA : 8;
};
/*IHOLD_IRUN – Driver current control*/
struct IHOLD_IRUN_t
{
	/*IHOLD Standstill current (0=1/32…31=32/32)
In combination with StealthChop mode, setting
IHOLD=0 allows to choose freewheeling or coil
short circuit for motor stand still.*/
	unsigned int IHOLD : 5;
	/*gap*/
	unsigned int : 3;
	/*IRUN Motor run current (0=1/32…31=32/32)
Hint: Choose sense resistors in a way, that normal
IRUN is 16 to 31 for best microstep performance.*/
	unsigned int IRUN : 5;
	/*gap*/
	unsigned int : 3;
	/*IHOLDDELAY Controls the number of clock cycles for motor
power down after a motion as soon as standstill is
detected (stst=1) and TPOWERDOWN has expired.
The smooth transition avoids a motor jerk upon
power down.
0: instant power down
1..15: Delay per current reduction step in multiple
of 2^18 clocks*/
	unsigned int IHOLDDELAY : 4;
};
/*TPOWERDOWN sets the delay time after stand still (stst) of the
motor to motor current power down. Time range is about 0 to
4 seconds.
Attention: A minimum setting of 2 is required to allow
automatic tuning of StealthChop PWM_OFFS_AUTO.
Reset Default = 10
0…((2^8)-1) * 2^18 tCLK
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP*/
struct TPOWERDOWN_t
{
	unsigned int value : 8;
};
/*TSTEP Actual measured time between two 1/256 microsteps derived
from the step input frequency in units of 1/fCLK. Measured
value is (2^20)-1 in case of overflow or stand still.
All TSTEP related thresholds use a hysteresis of 1/16 of the
compare value to compensate for jitter in the clock or the step
frequency. The flag small_hysteresis modifies the hysteresis to
a smaller value of 1/32.
(Txxx*15/16)-1 or
(Txxx*31/32)-1 is used as a second compare value for each
comparison value.
This means, that the lower switching velocity equals the
calculated setting, but the upper switching velocity is higher as
defined by the hysteresis setting.
In DcStep mode TSTEP will not show the mean velocity of the
motor, but the velocities for each microstep, which may not be
stable and thus does not represent the real motor velocity in
case it runs slower than the target velocity.
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP*/
struct TSTEP_t
{
	unsigned int value : 20;
};
/*TPWMTHRS This is the upper velocity for StealthChop voltage PWM mode.
TSTEP ≥ TPWMTHRS
- StealthChop PWM mode is enabled, if configured
- DcStep is disabled
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP*/
struct TPWMTHRS_t
{
	unsigned int value : 20;
};
/*TCOOLTHRS This is the lower threshold velocity for switching on smart
energy CoolStep and stallGuard feature. (unsigned)
Set this parameter to disable CoolStep at low speeds, where it
cannot work reliably. The stop on stall function (enable with
sg_stop when using internal motion controller) and the stall
output signal become enabled when exceeding this velocity. In
non-DcStep mode, it becomes disabled again once the velocity
falls below this threshold.
TCOOLTHRS ≥ TSTEP ≥ THIGH:
- CoolStep is enabled, if configured
- StealthChop voltage PWM mode is disabled
TCOOLTHRS ≥ TSTEP
- Stop on stall is enabled, if configured
- Stall output signal (DIAG0/1) is enabled, if configured
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP*/
struct TCOOLTHRS_t
{
	unsigned int value : 20;
};
/*This velocity setting allows velocity dependent switching into
a different chopper mode and fullstepping to maximize torque.
(unsigned)
The stall detection feature becomes switched off for 2-3
electrical periods whenever passing THIGH threshold to
compensate for the effect of switching modes.
TSTEP ≤ THIGH:
- CoolStep is disabled (motor runs with normal current
scale)
- StealthChop voltage PWM mode is disabled
- If vhighchm is set, the chopper switches to chm=1
with TFD=0 (constant off time with slow decay, only).
- If vhighfs is set, the motor operates in fullstep mode
and the stall detection becomes switched over to
DcStep stall detection.
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP*/
struct THIGH_t
{
	unsigned int value : 20;
};
/*This register is used in direct coil current
mode, only (direct_mode = 1). It bypasses the
internal sequencer. In this mode, the current is scaled by
IHOLD setting. Velocity based current
regulation of StealthChop is not available in
this mode. The automatic StealthChop current
regulation will work only for low stepper
motor velocities. 2x -255…+255*/
struct XDIRECT_t
{
	/*Specifies signed coil A
current (bits 8..0)*/
	int coilA : 9;
	/*gap*/
	unsigned int : 7;
	/*Specifies signed coil B current (bits
24..16)*/
	int coilB : 9;
};
/*Automatic commutation DcStep minimum velocity. Enable
DcStep by DCEN pin.
In this mode, the actual position is determined by the sensorless motor commutation and becomes fed back to the external
motion controller. In case the motor becomes heavily loaded,
VDCMIN is used as the minimum step velocity.
Hint: Also set DCCTRL parameters in order to operate DcStep.
(Only bits 22… 8 are used for value and for comparison)
Time reference t for VDCMIN: t = 2^24 / fCLK*/
struct VDCMIN_t
{
	unsigned int value : 23;
};
/*MSLUT 8x 32bit 0 or 1
reset default= sine wave table
Each bit gives the difference between entry x
and entry x+1 when combined with the corresponding MSLUTSEL W bits:
0: W= %00: -1
%01: +0
%10: +1
%11: +2
1: W= %00: +0
%01: +1
%10: +2
%11: +3
This is the differential coding for the first
quarter of a wave. Start values for CUR_A and
CUR_B are stored for MSCNT position 0 in
START_SIN and START_SIN90.
ofs31, ofs30, …, ofs01, ofs00
…
ofs255, ofs254, …, ofs225, ofs224*/
struct MSLUT_t
{
	unsigned int value[8];
};
/*MSLUTSEL – Look up Table Segmentation Definition
This register defines four segments within
each quarter MSLUT wave. Four 2 bit entries
determine the meaning of a 0 and a 1 bit in
the corresponding segment of MSLUT.
0<X1<X2<X3 reset default= sine wave table
The sine wave look up table can be divided into up to
four segments using an individual step width control
entry Wx. The segment borders are selected by X1, X2
and X3.
Segment 0 goes from 0 to X1-1.
Segment 1 goes from X1 to X2-1.
Segment 2 goes from X2 to X3-1.
Segment 3 goes from X3 to 255.
For defined response the values shall satisfy:
0<X1<X2<X3*/
struct MSLUTSEL_t
{
	/*Width control bit coding W0…W3:
%00: MSLUT entry 0, 1 select: -1, +0
%01: MSLUT entry 0, 1 select: +0, +1
%10: MSLUT entry 0, 1 select: +1, +2
%11: MSLUT entry 0, 1 select: +2, +3
	LUT width select from ofs00 to ofs(X1-1)*/
	unsigned int W0 : 2;
	/*Width control bit coding W0…W3:
%00: MSLUT entry 0, 1 select: -1, +0
%01: MSLUT entry 0, 1 select: +0, +1
%10: MSLUT entry 0, 1 select: +1, +2
%11: MSLUT entry 0, 1 select: +2, +3
	LUT width select from ofs(X1) to ofs(X2-1)*/
	unsigned int W1 : 2;
	/*Width control bit coding W0…W3:
%00: MSLUT entry 0, 1 select: -1, +0
%01: MSLUT entry 0, 1 select: +0, +1
%10: MSLUT entry 0, 1 select: +1, +2
%11: MSLUT entry 0, 1 select: +2, +3
	LUT width select from ofs(X2) to ofs(X3-1)*/
	unsigned int W2 : 2;
	/*Width control bit coding W0…W3:
%00: MSLUT entry 0, 1 select: -1, +0
%01: MSLUT entry 0, 1 select: +0, +1
%10: MSLUT entry 0, 1 select: +1, +2
%11: MSLUT entry 0, 1 select: +2, +3
	LUT width select from xofs(X3) to ofs255*/
	unsigned int W3 : 2;
	/*LUT segment 1 start*/
	unsigned int X1 : 8;
	/*LUT segment 2 start*/
	unsigned int X2 : 8;
	/*LUT segment 3 start*/
	unsigned int X3 : 8;
};
/*START_SIN and START_SIN90 
Start values are transferred to the microstep
registers CUR_A and CUR_B, whenever the
reference position MSCNT=0 is passed.*/
struct MSLUTSTART_t
{
	/*bit 7… 0: START_SIN gives the absolute current at
microstep table entry 0.
	reset default =0*/
	unsigned int START_SIN : 8;
	/*gap*/
	unsigned int : 8;
	/*bit 23… 16: START_SIN90 gives the absolute current for
microstep table entry at positions 256. 
	reset default =247*/
	unsigned int START_SIN90 : 8;
};
/*Microstep counter. Indicates actual position
in the microstep table for CUR_A. CUR_B uses
an offset of 256 (2 phase motor).
Hint: Move to a position where MSCNT is
zero before re-initializing MSLUTSTART or
MSLUT and MSLUTSEL.
0…1023*/
struct MSCNT_t
{
	unsigned int value : 10;
};
/**/
struct MSCURACT_t
{
	/*bit 8… 0: CUR_A (signed):
Actual microstep current for
motor phase A as read from
MSLUT (not scaled by current)
+/-0...255*/
	int CUR_A : 9;
	/*gap*/
	unsigned int : 7;
/*bit 24… 16: CUR_B (signed):
Actual microstep current for
motor phase B as read from
MSLUT (not scaled by current)
+/-0...255 */
	int CUR_B : 9;
};
/*CHOPCONF – Chopper Configuration
reset default=0x10410150*/
struct CHOPCONF_t
{
	/*TOFF off time and driver enable
	Off time setting controls duration of slow decay phase
NCLK= 24 + 32*TOFF
%0000: Driver disable, all bridges off
%0001: 1 – use only with TBL ≥ 2
%0010 … %1111: 2 … 15*/
	unsigned int toff : 4;
	/*When ChpperMode(chm)=0 this register become to HSTRT
hysteresis start value added to HEND
%000 … %111: Add 1, 2, …, 8 to hysteresis low value HEND
(1/512 of this setting adds to current setting)
Attention: Effective HEND+HSTRT ≤ 16.
Hint: Hysteresis decrement is done each 16 clocksWhen ChpperMode(chm)=1 this register become to TFD Fast decay time setting (MSB: fd3):
%0000 … %1111: Fast decay time setting TFD with
NCLK= 32*TFD (%0000: slow decay only)*/
	unsigned int HSTRT_TFD : 3;
	/*When ChpperMode(chm)=0 this register become to HEND hysteresis low value
	%0000 … %1111:
Hysteresis is -3, -2, -1, 0, 1, …, 12
(1/512 of this setting adds to current setting)
This is the hysteresis value which becomes
used for the hysteresis chopper.
When ChpperMode(chm)=1 this register become to OFFSET sine wave offset
%0000 … %1111:
Offset is -3, -2, -1, 0, 1, …, 12
This is the sine wave offset and 1/512 of the
value becomes added to the absolute value
of each sine wave entry.*/
	unsigned int HEND_OFFSET : 4;
	/*When ChpperMode(chm) = 1 this register become to MSB of fast decay time
	setting TFD Fast decay time setting(MSB: fd3) :
		% 0000 … % 1111 : Fast decay time setting TFD with
		NCLK = 32 * TFD(% 0000: slow decay only)*/
	unsigned int TFD3 : 1;
	/*fast decay mode
	When ChpperMode(chm) = 1 setting disfdcc=1 disables current comparator usage for termination of the fast decay cycle*/
	unsigned int disfdcc : 1;
	unsigned int : 1;
	/*chopper mode
	Set 0 - Standard mode (SpreadCycle)
Set 1 - Constant off time with fast decay time.
Fast decay time is also terminated when the
negative nominal current is reached. Fast decay is
after on time.*/
	unsigned int chm : 1;
	/*TBL blank time select %00 … %11: Set comparator blank time to 16, 24, 36 or 54 clocks
Hint: %01 or %10 is recommended for most applications*/
	unsigned int tbl : 2;
	unsigned int : 1;
	/*high velocity fullstep selection 
	This bit enables switching to fullstep, when VHIGH is
exceeded. Switching takes place only at 45° position.
The fullstep target current uses the current value from
the microstep table at the 45° position.*/
	unsigned int vhighfs : 1;
	/*high velocity chopper mode
This bit enables switching to chm=1 and fd=0, when VHIGH
is exceeded. This way, a higher velocity can be achieved.
Can be combined with vhighfs=1. If set, the TOFF setting
automatically becomes doubled during high velocity
operation in order to avoid doubling of the chopper
frequency.*/
	unsigned int vhighchm : 1;
	/*TPFD allows dampening of motor mid-range resonances.
Passive fast decay time setting controls duration of the
fast decay phase inserted after bridge polarity change
NCLK= 128*TPFD
%0000: Disable
%0001 … %1111: 1 … 15*/
	unsigned int TPFD : 4;
	/*MRES micro step resolution
	%0000: Native 256 microstep setting. Normally use this setting with the internal motion controller.
	%0001 … %1000: 128, 64, 32, 16, 8, 4, 2, FULLSTEP
Reduced microstep resolution esp. for STEP/DIR operation.
The resolution gives the number of microstep entries per
sine quarter wave.
The driver automatically uses microstep positions which
result in a symmetrical wave, when choosing a lower
microstep resolution.
step width=2^MRES [microsteps]*/
	unsigned int MRES : 4;
	/*interpolation to 256 microsteps
	1: The actual microstep resolution (MRES) becomes
extrapolated to 256 microsteps for smoothest motor
operation (useful for STEP/DIR operation, only)*/
	unsigned int intpol : 1;
	/*enable double edge step pulses
	1: Enable step impulse at each step edge to reduce step
frequency requirement. */
	unsigned int dedge : 1;
	/*short to GND protection disable
	0: Short to GND protection is on
1: Short to GND protection is disabled*/
	unsigned int diss2g : 1;
	/*short to supply protection disable
	0: Short to VS protection is on
1: Short to VS protection is disabled*/
	unsigned int diss2vs : 1;
};
/*COOLCONF – Smart Energy Control CoolStep and StallGuard2*/
struct COOLCONF_t
{
	/*minimum StallGuard2 value for smart current control and smart current enable
	If the StallGuard2 result falls below SEMIN*32, the motor
current becomes increased to reduce motor load angle.
%0000: smart current control CoolStep off
%0001 … %1111: 1 … 15*/
	unsigned int semin : 4;
	unsigned int : 1;
	/*current up step width 
	Current increment steps per measured StallGuard2 value
	%00 … %11: 1, 2, 4, 8*/
	unsigned int seup : 2;
	unsigned int : 1;
	/*StallGuard2 hysteresis value for smart current control
If the StallGuard2 result is equal to or above
(SEMIN+SEMAX+1)*32, the motor current becomes
decreased to save energy.
%0000 … %1111: 0 … 15*/
	unsigned int semax : 4;
	unsigned int : 1;
	/*current down step speed
	%00: For each 32 StallGuard2 values decrease by one
%01: For each 8 StallGuard2 values decrease by one
%10: For each 2 StallGuard2 values decrease by one
%11: For each StallGuard2 value decrease by one*/
	unsigned int sedn : 2;
	/*minimum current for smart current control
0: 1/2 of current setting (IRUN)
1: 1/4 of current setting (IRUN)*/
	unsigned int seimin : 1;
	/*StallGuard2 threshold value
	This signed value controls StallGuard2 level for stall
output and sets the optimum measurement range for
readout. A lower value gives a higher sensitivity. Zero is
the starting value working with most motors.
-64 to +63: A higher value makes StallGuard2 less
sensitive and requires more torque to
indicate a stall.*/
	int sgt : 7;
	unsigned int : 1;
	/*StallGuard2 filter enable
	Set 0 - Standard mode, high time resolution for StallGuard2
	Set 1 - Filtered mode, StallGuard2 signal updated for each
four fullsteps (resp. six fullsteps for 3 phase motor)
only to compensate for motor pole tolerances*/
	unsigned int sfilt : 1;
	unsigned int : 1;
};
/*DcStep (DC) automatic commutation
configuration register (enable via pin DCEN
or via VDCMIN)
Using a higher microstep resolution or
interpolated operation, DcStep delivers a
better stallGuard signal.
DC_SG is also available above VHIGH if
vhighfs is activated. For best result also set
vhighchm.*/
struct DCCTRL_t
{
	/*bit 9… 0: DC_TIME: Upper PWM on time
limit for commutation (DC_TIME *
1/fCLK). Set slightly above effective
blank time TBL.*/
	unsigned int DC_TIME : 10;
	/*gap*/
	unsigned int : 6;
/*bit 23… 16: DC_SG: Max. PWM on time for
step loss detection using DcStep
StallGuard2 in DcStep mode.
(DC_SG * 16/fCLK) 
Set slightly higher than DC_TIME/16 0=disable*/
	unsigned int DC_SG : 8;
};
/*DRV_STATUS – StallGuard2 Value and Driver Error Flags*/
struct DRV_STATUS_t
{
	/*StallGuard2 result respectively PWM on time for coil A in stand still for motor temperature detection
	Mechanical load measurement:
The StallGuard2 result gives a means to measure mechanical
motor load. A higher value means lower mechanical load. A
value of 0 signals highest load. With optimum SGT setting,
this is an indicator for a motor stall. The stall detection
compares SG_RESULT to 0 in order to detect a stall. SG_RESULT
is used as a base for CoolStep operation, by comparing it to a
programmable upper and a lower limit. It is not applicable in
StealthChop mode.
StallGuard2 works best with microstep operation or DcStep.
Temperature measurement:
In standstill, no StallGuard2 result can be obtained. SG_RESULT
shows the chopper on-time for motor coil A instead. Move the
motor to a determined microstep position at a certain current
setting to get a rough estimation of motor temperature by a
reading the chopper on-time. As the motor heats up, its coil
resistance rises and the chopper on-time increases. */
	unsigned int SG_RESULT : 10;
	unsigned int : 2;
	/*short to supply indicator phase A
	1: Short to supply detected on phase A or B. The driver
becomes disabled. The flags stay active, until the driver is
disabled by software (TOFF=0) or by the ENN input. Sense
resistor voltage drop is included in the measurement!*/
	unsigned int s2vsa : 1;
	/*short to supply indicator phase B
	1: Short to supply detected on phase A or B. The driver
becomes disabled. The flags stay active, until the driver is
disabled by software (TOFF=0) or by the ENN input. Sense
resistor voltage drop is included in the measurement!*/
	unsigned int s2vsb : 1;
	/*StealthChop indicator 
	1: Driver operates in StealthChop mode*/
	unsigned int stealth : 1;
	/*full step active indicator
1: Indicates that the driver has switched to fullstep as defined
by chopper mode settings and velocity thresholds. */
	unsigned int fsactive : 1;
	/*actual motor current / smart energy current
Actual current control scaling, for monitoring smart energy
current scaling controlled via settings in register COOLCONF, or
for monitoring the function of the automatic current scaling.*/
	unsigned int CS_ACTUAL : 5;
	unsigned int : 3;
	/*StallGuard2 status 1: Motor stall detected (SG_RESULT=0) or DcStep stall in DcStep
mode.*/
	unsigned int stallGuard : 1;
	/*overtemperature flag 1: Overtemperature limit has been reached. Drivers become
disabled until otpw is also cleared due to cooling down of the IC. 
The overtemperature flag is common for both bridges.*/
	unsigned int ot : 1;
	/*overtemperature prewarning flag
1: Overtemperature pre-warning threshold is exceeded.
The overtemperature pre-warning flag is common for both
bridges.*/
	unsigned int otpw : 1;
	/*short to ground indicator phase A
	1: Short to GND detected on phase A or B. The driver becomes
disabled. The flags stay active, until the driver is disabled by
software (TOFF=0) or by the ENN input.*/
	unsigned int s2ga : 1;
	/*short to ground indicator phase B
	1: Short to GND detected on phase A or B. The driver becomes
disabled. The flags stay active, until the driver is disabled by
software (TOFF=0) or by the ENN input.*/
	unsigned int s2gb : 1;
	/*open load indicator phase A
	1: Open load detected on phase A or B.
Hint: This is just an informative flag. The driver takes no action
upon it. False detection may occur in fast motion and
standstill. Check during slow motion, only.*/
	unsigned int ola : 1;
	/*open load indicator phase A
	1: Open load detected on phase A or B.
Hint: This is just an informative flag. The driver takes no action
upon it. False detection may occur in fast motion and
standstill. Check during slow motion, only.*/
	unsigned int olb : 1;
	/*standstill indicator This flag indicates motor stand still in each operation mode.
This occurs 2^20 clocks after the last step pulse.*/
	unsigned int stst : 1;
};
/*PWMCONF – Voltage PWM Mode StealthChop
reset default=0xC40C001E*/
struct PWMCONF_t
{
	/*PWM_OFS User defined amplitude(offset)
	User defined PWM amplitude offset (0-255) related to full
motor current (CS_ACTUAL=31) in stand still.(Reset default=30)
Use PWM_OFS as initial value for automatic scaling to
speed up the automatic tuning process. To do this, set
PWM_OFS to the determined, application specific value,
with pwm_autoscale=0. Only afterwards, set
pwm_autoscale=1. Enable StealthChop when finished.
PWM_OFS = 0 will disable scaling down motor current
below a motor specific lower measurement threshold.
This setting should only be used under certain
conditions, i.e. when the power supply voltage can vary
up and down by a factor of two or more. It prevents
the motor going out of regulation, but it also prevents
power down below the regulation limit.
PWM_OFS > 0 allows automatic scaling to low PWM duty
cycles even below the lower regulation threshold. This
allows low (standstill) current settings based on the
actual (hold) current scale (register IHOLD_IRUN). */
	unsigned int PWM_OFS : 8;
	/*PWM_GRAD User defined amplitude gradient
	Velocity dependent gradient for PWM amplitude: PWM_GRAD * 256 / TSTEP
This value is added to PWM_OFS to compensate for the
velocity-dependent motor back-EMF.
Use PWM_GRAD as initial value for automatic scaling to
speed up the automatic tuning process. To do this, set
PWM_GRAD to the determined, application specific value,
with pwm_autoscale=0. Only afterwards, set
pwm_autoscale=1. Enable StealthChop when finished.
Hint: After initial tuning, the required initial value can be read
out from PWM_GRAD_AUTO.*/
	unsigned int PWM_GRAD : 8;
	/*PWM frequency selection 
	%00: fPWM=2/1024 fCLK (Reset default)
%01: fPWM=2/683 fCLK
%10: fPWM=2/512 fCLK
%11: fPWM=2/410 fCLK*/
	unsigned int pwm_freq : 2;
	/*PWM automatic amplitude scaling
Set 0 - User defined feed forward PWM amplitude. The
current settings IRUN and IHOLD have no influence!
The resulting PWM amplitude (limited to 0…255) is:
PWM_OFS * ((CS_ACTUAL+1) / 32)
+ PWM_GRAD * 256 / TSTEP
Set 1 - Enable automatic current control (Reset default)*/
	unsigned int pwm_autoscale : 1;
	/*PWM automatic gradient adaptation
	Set to 0 Fixed value for PWM_GRAD (PWM_GRAD_AUTO = PWM_GRAD)
Set to 1 Automatic tuning (only with pwm_autoscale=1)
(Reset default)
PWM_GRAD_AUTO is initialized with PWM_GRAD
while pwm_autograd=0 and becomes optimized
automatically during motion.
Preconditions
1. PWM_OFS_AUTO has been automatically
initialized. This requires standstill at IRUN for
>130ms in order to a) detect standstill b) wait >
128 chopper cycles at IRUN and c) regulate
PWM_OFS_AUTO so that
-1 < PWM_SCALE_AUTO < 1
2. Motor running and 1.5 * PWM_OFS_AUTO <
PWM_SCALE_SUM < 4* PWM_OFS_AUTO and
PWM_SCALE_SUM < 255.
Time required for tuning PWM_GRAD_AUTO
About 8 fullsteps per change of +/-1.
Also enables use of reduced chopper frequency for
tuning PWM_OFS_AUTO.*/
	unsigned int pwm_autograd : 1;
	/*Allows different standstill modes
	Stand still option when motor current setting is zero (I_HOLD=0).
%00: Normal operation
%01: Freewheeling
%10: Coil shorted using LS drivers
%11: Coil shorted using HS drivers*/
	unsigned int freewheel : 2;
	unsigned int : 2;
	/*Regulation loop gradient
	User defined maximum PWM amplitude change per half wave when using pwm_autoscale=1. (1…15):
1: 0.5 increments (slowest regulation)
2: 1 increment
3: 1.5 increments
4: 2 increments (Reset default))
...
8: 4 increments
...
15: 7.5 increments (fastest regulation)*/
	unsigned int PWM_REG : 4;
	/*PWM automatic scale amplitude limit when switching onLimit for PWM_SCALE_AUTO when switching back from
SpreadCycle to StealthChop. This value defines the upper
limit for bits 7 to 4 of the automatic current control
when switching back. It can be set to reduce the current
jerk during mode change back to StealthChop.
It does not limit PWM_GRAD or PWM_GRAD_AUTO offset.
(Default = 12)*/
	unsigned int PWM_LIM : 4;
};
/*Results of StealthChop amplitude regulator.
These values can be used to monitor
automatic PWM amplitude scaling (255=max.
voltage).*/
struct PWM_SCALE_t
{
	/*bit 7… 0 PWM_SCALE_SUM:
Actual PWM duty cycle. This
value is used for scaling the
values CUR_A and CUR_B read
from the sine wave table.
0…255*/
	unsigned int PWM_SCALE_SUM : 8;
	/*gap*/
	unsigned int : 8;
	/*bit 24… 16 PWM_SCALE_AUTO:
9 Bit signed offset added to the
calculated PWM duty cycle. This
is the result of the automatic
amplitude regulation based on
current measurement.
signed -255…+255*/
	int PWM_SCALE_AUTO : 9;
};
/*These automatically generated values can be
read out in order to determine a default /
power up setting for PWM_GRAD and
PWM_OFS.*/
struct PWM_AUTO_t
{
	/*bit 7… 0 PWM_OFS_AUTO:
Automatically determined offset
value 0…255*/
	unsigned int PWM_SCALE_SUM : 8;
	/*gap*/
	unsigned int : 8;
	/*bit 23… 16 PWM_GRAD_AUTO:
Automatically determined
gradient value 0…255*/
	unsigned int PWM_SCALE_SUM : 8;
};
/*Number of input steps skipped due to higher
load in DcStep operation, if step input does
not stop when DC_OUT is low. This counter
wraps around after 2^20 steps. Counts up or
down depending on direction. Only with
SDMODE=1.*/
struct LOST_STEPS_t
{
	unsigned int value;
};
enum tmc2160
{
	GCONF = 0x00, GSTAT = 0x01, IOIN = 0x04, OTP_PROG = 0x06, OTP_READ = 0x07, FACTORY_CONF = 0x08, SHORT_CONF = 0x09, DRV_CONF = 0x0A, GLOBAL_SCALER = 0x0B,
	OFFSET_READ = 0x60, IHOLD_IRUN = 0x10, TPOWERDOWN = 0x11, TSTEP = 0x12, TPWMTHRS = 0x13, TCOOLTHRS = 0x14, THIGH = 0x15, XDIRECT = 0x2D, VDCMIN = 0x33,
	MSLUT = 0x60, MSLUTSEL = 0x68, MSLUTSTART = 0x69, MSCNT = 0x6A, MSCURACT = 0x6B, CHOPCONF = 0x6C, COOLCONF = 0x6D, DCCTRL = 0x6E, DRV_STATUS = 0x6F,
	PWMCONF = 0x70, PWM_SCALE = 0x71, PWM_AUTO = 0x72, LOST_STEPS = 0x73
};
