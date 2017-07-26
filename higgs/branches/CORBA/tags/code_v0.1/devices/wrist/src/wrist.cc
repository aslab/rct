/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
/* 
 * HOW TO CONTROL THE WRIST
 * 
 * There are two important modes:
 * Ramp:
 * You specify the maximum speed and acceleration an then set the target position, and
 * the powercube performs a trapezoidal control on speed based on the specified speed
 * and acceleration settings.
 * Step:
 * You tell the powercube the position and the time to reach it (not implemented)
 * 
 * MaxCur: This parameter controls the maximum current allowed on the axis. If it is reached
 * the axis is halted and an error is issued.
 * 
 * First send a Reset and Home commands and wait until it finishes, then
 * set parameters and/or issue motion commands.
 */

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "Exception.h"
#include "wrist.h"

// TODO: Isochronous movement in the ramp mode.

#define wrist_axis	higgs::wrist::wrist_axis
#define PITCH		higgs::wrist::PITCH
#define ROLL		higgs::wrist::ROLL
#define BOTH		higgs::wrist::BOTH

#define PITCH_CALIBRATION	0.F
#define ROLL_CALIBRATION	0.04F

wrist_servant::wrist_servant(const char * serial_device)
: device(serial_device)
{
    if(!device.Open())
	error_exception("Could not open serial device.");
    powercube_telegram::device = &device;

    reset();


    // Calibrate.
    set_position(0.F, BOTH);

    // Default values.
    set_max_accel(999.F, BOTH);
    set_max_speed(1.F, BOTH);

    pthread_mutex_init(&powercube_telegram::device_lock, 0);
    powercube_telegram::thread_safe = true;
    if (pthread_create(&supervisor_thread, 0, check_supervisor, this))
	error_exception("Could not create supervisor thread. Aborting.");
}

wrist_servant::~wrist_servant()
{
    powercube_telegram::thread_safe = false;
    pthread_mutex_destroy(&powercube_telegram::device_lock);
    pthread_cancel(supervisor_thread);

    // Try to recover zero position first.
    set_max_accel(1.F, BOTH);
    set_max_speed(2.F, BOTH);
    set_position(0.F, BOTH);
    wait(BOTH);

    reset();
    set_position(0.F, BOTH);
    wait(BOTH);
    TRY;
    powercube_telegram(adr(PITCH) , HALT_CMD).send();
    powercube_telegram(adr(ROLL) , HALT_CMD).send();
    CATCH;
    device.Close();
    powercube_telegram::device = 0;
}

char * wrist_servant::get_full_state(wrist_axis axis)
{
    if (axis != PITCH && axis != ROLL)
	error_exception("Only one axis allowed.");

    typedef std::pair<std::string, std::string> parameter_pair;
    typedef std::vector<parameter_pair> parameter_list;

    parameter_list ret;

    unsigned char  u8;
    //signed   char  s8;
    unsigned short u16;
    signed   short s16;
    unsigned long  u32;
    signed   long  s32;
    float          f;

#define GET_PAR_U8(par) powercube_telegram(adr(axis) , par).receive(&u8); \
      { std::ostringstream stream; stream << (unsigned int)u8;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_S8(par) powercube_telegram(adr(axis) , par).receive(&s8); \
      { std::ostringstream stream; stream << s8;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_U16(par) powercube_telegram(adr(axis) , par).receive(&u16); \
      { std::ostringstream stream; stream << u16;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_S16(par) powercube_telegram(adr(axis) , par).receive(&s16); \
      { std::ostringstream stream; stream << s16;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_U32(par) powercube_telegram(adr(axis) , par).receive(&u32); \
      { std::ostringstream stream; stream << u32;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_S32(par) powercube_telegram(adr(axis) , par).receive(&s32); \
      { std::ostringstream stream; stream << s32;\
	ret.push_back(parameter_pair(#par, stream.str()));}
#define GET_PAR_F(par) powercube_telegram(adr(axis) , par).receive(&f); \
      { std::ostringstream stream; stream << f;\
	ret.push_back(parameter_pair(#par, stream.str()));}

    TRY;
    GET_PAR_F(DefHomeOffset);
    GET_PAR_F(DefGearRatio);
    GET_PAR_F(DefLinRatio);
    GET_PAR_F(DefMinPos);
    GET_PAR_F(DefMaxPos);
    GET_PAR_F(DefMaxDeltaPos);
    //GET_PAR_F(DefMaxDeltaVel);
    GET_PAR_F(DefTorqueRatio);
    GET_PAR_F(DefCurRatio);
    //GET_PAR_F(DefMinVel);
    GET_PAR_F(DefMaxVel);
    //GET_PAR_F(DefMinAcc);
    GET_PAR_F(DefMaxAcc);
    //GET_PAR_F(DefMinCur);
    GET_PAR_F(DefMaxCur);
    GET_PAR_F(DefHomeVel);
    GET_PAR_F(DefHomeAcc);
    GET_PAR_U32(DefCubeSerial);
    GET_PAR_U32(DefConfig);
    GET_PAR_U32(DefPulsesPerTurn);
    GET_PAR_U16(DefCubeVersion);
    //GET_PAR_U16(DefServiceInterval);
    GET_PAR_U16(DefBrakeTimeOut);
    GET_PAR_U8(DefAddress);
    GET_PAR_U8(DefPrimBaud);
    GET_PAR_U8(DefSecBaud);
    GET_PAR_S32(PosCount);
    GET_PAR_S32(RefPosCount);
    GET_PAR_U32(DIoSetup);
    GET_PAR_U32(CubeState);
    GET_PAR_U32(TargetPosInc);
    GET_PAR_U32(TargetVelInc);
    GET_PAR_U32(TargetAccInc);
    GET_PAR_U32(StepInc);
    GET_PAR_S32(HomeOffsetInc);
    GET_PAR_S16(RawCur);
    GET_PAR_S32(HomeToZeroInc);
    GET_PAR_U32(Config);
    GET_PAR_U8(MoveMode);
    GET_PAR_F(IncRatio);
    GET_PAR_F(ActPos);
    GET_PAR_F(ActPos_);
    GET_PAR_F(IPolPos);
    GET_PAR_F(DeltaPos);
    GET_PAR_F(MaxDeltaPos);
    GET_PAR_F(ActVel);
    GET_PAR_F(IPolVel);
    GET_PAR_F(MinPos);
    GET_PAR_F(MaxPos);
    GET_PAR_F(MaxVel);
    GET_PAR_F(MaxAcc);
    GET_PAR_F(MaxCur);
    GET_PAR_F(Cur);
    GET_PAR_S16(DefC0);
    GET_PAR_S16(DefDamp);
    //GET_PAR_S16(DefA0);
    GET_PAR_S16(ActC0);
    GET_PAR_S16(ActDamp);
    GET_PAR_S16(ActA0);
    //GET_PAR_F(DefBurnCount);
    GET_PAR_U32(Setup);
    GET_PAR_F(HomeOffset);

    CATCH;

    string ret_s;
    for (parameter_list::iterator i = ret.begin(); i != ret.end(); i++)
      {
	std::string title_space(20 - i->first.length(), ' ');
	ret_s += i->first + ": " + title_space + i->second + "\n";
      }

    return CORBA::string_dup(ret_s.c_str());
}

char * wrist_servant::get_status(wrist_axis axis)
{
    if (axis != PITCH && axis != ROLL)
	error_exception("Only one axis allowed.");

    typedef std::pair<std::string, std::string> parameter_pair;
    typedef std::vector<parameter_pair> parameter_list;

    parameter_list ret;

    PowerCubeModuleState state = cube_state(axis);

    TRY;

#define PRINT_STATUS(X)	if (state & X) ret.push_back(parameter_pair(#X, ""));
    PRINT_STATUS(STATE_ERROR);
    PRINT_STATUS(STATE_HOME_OK);
    PRINT_STATUS(STATE_HALTED);
    PRINT_STATUS(STATE_POWERFAULT);
    PRINT_STATUS(STATE_TOW_ERROR);
    PRINT_STATUS(STATE_COMM_ERROR);
    PRINT_STATUS(STATE_SWR);
    PRINT_STATUS(STATE_SW1);
    PRINT_STATUS(STATE_SW2);
    PRINT_STATUS(STATE_BRAKEACTIVE);
    PRINT_STATUS(STATE_CURLIMIT);
    PRINT_STATUS(STATE_MOTION);
    PRINT_STATUS(STATE_RAMP_ACC);
    PRINT_STATUS(STATE_RAMP_STEADY);
    PRINT_STATUS(STATE_RAMP_DEC);
    PRINT_STATUS(STATE_RAMP_END);
    PRINT_STATUS(STATE_INPROGRESS);
    PRINT_STATUS(STATE_FULLBUFFER);
    PRINT_STATUS(STATE_POW_VOLT_ERR);
    PRINT_STATUS(STATE_POW_FET_TEMP);
    PRINT_STATUS(STATE_POW_WDG_TEMP);
    PRINT_STATUS(STATE_POW_SHORCUR);
    PRINT_STATUS(STATE_POW_HALLERR);
    PRINT_STATUS(STATE_POW_INTEGRALERR);
    PRINT_STATUS(STATE_CPU_OVERLOAD);
    PRINT_STATUS(STATE_BEYOND_HARD);
    PRINT_STATUS(STATE_BEYOND_SOFT);
    PRINT_STATUS(STATE_POW_SETUP_ERR);

    CATCH;

    string ret_s;
    for (parameter_list::iterator i = ret.begin(); i != ret.end(); i++)
      {
	std::string title_space(20 - i->first.length(), ' ');
	ret_s += i->first + ": " + title_space + i->second + "\n";
      }

    return CORBA::string_dup(ret_s.c_str());
}

void wrist_servant::set_max_accel(CORBA::Float accel, wrist_axis axis)
{
    TRY;
    if (axis == BOTH || axis == PITCH)
      {
	powercube_telegram(adr(PITCH) , TargetAcc).send(accel);
	max_accel_pitch = accel;
      }
    if (axis == BOTH || axis == ROLL)
      {
	powercube_telegram(adr(ROLL) , TargetAcc).send(accel);
	max_accel_roll = accel;
      }
    CATCH;
}

void wrist_servant::set_max_speed(CORBA::Float speed, wrist_axis axis)
{
    TRY;
    if (axis == BOTH || axis == PITCH)
      {
	powercube_telegram(adr(PITCH) , TargetVel).send(speed);
	max_speed_pitch = speed;
      }
    if (axis == BOTH || axis == ROLL)
      {
	powercube_telegram(adr(ROLL) , TargetVel).send(speed);
	max_speed_roll = speed;
      }
    CATCH;
}

void wrist_servant::set_position(CORBA::Float position, wrist_axis axis)
{
    TRY;
    if (axis == BOTH || axis == PITCH)
      {
	if (position > 1.6F) position_pitch = 1.6F;
	else if (position < -1.7F) position_pitch = -1.7F;
	else position_pitch = position;
	powercube_telegram(adr(PITCH) , FRAMP_MODE).send(position_pitch + PITCH_CALIBRATION);
      }
    if (axis == BOTH || axis == ROLL)
      {
	if (position > 3.9F) position_roll = 3.9F;
	else if (position < -3.9F) position_roll = -3.9F;
	else position_roll = position;
	powercube_telegram(adr(ROLL) , FRAMP_MODE).send(position_roll + ROLL_CALIBRATION);
      }
    CATCH;
}


void wrist_servant::set_diff_position(CORBA::Float diff, wrist_axis axis)
{
    TRY;
    if (axis == BOTH || axis == PITCH)
      {
	position_pitch += diff;
	set_position(position_pitch, PITCH);
      }
    if (axis == BOTH || axis == ROLL)
      {
	position_roll += diff;
	set_position(position_roll, ROLL);
      }
    CATCH;
}


CORBA::Float wrist_servant::get_position(wrist_axis axis)
{
    if (axis == BOTH)
	throw 0;

    CORBA::Float ret;
    TRY;
    powercube_telegram(adr(axis) , ActPos).receive(&ret);
    CATCH;

    if (axis == PITCH)
	ret -= PITCH_CALIBRATION;
    else
	ret -= ROLL_CALIBRATION;

    return ret;
}

CORBA::Float wrist_servant::get_speed(wrist_axis axis)
{
    if (axis == BOTH)
	throw 0;
    CORBA::Float ret;
    TRY;
    powercube_telegram(adr(axis) , ActVel).receive(&ret);
    CATCH;
    return ret;
}

CORBA::Float wrist_servant::get_current(wrist_axis axis)
{
    if (axis == BOTH)
	throw 0;
    CORBA::Float ret;
    TRY;
    powercube_telegram(adr(axis) , Cur).receive(&ret);
    CATCH;
    return ret;
}


CORBA::Boolean wrist_servant::is_ready(wrist_axis axis)
{
    if (axis == BOTH)
	return is_ready(PITCH) && is_ready(ROLL);

    PowerCubeModuleState state = cube_state(axis);
    return !(state & STATE_MOTION);
}

void wrist_servant::wait(wrist_axis axis)
{
    while (!is_ready(axis))
	;
}

void wrist_servant::reset()
{
    powercube_telegram(adr(PITCH) , RESET_CMD).send();
    powercube_telegram(adr(ROLL) , RESET_CMD).send();
    powercube_telegram(adr(PITCH) , HOME_CMD).send();
    powercube_telegram(adr(ROLL) , HOME_CMD).send();

    wait(BOTH);

    set_max_speed(max_speed_pitch, PITCH);
    set_max_accel(max_accel_pitch, PITCH);
    set_max_speed(max_speed_roll, ROLL);
    set_max_accel(max_accel_roll, ROLL);
}

PowerCubeModuleState wrist_servant::cube_state(wrist_axis axis)
{
    if (axis != PITCH && axis != ROLL)
	error_exception("Only one axis allowed.");

    unsigned long state;
    TRY;
    powercube_telegram(adr(axis) , CubeState).receive(&state);
    CATCH;
    return (PowerCubeModuleState)state;
}

// Helper function for mapping the IDL wrist axis to the powercube device.
// Gets the enum value and returns the powercube's axis numeric address.
int wrist_servant::adr(wrist_axis axis)
{
    switch (axis)
      {
	case PITCH:
	    return POWERCUBE_PITCH;
	case ROLL:
	    return POWERCUBE_ROLL;
	default:
	    throw 0;
      }
}

// Function that runs in a thread and if detects an error it resets
// that axis.
void * wrist_servant::check_supervisor(void * arg)
{
    TRY;
    wrist_servant * this_ = (wrist_servant *) arg;
    PowerCubeModuleState state;
    for (;;)
      {
	sleep(3);

	this_->get_position(ROLL);
	state = this_->cube_state(PITCH);
	if (state & STATE_POW_VOLT_ERR)
	    error_exception("Power error! Check voltage is over 22V and under 27V.");
	if (state & STATE_ERROR)
	    this_->reset();

	this_->get_position(ROLL);
	state = this_->cube_state(PITCH);
	if (state & STATE_POW_VOLT_ERR)
	    error_exception("Power error! Check voltage is over 22V and under 27V.");
	if (state & STATE_ERROR)
	    this_->reset();

      }
    CATCH;
}

// Default values.
float wrist_servant::max_speed_pitch = 0.5;
float wrist_servant::max_accel_pitch = 0.5;
float wrist_servant::max_speed_roll = 0.5;
float wrist_servant::max_accel_roll = 0.5;

