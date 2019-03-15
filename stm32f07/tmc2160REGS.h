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
	unsigned int offsetPhB : 8;
	/*Offset calibration result phase A (signed)*/
	unsigned int offsetPhA : 8;
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
0…((2^8)-1) * 2^18 tCLK*/
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
case it runs slower than the target velocity. */
struct TSTEP_t
{
	unsigned int value : 20;
};
/*TPWMTHRS This is the upper velocity for StealthChop voltage PWM mode.
TSTEP ≥ TPWMTHRS
- StealthChop PWM mode is enabled, if configured
- DcStep is disabled*/
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
- Stall output signal (DIAG0/1) is enabled, if configured*/
struct TCOOLTHRS_t
{
	unsigned int value : 20;
};
enum tmc2160
{
	GCONF = 0x00, GSTAT = 0x01, IOIN = 0x04, OTP_PROG = 0x06, OTP_READ = 0x07, FACTORY_CONF = 0x08, SHORT_CONF = 0x09, DRV_CONF = 0x0A, GLOBAL_SCALER = 0x0B,
	OFFSET_READ = 0x0C, IHOLD_IRUN = 0x10, TPOWERDOWN = 0x11, TSTEP = 0x12, TPWMTHRS = 0x13, TCOOLTHRS = 0x14,
};
