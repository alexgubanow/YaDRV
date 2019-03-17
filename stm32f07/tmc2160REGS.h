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
(Only bits 22… 8 are used for value and for comparison)Time reference t for VDCMIN: t = 2^24 / fCLK*/
struct VDCMIN_t
{
	unsigned int value : 23;
};
/*MSLUT 8x 32bit 0 or 1
reset default= sine wave tableEach bit gives the difference between entry x
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
/*This register defines four segments within
each quarter MSLUT wave. Four 2 bit entries
determine the meaning of a 0 and a 1 bit in
the corresponding segment of MSLUT.
See separate table!
0<X1<X2<X3 reset default= sine wave table*/
struct MSLUTSEL_t
{
	unsigned int value;
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
/*chopper and driver configuration
See separate table!
reset default=0x10410150*/
struct CHOPCONF_t
{
	unsigned int value;
};
/*CoolStep smart current control register
and StallGuard2 configuration
See separate table!*/
struct COOLCONF_t
{
	unsigned int value : 25;
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
/*StallGuard2 value and driver error flags
See separate table!*/
struct DRV_STATUS_t
{
	unsigned int value;
};
/*Voltage PWM mode chopper configuration
See separate table!
reset default=0xC40C001E*/
struct PWMCONF_t
{
	unsigned int value;
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
