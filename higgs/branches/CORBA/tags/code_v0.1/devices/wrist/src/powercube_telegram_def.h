/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 * <p> Definitions for the powercube module </p>
 */
#ifndef __POWERCUBE_TELEGRAMDEF_HPP
#define __POWERCUBE_TELEGRAMDEF_HPP

// ------------------------------------------------------------------ 
// Telegram commandes (CMD) for telegrams
// ------------------------------------------------------------------ 

// Data direction: Host computer -> Sensor

typedef enum {
    RESET_CMD			= 0x00,	// Clear error state.
    HOME_CMD			= 0x01,	// Start Homing procedure.
    HALT_CMD			= 0x02,	// Stop inmediately.
    PIDPARAM_CMD		= 0x09,	// Recalculate the PID loop parameters.
    SET_EXTENDED_CMD		= 0x08,	// Set parameter.
    GET_EXTENDED_CMD		= 0x0a,	// Fetch parameter.
    SET_MOTION_CMD		= 0x0b,	// Set motion command.
    SET_I_STEP_CMD		= 0x0d,	// Motion command in step mode.
    INVALID_CMD			= 0xff,	// -.

// Data direction: Sensor -> Host computer

} PowerCubeCommand;

/**
 * Parameters
 */
typedef enum
{
    DefHomeOffset		= 0x00,	// Offset to the home position.
    DefGearRatio		= 0x01,	// Gear ratio.
    DefLinRatio			= 0x02,	// Transmission factor for transforming rotary in linear motion.
    DefMinPos			= 0x03,	// Minimum drive position.
    DefMaxPos			= 0x04,	// Maximum drive position.
    DefMaxDeltaPos		= 0x05,	// Maximum following error for the digital servo filter.
    DefMaxDeltaVel		= 0x06,	// Maximum following error for velocity control.
    DefTorqueRatio		= 0x07,	// Transmission factor for transforming current to torque.
    DefCurRatio			= 0x08,	// Transmission factor for current measurement.
    DefMinVel			= 0x09,	// Minimum velocity.
    DefMaxVel			= 0x0a,	// Maximum velocity.
    DefMinAcc			= 0x0b,	// Minimum acceleration.
    DefMaxAcc			= 0x0c,	// Maximum acceleration.
    DefMinCur			= 0x0d,	// Minimum current.
    DefMaxCur			= 0x0e,	// Maximum current.
    DefHomeVel			= 0x0f,	// Homing velocity. This value is signed and thereby
					// specifies the homing direction.
    DefHomeAcc			= 0x10,	// Homing acceleration.
    DefCubeSerial		= 0x1a,	// Serial number of the PowerCube.
    DefConfig			= 0x1b,	// Config word.
    DefPulsesPerTurn		= 0x1c,	// Number of encoder ticks per revolution.
    DefCubeVersion		= 0x1d,	// Version information.
    DefServiceInterval		= 0x1e,	// Service interval.
    DefBrakeTimeOut		= 0x1f,	// Delay for releasing the brake in ms.
    DefAddress			= 0x20,	// Module bus address [1..31].
    DefPrimBaud			= 0x22,	// Primary Baud rate setting.
    DefSecBaud			= 0x23,	// Secondary Baud rate setting.
    PosCount			= 0x24,	// Absolute Counter value.
    RefPosCount			= 0x25,	// Absolute Counter value at Homing position.
    DIoSetup			= 0x26,	// Digital IO word.
    CubeState			= 0x27,	// Module State word.
    TargetPosInc		= 0x28,	// Target position in Encoder ticks.
    TargetVelInc		= 0x29,	// Target velocity en Encoder ticks/s.
    TargetAccInc		= 0x2a,	// Target acceleration in Encoder ticks/s^2.
    StepInc			= 0x2b,	// Step mode target position in Encoder ticks.
    HomeOffsetInc		= 0x2c,	// Home offset in Encoder ticks.
    RawCur			= 0x35,	// Commanded Current in Digits [-500..+500].
    HomeToZeroInc		= 0x36,	// Number of Encoder ticks between home switch and
					// Encoder index.
    Config			= 0x39,	// Config word.
    MoveMode			= 0x3a,	// Motion mode.
    IncRatio			= 0x3b,	// Ratio of Encoder ticks and unit rad resp m.
    ActPos			= 0x3c,	// Actual position in rad resp. m (Actual value).
    ActPos_			= 0x3d,	// Previous position in rad resp m (Actual value).
    IPolPos			= 0x3e,	// Actual interpolated position (Actual value).
    DeltaPos			= 0x3f,	// Actual following error (Actual value).
    MaxDeltaPos			= 0x40,	// Maximum following error.
    ActVel			= 0x41,	// Actual velocity in units/s (Actual value).
    IPolVel			= 0x42,	// Actual Interpolated velocity in units/s (Actual value).
    MinPos			= 0x45,	// Minimum position (Limit).
    MaxPos			= 0x46,	// Maximum position (Limit).
    MaxVel			= 0x48,	// Maximum velocity in units/s (Limit).
    MaxAcc			= 0x4a,	// Maximum acceleration in units/s^2 (Limit).
    MaxCur			= 0x4c,	// Maximum Current (Limit).
    Cur				= 0x4d,	// Actual current (Actual value).
    TargetPos			= 0x4e,	// Target position in units (Target value).
    TargetVel			= 0x4f,	// Target velocity in units/s (Target value).
    TargetAcc			= 0x50,	// Target acceleration in units/s^2 (Target value).
    DefC0			= 0x51,	// Servo loop gain C0 (Default value).
    DefDamp			= 0x52,	// Servo loop damping (Default value).
    DefA0			= 0x53,	// Servo loop parameter A0 (Default value).
    ActC0			= 0x54,	// Servo loop gain C0 (Actual value).
    ActDamp			= 0x85,	// Servo loop damping (Actual value).
    ActA0			= 0x86,	// Servo loop parameter A0 (Actual value).
    DefBurnCount		= 0x87,	// Number of flash downloads (Default downloads).
    Setup			= 0x88,	// Setup word (Default value).
    HomeOffset			= 0x89,	// Home offset (Actual value).
} PowerCubeParameter;


// ------------------------------------------------------------------ 
// Modes (data(0)) for telegram SET_MOTION_CMD
// ------------------------------------------------------------------ 

typedef enum
{
    FRAMP_MODE			= 4,	// Set Mode for target position.
    FSTEP_MODE			= 6,	// Set Mode for target position and time.
    FVEL_MODE			= 7,	// Set Mode for velocity.
    FCUR_MODE			= 8,	// Set Mode for current.
    IRAMP_MODE			= 9,	// Set Mode for target position.
    ISTEP_MODE			= 6,	// Set Mode for target position and time.
    IVEL_MODE			= 7,	// Set Mode for velocity.
    ICUR_MODE			= 8,	// Set Mode for current.

    FRAMP_ACK			= 14,	// Set Mode for target position.
    FSTEP_ACK			= 16,	// Set Mode for target position and time.
    FVEL_ACK			= 17,	// Set Mode for velocity.
    FCUR_ACK			= 18,	// Set Mode for current.
    IRAMP_ACK			= 19,	// Set Mode for target position.
    ISTEP_ACK			= 21,	// Set Mode for target position and time.
    IVEL_ACK			= 22,	// Set Mode for velocity.
    ICUR_ACK			= 23,	// Set Mode for current.
} PowerCubeMotion;

typedef enum
{
    SHORT_NOT_OK		= 0x01,	// (STATE_ERROR) OR (NOT STATE_HOME_OK) OR (STATE_HALTED).
    SHORT_SWR			= 0x02,	// STATE_SWR.
    SHORT_SW1			= 0x04,	// STATE_SWR.
    SHORT_SW2			= 0x08,	// STATE_SWR.
    SHORT_MOTION		= 0x10,	// STATE_MOTION.
    SHORT_RAMP_END		= 0x20,	// STATE_RAMP_END.
    SHORT_INPROGRESS		= 0x40,	// STATE_INPROGRESS.
    SHORT_FULLBUFFER		= 0x80,	// STATE_FULLBUFFER.
} PowerCubeShortState;

typedef enum
{
    INBIT0			= 0x01,	// State of input 0.
    INBIT1			= 0x02,	// State of input 1.
    INBIT2			= 0x04,	// State of input 2.
    INBIT3			= 0x08,	// State of input 3.
    OUTBIT0			= 0x10,	// State of output 0.
    OUTBIT1			= 0x20,	// State of output 1.
    OUTBIT2			= 0x40,	// State of output 2.
    OUTBIT3			= 0x80,	// State of output 3.
} PowerCubeDigitalIOState;

typedef enum
{
    STATE_ERROR			= 0x00000001,	// An error ocurred.
    STATE_HOME_OK		= 0x00000002,	// This flag is set after a succesfull homing procedure.
    STATE_HALTED		= 0x00000004,	// This flag is set in conjuction with an emergency stop.
    STATE_POWERFAULT		= 0x00000008,	// This flag defines an error of the servo amplifier.
    STATE_TOW_ERROR		= 0x00000010,	// Tow error: the servo loop was not able to follow
						// the target position within the given limit.
    STATE_COMM_ERROR		= 0x00000020,	// A data transmission error ocurred.
    STATE_SWR			= 0x00000040,	// This flag shows the state of the home switch.
    STATE_SW1			= 0x00000080,	// This flag shows the state of the Limit switch 1.
    STATE_SW2			= 0x00000100,	// This flag shows the state of the Limit switch 2.
    STATE_BRAKEACTIVE		= 0x00000200,	// This flag is a warning of the brake.
    STATE_CURLIMIT		= 0x00000400,	// This flag is a warning of the servo loop.
    STATE_MOTION		= 0x00000800,	// This flag indicates the drive is in motion.
    STATE_RAMP_ACC		= 0x00001000,	// This flag indicates the drive is in acceleration
						// when controlled by ramp motion command.
    STATE_RAMP_STEADY		= 0x00002000,	// This flag indicates the drive is moving at constant speed
						// when controlled by ramp motion command.
    STATE_RAMP_DEC		= 0x00004000,	// This flag indicates the drive is in deceleration
						// when controlled by ramp motion command.
    STATE_RAMP_END		= 0x00008000,	// This flag indicates the end of a ramp motion profile.
						// The drive is not moving.
    STATE_INPROGRESS		= 0x00010000,	// This flag is only used in step motion control.
						// It indicates a step motion command is in progress.
    STATE_FULLBUFFER		= 0x00020000,	// This flag is only used in step motion control.
						// It indicates a step motion command was pushed to the stack command.
						// This happens when the module receives a Step motion command while
						// STATE_INPROGRESS is set.
    STATE_POW_VOLT_ERR		= 0x00040000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// It indicates the voltage drop in the servo loop
    STATE_POW_FET_TEMP		= 0x00080000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// The power transistors have overheated and the servo loop has been disabled
    STATE_POW_WDG_TEMP		= 0x00100000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// The motor has overheated and the servo loop has been disabled
    STATE_POW_SHORCUR		= 0x00200000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// A short circuit occured. The servo loop has been disabled.
    STATE_POW_HALLERR		= 0x00400000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// An error occurred in reading the hall effect sensors of the motor
						// The motor has been overheated.
    STATE_POW_INTEGRALERR	= 0x00800000,	// This flag is set in conjuction with STATE_POWERFAULT.
						// The drive has been overloaded and the servo loop has been disabled
    STATE_CPU_OVERLOAD		= 0x01000000,	// Communication breakdown between CPU and current controller.
						// Power must be switched off.
    STATE_BEYOND_HARD		= 0x02000000,	// This flag indicates the module has reached the hard limit.
						// An emergency stop has been executed automatically.
    STATE_BEYOND_SOFT		= 0x04000000,	// This flag indicates the module has reached the soft limit.
						// An emergency stop has been executed automatically.
    STATE_POW_SETUP_ERR		= 0x08000000,	// Error in initializing the current controller.
						// Module settings disacord with controller configuration.
} PowerCubeModuleState;

typedef enum
{
    DIOIO_MOD_INBIT0		= 0x0000001,	// State of input 0.
    DIOIO_MOD_INBIT1		= 0x0000002,	// State of input 1.
    DIOIO_MOD_INBIT2		= 0x0000004,	// State of input 2.
    DIOIO_MOD_INBIT3		= 0x0000008,	// State of input 3.
    DIOIO_MOD_OUTBIT0		= 0x0000010,	// State of output 0.
    DIOIO_MOD_OUTBIT1		= 0x0000020,	// State of output 1.
    DIOIO_MOD_OUTBIT2		= 0x0000040,	// State of output 2.
    DIOIO_MOD_INSWR		= 0x0000100,	// State of Home switch.
    DIOIO_MOD_INSW1		= 0x0000200,	// State of Limit switch 1.
    DIOIO_MOD_INSW2		= 0x0000400,	// State of Limit switch 2.
} PowerCubeDigitalIO;


typedef enum
{
    SETUPID_MOD_ENCODER_FEEDBACK	= 0x00000001,	// not used.
    SETUPID_MOD_RESOLVER_FEEDBACK	= 0x00000002,	// not used.
    SETUPID_MOD_ABSOLUTE_FEEDBACK	= 0x00000004,	// not used.
    SETUPID_MOD_4IN_4OUT		= 0x00000008,	// 1=The 15pole connector is configured for 4 I/O-Signals.
    SETUPID_MOD_3IN_ENCODER_IN		= 0x00000010,	// 1=The 15pole connector is configured for Encoder input.
    SETUPID_MOD_3IN_ENCODER_OUT		= 0x00000020,	// 1=The 15pole connector is configured for Encoder output.
    SETUPID_MOD_RS232			= 0x00000040,	// 1=RS232 communication is active.
    SETUPID_MOD_CAN			= 0x00000200,	// 1=CAN communication is active.
    SETUPID_MOD_PROFIBUS		= 0x00000400,	// 1=Profibus communication is active.
    SETUPID_MOD_USE_M3ID		= 0x00000800,	// 1=CAN identifiers for MoRSE3 are active.
    SETUPID_MOD_USE_M4ID		= 0x00001000,	// 1=CAN identifiers for MoRSE4 are active.
    SETUPID_MOD_USE_CANOPEN		= 0x00002000,	// 1=The CANopen interface is active.
    SETUPID_MOD_USE_SW2_AS_ENABLE	= 0x00008000,	// 1=Input for Limit switch 2 is used as an Enable signal.
    SETUPID_MOD_USE_SW2_AS_BRAKE	= 0x00010000,	// 1=Input for Limit switch 2 is used as Release brake signal.
    SETUPID_MOD_ERROR_TO_OUT0		= 0x00020000,	// 1=An error will be signalized on output 0.
} PowerCubeSetupWord;

typedef enum
{
    CONFIGID_MOD_BRAKE_PRESENT		= 0x00000008,	// 1=Brake is present.
    CONFIGID_MOD_BRAKE_AT_POWERON	= 0x00000010,	// 0=Brake is relaxed on power on.
    CONFIGID_MOD_SWR_WITH_ENCODERZERO	= 0x00000020,	// 1=EncoderIndex signal is used in homing procedure.
    CONFIGID_MOD_SWR_AT_FALLING_EDGE	= 0x00000040,	// 1=Homing on fallinf edge of limit switch.
    CONFIGID_MOD_CHANGE_SWR_TO_LIMIT	= 0x00000080,	// 1=Home switch is limit switch (except during homing).
    CONFIGID_MOD_SWR_ENABLED		= 0x00000100,	// 1=Home switch is enabled.
    CONFIGID_MOD_SWR_LOW_ACTIVE		= 0x00000200,	// 1=Home switch is low active.
    CONFIGID_MOD_SWR_USE_EXTERNAL	= 0x00000400,	// 1=External home switch is used.
    CONFIGID_MOD_SW1_ENABLED		= 0x00000800,	// 1=Limit switch 1 is enabled.
    CONFIGID_MOD_SW1_LOW_ACTIVE		= 0x00001000,	// 1=Limit switch 1 is low active.
    CONFIGID_MOD_SW1_USE_EXTERNAL	= 0x00002000,	// 1=External limit switch 1 is used.
    CONFIGID_MOD_SW2_ENABLED		= 0x00004000,	// 1=Limit switch 2 is enabled.
    CONFIGID_MOD_SW2_LOW_ACTIVE		= 0x00008000,	// 1=Limit switch 2 is low active.
    CONFIGID_MOD_SW2_USE_EXTERNAL	= 0x00010000,	// 1=External limit switch 2 is used.
    CONFIGID_MOD_LINEAR			= 0x00020000,	// 1=Module is a linear type.
    CONFIGID_MOD_ALLOW_FULL_CUR		= 0x00080000,	// 0=Commanded current (PCube_moveCur) is limited to nominal current.
    CONFIGID_MOD_M3_COMPATIBLE		= 0x00100000,	// 1=Module is M3 compatible.
							// This concerns CAN communication and behaviour at PCube_moveStep.
							// Module does not accept motion commands unless sucesfully homed.
    CONFIGID_MOD_LINEAR_SCREW		= 0x00200000,	// 1=Module is linear, driven by ball screw.
    CONFIGID_MOD_DISABLE_ON_HALT	= 0x00800000,	// 1=Motor power disabled in case of error.
    CONFIGID_MOD_WATCHDOG_ENABLE	= 0x01000000,	// 1=Watchdog is enabled.
							// Activated automatically by the first "life sign" of the host control.
    CONFIGID_MOD_ZERO_MOVE_AFTER_HOK	= 0x02000000,	// 1=After Homing the module moves to zero.
    CONFIGID_MOD_DISABLE_ACK		= 0x04000000,	// 1=All acknowledge messages are disabled.
							// All Get commands will still be acknowledged.
							// Valid only for CAN-Bus.
    CONFIGID_MOD_SYNC_MOTION		= 0x08000000,	// 1=Syncronized motion commands enabled.
							// After sending a motion command the drive expects the broadcast
							// PCube_StartMotionAll to start motion. Valid only for CAN-Bus.
} PowerCubeConfigWord;

typedef enum
{
    B1200_MODE				= 0x00,
    B2400_MODE				= 0x01,
    B4800_MODE				= 0x02,
    B9600_MODE				= 0x03,
    B19200_MODE				= 0x04,
    B38400_MODE				= 0x05,
} PowerCubeBaudRate;

#endif    // __POWERCUBE_TELEGRAMDEF_HPP
