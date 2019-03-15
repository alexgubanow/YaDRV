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

enum tmc2160
{
	GCONF = 0x00
};


#define TMC2160_GCONF       0x00
#define TMC2160_GSTAT       0x01
#define TMC2160_IOIN        0x04
#define TMC2160_DRV_CONF	0x0A
#define TMC2160_IHOLD_IRUN  0x10
#define TMC2160_TPOWERDOWN  0x11
#define TMC2160_TSTEP       0x12
#define TMC2160_TPWMTHRS    0x13
#define TMC2160_TCOOLTHRS   0x14
#define TMC2160_THIGH       0x15
#define TMC2160_XDIRECT     0x2D
#define TMC2160_VDCMIN      0x33
#define TMC2160_MSLUT0      0x60
#define TMC2160_MSLUT1      0x61
#define TMC2160_MSLUT2      0x62
#define TMC2160_MSLUT3      0x63
#define TMC2160_MSLUT4      0x64
#define TMC2160_MSLUT5      0x65
#define TMC2160_MSLUT6      0x66
#define TMC2160_MSLUT7      0x67
#define TMC2160_MSLUTSEL    0x68
#define TMC2160_MSLUTSTART  0x69
#define TMC2160_MSCNT       0x6A
#define TMC2160_MSCURACT    0x6B
#define TMC2160_CHOPCONF    0x6C
#define TMC2160_COOLCONF    0x6D
#define TMC2160_DCCTRL      0x6E
#define TMC2160_DRV_STATUS  0x6F
#define TMC2160_PWMCONF     0x70
#define TMC2160_PWM_SCALE   0x71
#define TMC2160_ENCM_CTRL   0x72
#define TMC2160_LOST_STEPS  0x73