// Created on: Spring 2010
// Last Change: Fri Feb 25 01:00 PM 2011 C
/**
 * Modified by:
 * \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Library for controlling the Laser SICK
 *
 * Original code:
 * Contributed by Paloma de la Puente del grupo de Robótica Móvil.
 */
#ifndef __PORT_HH
#define __PORT_HH


#ifdef WIN32
	#include<windows.h>
#else

#endif


//CONFIGURATION PARAMETERS
#define PORT_COMMS_INTERVAL_TIMEOUT			150	//millisecs
#define PORT_COMMS_TOTAL_TIMEOUT_MULTIPLIER 150	//millisecs
#define PORT_COMMS_TOTAL_TIMEOUT_CONSTANT	0   //millisecs
	

//ERROR CODES
#define PORT_OK 0
#define PORT_ERROR -1
#define PORT_ERROR_CREATEFILE		-101
#define PORT_ERROR_SETDCB			-102
#define PORT_ERROR_WRITEFILE		-103 
#define PORT_ERROR_WRITENUM			-104 
#define PORT_ERROR_READFILE			-105
#define PORT_ERROR_READNUM			-106
#define PORT_ERROR_CLOSE_HANDLE		-107
#define PORT_ERROR_BAD_PARAMETER	-108
#define PORT_ERROR_TIMEOUT			-109


class PortCOM
{	
public:
	PortCOM();
	int Init(const char device[]);  
	void Close();
	int SetBaud(int baud);
	int Receive(int num,unsigned char* cade);
	int Send(int num,unsigned char* cade);
	
protected:

#ifdef WIN32
	DCB dcb;
	HANDLE  idCom;
	COMMTIMEOUTS timeouts;
#else
	  int serialPort;
#endif
};
    

#endif /*PORT*/
