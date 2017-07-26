// Created on: November 2010
// Last Change: Fri Feb 25 03:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Declaration of the telegram class.
 *
 * This class builds and disassembles the packets sent and received in raw format
 * to and from the powercube.
 */
#ifndef __POWERCUBE_TELEGRAM_HPP
#define __POWERCUBE_TELEGRAM_HPP

#include <string>

#include "Exception.h"
#include "SerialLinkRS232.h"
#include "powercube_telegram_def.h"

class powercube_telegram
{
    public:
	powercube_telegram(int address, PowerCubeCommand cmd);
	powercube_telegram(int address, PowerCubeParameter par);
	powercube_telegram(int address, PowerCubeMotion mot);

	void send();
	void send(signed char arg);
	void send(unsigned char arg);
	void send(signed short arg);
	void send(unsigned short arg);
	void send(signed long arg);
	void send(unsigned long arg);
	void send(float arg);
	void send(float target_pos, unsigned short time_ms);

	void receive(signed char * arg);
	void receive(unsigned char * arg);
	void receive(signed short * arg);
	void receive(unsigned short * arg);
	void receive(signed long * arg);
	void receive(unsigned long * arg);
	void receive(float * arg);

	// In case multiple axis with different serial ports are used, change these next
	// two lines with an array, with the index indicating the address of the axis controlled.
	// These three variables must me initialized from the caller.
	static SerialLinkRS232 * device;
	static pthread_mutex_t device_lock;
	static bool thread_safe;

    private:
	PowerCubeCommand cmd;
	const PowerCubeParameter par;
	const PowerCubeMotion mot;

	const int address;

	void send_and_receive(const unsigned char arg_send[6], int arg_size_send,
		unsigned char arg_receive[6], int arg_size_receive, bool only_ack_check_receive = true);
	void send(const unsigned char arg[6], int arg_size);
	void receive(unsigned char arg[6], int arg_size, bool only_ack_check = true);

	int  assemble_identifier(const unsigned char arg[6], int arg_size, unsigned char dest[22], bool recv = false);

	int DLE  (const unsigned char orig[11], int orig_size, unsigned char dest[20]);
	int unDLE(const unsigned char orig[20], int orig_size, unsigned char dest[11]);

	unsigned char BCC(unsigned char string[8], int string_size);

	void check_environment();
};


#endif // POWERCUBE_TELEGRAM_HPP

