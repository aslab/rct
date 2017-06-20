/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <pthread.h>


#include "powercube_telegram.h"

#define	STX	0x02
#define	ETX	0x03


/*************************************************************************/
/** \class powercube_telegram
 * Constructs the telegrams and sends these commands to the powercube.
 *
 *  Motion modes not implemented:
 *
 *  \c I*, \c *_ACK
 *
 *  Commands not implemented:
 *
 *  \c SET_I_STEP_CMD
 *
 *  There are some parameters that are not supported by
 *  the powercube, like DefMinCur.
 *
 *  All send/receive methods raise exceptions if the arguments are
 *  not adequate or there are problems with the communication. They also
 *  block the process until the communication protocol via the RS-232 port
 *  has ended.
 *
 * \warning Do not forget to set \c device before sending/receiving telegrams
 * 	and initializing mutex if you set thread_safe!
 */
/*************************************************************************/

/** Constructor for basic commands.
 *
 * \param address The address of the axis to which this command must be sent.
 * \param cmd The command. Valid values are
 *  - \c RESET_CMD
 *  - \c HOME_CMD
 *  - \c HALT_CMD
 *  - \c PIDPARAM_CMD
 */
powercube_telegram::powercube_telegram(int address, PowerCubeCommand cmd)
: cmd(cmd), par((PowerCubeParameter)0), mot((PowerCubeMotion)0), address(address)
{
    assert_exception(cmd != SET_EXTENDED_CMD && cmd != GET_EXTENDED_CMD && cmd != SET_MOTION_CMD);
    check_environment();
}

/** Constructor for getting or setting parameters.
 *
 * \param address The address of the axis to which this command must be sent.
 * \param par The parameter to be fetched/set. Valid values are the Parameter ID's
 * 	found in the document <em>Data exchange with PowerCube.pdf</em> and in the
 * 	structure \c PowerCubeParameter. FIXME: Make it a link in doxygen.
 * \param write \c true if this telegram will be used to set the parameter, \c false
 * 	if you want to read it.
 */
powercube_telegram::powercube_telegram(int address, PowerCubeParameter par)
: cmd(SET_EXTENDED_CMD), par(par),
    mot((PowerCubeMotion)0), address(address)
{
    check_environment();
}

/** Constructor for motion commands.
 *
 * \param address The address of the axis to which this command must be sent.
 * \param mot The motion command. Valid values are the Motion ID's
 * 	found in the document <em>Data exchange with PowerCube.pdf</em> and in the
 * 	structure \c PowerCubeMotion. FIXME: Make it a link in doxygen.
 */
powercube_telegram::powercube_telegram(int address, PowerCubeMotion mot)
: cmd(SET_MOTION_CMD), par((PowerCubeParameter)0), mot(mot), address(address)
{
    check_environment();
}

/** Transmit the telegram.
*/
void powercube_telegram::send()
{
    assert_exception(
	    cmd == RESET_CMD ||
	    cmd == HOME_CMD ||
	    cmd == HALT_CMD ||
	    cmd == PIDPARAM_CMD );
    send_and_receive(0,0,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(signed char arg)
{
    assert_exception(0);
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,1,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(unsigned char arg)
{
    assert_exception(0);
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,1,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(signed short arg)
{
    if (cmd == GET_EXTENDED_CMD)
	cmd = SET_EXTENDED_CMD;
    assert_exception(
	    cmd == SET_EXTENDED_CMD && (
		par == RawCur ||
		par == ActC0 ||
		par == ActDamp ||
		par == ActA0 ) );
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,2,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(unsigned short arg)
{
    assert_exception(0);
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,2,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(signed long arg)
{
    assert_exception(0);
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,4,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(unsigned long arg)
{
    if (cmd == GET_EXTENDED_CMD)
	cmd = SET_EXTENDED_CMD;
    assert_exception(
	    cmd == SET_EXTENDED_CMD && (
		par == DIoSetup ||
		par == TargetPosInc ||
		par == TargetVelInc ||
		par == TargetAccInc ||
		par == Config ) );
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,4,0,0);
}

/** Transmit the telegram.
 * \param arg Use this value as parameter.
 */
void powercube_telegram::send(float arg)
{
    if (cmd == GET_EXTENDED_CMD)
	cmd = SET_EXTENDED_CMD;
    assert_exception( (
		cmd == SET_EXTENDED_CMD && (
		    par == MaxDeltaPos ||
		    par == MinPos ||
		    par == MaxPos ||
		    par == MaxVel ||
		    par == MaxAcc ||
		    par == MaxCur ||
		    par == Cur ||
		    par == TargetPos ||
		    par == TargetVel ||
		    par == TargetAcc ||
		    par == HomeOffset ) )
	    || (
		cmd == SET_MOTION_CMD && (
		    mot == FRAMP_MODE ||
		    mot == FVEL_MODE ||
		    mot == FCUR_MODE ) ) );
    unsigned char *parg = (unsigned char *)&arg;
    send_and_receive(parg,4,0,0);
}

/** Transmit the telegram.
 * Only for FSTEP_MODE motion commands.
 * \param target_pos Desired position.
 * \param time_ms Time to reach the desired position, in milliseconds.
 */
void powercube_telegram::send(float target_pos, unsigned short time_ms)
{
    assert_exception( cmd == SET_MOTION_CMD && mot == FSTEP_MODE);
    unsigned char * c_target = (unsigned char *) &target_pos;
    unsigned char * c_time   = (unsigned char *) &time_ms;
    unsigned char parg[6];
    parg[0] = c_target[0];
    parg[1] = c_target[1];
    parg[2] = c_target[2];
    parg[3] = c_target[3];
    parg[4] = c_time[0];
    parg[5] = c_time[1];
    send_and_receive(parg,6,0,0);
}


/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(signed char * arg)
{
    assert_exception(0);
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,1,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(unsigned char * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == DefAddress ||
		par == DefPrimBaud ||
		par == DefSecBaud ||
		par == MoveMode ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,1,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(signed short * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == RawCur ||
		par == DefC0 ||
		par == DefDamp ||
		par == ActC0 ||
		par == ActDamp ||
		par == ActA0 ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,2,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(unsigned short * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == DefCubeVersion ||
		//par == DefServiceInterval ||
		par == DefBrakeTimeOut ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,2,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(signed long * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == PosCount ||
		par == RefPosCount ||
		par == HomeOffsetInc ||
		par == HomeToZeroInc ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,4,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(unsigned long * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == DefCubeSerial ||
		par == DefConfig ||
		par == DefPulsesPerTurn ||
		par == DIoSetup ||
		par == CubeState ||
		par == TargetPosInc ||
		par == TargetVelInc ||
		par == TargetAccInc ||
		par == StepInc ||
		par == Config ||
		par == Setup ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,4,false);
}

/** Get the parameter.
 * \param arg Variable to store the fetched parameter.
 */
void powercube_telegram::receive(float * arg)
{
    if (cmd == SET_EXTENDED_CMD)
	cmd = GET_EXTENDED_CMD;
    assert_exception(
	    cmd == GET_EXTENDED_CMD && (
		par == DefHomeOffset ||
		par == DefGearRatio ||
		par == DefLinRatio ||
		par == DefMinPos ||
		par == DefMaxPos ||
		par == DefMaxDeltaPos ||
		//par == DefMaxDeltaVel ||
		par == DefTorqueRatio ||
		par == DefCurRatio ||
		//par == DefMinVel ||
		par == DefMaxVel ||
		//par == DefMinAcc ||
		par == DefMaxAcc ||
		//par == DefMinCur ||
		par == DefMaxCur ||
		par == DefHomeVel ||
		par == DefHomeAcc ||
		par == IncRatio ||
		par == ActPos ||
		par == ActPos_ ||
		par == IPolPos ||
		par == DeltaPos ||
		par == MaxDeltaPos ||
		par == ActVel ||
		par == IPolVel ||
		par == MinPos ||
		par == MaxPos ||
		par == MaxVel ||
		par == MaxAcc ||
		par == MaxCur ||
		par == Cur ||
		par == HomeOffset ) );
    unsigned char *parg = (unsigned char *)arg;
    send_and_receive(0,0,parg,4,false);
}

/**
 * The serial port. Make sure it is open before sending or receiving telegrams.
 * The device is common to all powercube_telegram objects.
 * \warning Do not forget to set it before transmitting telegrams!
 */
SerialLinkRS232 * powercube_telegram::device = 0;

/**
 * Set to true to use the mutex when accessing the serial port. Allows for
 * telegrams to be correctly sent and confirmed from various threads.
 */
bool powercube_telegram::thread_safe = false;

/**
 * The mutex to use when sending telegrams from various threads at the same time.
 * \warning Do not forget to set it if thread_safe is true!
 */
pthread_mutex_t powercube_telegram::device_lock = pthread_mutex_t();

// Proxy method for using mutexes.
void powercube_telegram::send_and_receive(const unsigned char arg_send[6], int arg_size_send,
	unsigned char arg_receive[6], int arg_size_receive, bool only_ack_check_receive)
{
    if (thread_safe)
	pthread_mutex_lock(&device_lock);
    send(arg_send, arg_size_send);
    receive(arg_receive, arg_size_receive, only_ack_check_receive);
    if (thread_safe)
	pthread_mutex_unlock(&device_lock);
}

/*
 * Assembles the identifier and sends it through the serial device.
 * If failes, it retries. If it keeps failing, it raises an exception.
 */
void powercube_telegram::send(const unsigned char arg[6], int arg_size)
{
    unsigned char telegram[22];
    int telegram_length = assemble_identifier(arg, arg_size, telegram);

    // Send it.
    int i;
    for (i = 0; i < 10; i++)
	if (device->Send(telegram, telegram_length))
	    break;
    if (i == 10)
	error_exception("Could not send telegram.");
    device->EmptyBuffers();
}

/* Waits until a telegram is received and checks it is correctly formed or the timeout expires.
 * if only_ack_check is false, it also assigns arg.
 * The receive and send methods check for valid arguments.
 */
void powercube_telegram::receive(unsigned char arg[6], int arg_size, bool only_ack_check)
{
    unsigned char ack[22];
    memset(ack, 0, 22);
    int ack_length = 0;
    for (;;)
      {
	if (!device->Receive(&ack[ack_length], 1) || ack_length >= 25)
	    error_exception("Ack telegram not received.");
	if (ack[ack_length] == ETX)
	  {
	    ack_length++;
	    break;
	  }
	if (ack[0] == STX)
	    ack_length++;
      }

    // It is not checked further because it is too complex and the received
    // BCC is sometimes not as expected.
    if (only_ack_check)
	return;

    // Only data is received with the command GET_EXTENDED_CMD.
    unsigned char identifier[11];
    unDLE(ack + 1, ack_length - 2, identifier);
    for (int i = 0; i < arg_size; i++)
      {
	arg[i] = identifier[4 + i];
      }
}

// Total: 1 STX, 2..16 Identifier, 1 ETX.
// Returns bytes used in dest.
int powercube_telegram::assemble_identifier(const unsigned char arg[6], int arg_size, unsigned char dest[22], bool recv)
{
    assert_exception(arg_size <= 6);
    bool additional_param =
	(cmd == SET_EXTENDED_CMD || cmd == GET_EXTENDED_CMD || cmd == SET_MOTION_CMD);

    int TELID_len = 1 + (additional_param ? 1 : 0) + arg_size;
    unsigned char telegram[13]; // 1 STX, 3..11 Identifier, 1 ETX.
    int i = 0; // Keeps the length written so far of the telegram.

    /***** Assemble telegram (identifier). *****/
    // STX
    dest[i++] = STX;
    // TELID. Contains axis' address and length of data.
    telegram[i++] = (unsigned char)( ((address >> 3) & 0x03) | (recv ? 0x08 : 0x04) );
    telegram[i++] = (unsigned char)( ((address << 5) & 0xE0) | (TELID_len & 0x0F) );
    // DATA
    telegram[i++] = cmd;
    if (additional_param)
	telegram[i++] = (cmd == SET_MOTION_CMD ? (unsigned char)mot : (unsigned char)par);
    for (int j = 0; j < arg_size; j++)
	telegram[i++] = arg[j];
    // BCC
    telegram[i] = (unsigned char)(BCC(telegram + 1, i - 1) & 0xFF); i++;
    assert_exception(i <= 12);
    // DLE filter.
    i = 1 + DLE(telegram + 1, i - 1, dest + 1);
    // And finish with ETX.
    dest[i++] = ETX;

    return i;
}


/*
 * Performs the DLE conversion as detailed in <em>Data exchange with PowerCube.pdf</em>.
 * Identifier: 2->2 TELID, 1->2 cmd, 0..1->0..2 par/mot, 0..6->0..12 Data, 1->1..2 BCC.
 * Total: 1->1 STX, 2..11->2..20 Identifier, 1->1 ETX. (Only identifier should be passed.)
 * Returns bytes used in dest.
 */
int powercube_telegram::DLE(const unsigned char orig[11], int orig_size, unsigned char dest[20])
{
    int i, j; // i = index for orig, j = index for dest.
    for (i = 0, j = 0; i < orig_size; i++, j++)
      {
	if (orig[i] == 0x02 || orig[i] == 0x03 || orig[i] == 0x10)
	  {
	    dest[j] = 0x10;
	    j++;
	    dest[j] = orig[i] + 0x80;
	  }
	else
	    dest[j] = orig[i];
      }
    return j;
}

/*
 * Performs the DLE inverse conversion as detailed in <em>Data exchange with PowerCube.pdf</em>.
 * Identifier: 2->2 TELID, 1->2 cmd, 0..1->0..2 par/mot, 0..6->0..12 Data, 1->1..2 BCC.
 * Total: 1->1 STX, 2..11->2..20 Identifier, 1->1 ETX. (Only identifier should be passed.)
 * Returns bytes used in dest.
 */
int powercube_telegram::unDLE(const unsigned char orig[20], int orig_size, unsigned char dest[11])
{
    int i, j; // i = index for orig, j = index for dest.
    for (i = 0, j = 0; i < orig_size; i++, j++)
      {
	if (orig[i] == 0x10)
	  {
	    i++;
	    dest[j] = orig[i] - 0x80;
	    assert_exception(orig[i] != 0x02 && orig[i] != 0x03 && orig[i] != 0x10);
	  }
	else
	    dest[j] = orig[i];
      }
    return j;
}


// Identifier w/o BCC: 2 TELID, 1 cmd, 0..1 par/mot, 0..6 Data.
unsigned char powercube_telegram::BCC(unsigned char string[10], int string_size)
{
    assert_exception(string_size <= 10);
    unsigned short sum = 0;
    while (string_size--)
      {
	sum += *string++;
	if (sum >= 256)
	    sum -= 255;
      }
    return sum;
}

// Checks the cpu target complies with the byte sizes
// as required by <em>Data exchange with PowerCube.pdf</em>
// In case some of these checks fail, the type should be changed
// in all the source of the powercube_telegram class.
void powercube_telegram::check_environment()
{
    assert_exception(sizeof(unsigned char)	== 1);
    assert_exception(sizeof(signed char)	== 1);
    assert_exception(sizeof(unsigned short)	== 2);
    assert_exception(sizeof(signed short)	== 2);
    assert_exception(sizeof(unsigned long)	== 4);
    assert_exception(sizeof(signed long)	== 4);
    assert_exception(sizeof(float)		== 4);
}

