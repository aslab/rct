/*
 * Modified by:
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
/*
   Sick module for Cycab Development Kit
   Copyright (C) C. Pradalier and C. Braillon, INRIA Rhone-Alpes

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later
   version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
   MA  02110-1301  USA

   INRIA Rhone-Alpes, hereby disclaims all copyright interest in
   the program
   */

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "SerialLinkRS232.h"

//#define TRACE


/** \class SerialLinkRS232
 * \brief Manages connections of RS-232 serial ports.
 *
 * Any standard speed is allowed (see termios.h). 8 data bits, 1 stop bit. No handshake.
 *
 * \bug There is no check for connectivity once the port is opened.
 */




/** Constructor.
 *
 * \param dev Filename of the device. It must be a valid RS-232 device file.
 */
SerialLinkRS232::SerialLinkRS232(const char * dev)
{
    device = strdup(dev); // FIXME: use new and delete.
    fd = -1;
}

SerialLinkRS232::~SerialLinkRS232()
{
    Close();
    free(device); // FIXME: use new and delete.
}

/** Opens the serial device and configures it.
 *
 * \warning You must call this method before sending or receiving!
 * 	Otherwise the other methods will not work.
 *
 * If it is already opened, it first closes the old serial device.
 *
 * \param speed Values accepted include B9600. Other values in termios.h
 * \return True if operation was successful.
 */
bool SerialLinkRS232::Open(unsigned int speed)
{
    if (isOpen())
	    Close();

    fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY); // | O_NDELAY
    if (fd < 0)
      {
	fd = -1;
	return false;
      }

    cfmakeraw (&newtio);
    tcgetattr(fd, &newtio);
    cfsetospeed(&newtio,(speed));
    cfsetispeed(&newtio,(speed));
    tcflush(fd, TCIFLUSH);
    newtio.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    newtio.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    newtio.c_cflag |= (CLOCAL | CREAD);
    newtio.c_cflag &= ~(CSIZE | PARENB | CRTSCTS); /* Mask the character size bits */
    newtio.c_cflag |= CS8; /* Select 8 data bits */ 
    newtio.c_oflag &= ~(OPOST);
    newtio.c_cc[VTIME]=0;
    newtio.c_cc[VMIN]=0;
    tcsetattr(fd,TCSANOW,&newtio);

    return true;
}

/** Closes the link.
 * This method is automatically called when destroying the instance.
 */
void SerialLinkRS232::Close()
{
    if (fd != -1)
	close(fd);
    fd = -1;
}

/** Transmit data.
 *
 * No bytes are buffered. This method returns inmediately without waiting
 * for the data being actually sent.
 *
 * \param data Arbitrary data in binary form.
 * \param size Length in bytes of \c data.
 * \return Returns true of all bytes have been successfully queued for transmission.
 */
bool SerialLinkRS232::Send(unsigned char * data,size_t size)
{
    if (fd == -1)
	return false;
    size_t wes = write(fd,data,size);
    return (wes == size);
}

/** Receive data.
 *
 * Blocks until all characters are read.
 *
 * \param data Buffer to store the data to. It must big enough to hold \c size bytes.
 * \param size Number of bytes expected to be read.
 * \param timeout Maximum time to wait for the data to be read, in milliseconds.
 * \return If all \c size bytes could be read.
 */
bool SerialLinkRS232::Receive(unsigned char * data, size_t size, unsigned short timeout)
{
    if (fd == -1)
	return false;

    unsigned int count = 0;
    int w = -1;
    while (count < size)
      {
	if (w == -1)
	  {
	    if (!WaitData(timeout)) 
		break;
	  }
	w = read(fd, &(data[count]), size - count);
	count += w;
      }
    return (count == size);
}

/**
 * Destroys all unread bytes in the input buffer and then
 * blocks the current thread until all bytes in the output buffer
 * have been effectively transmited.
 *
 * Can be used to reset all buffers for a new clean communication session,
 * or if you read all input data before, wait until all output data has been
 * sent without loosing information.
 */
bool SerialLinkRS232::EmptyBuffers()
{
    if (fd < 0)
	return false;
    tcdrain(fd);
    tcflush(fd, TCIFLUSH);
    return true;
}


/** Blocks until Rx buffer is not empty.
 * Waits until data is available for reading on the link up to the maximum time specified.
 * 
 * \param millisec Maximum time to wait for data, in milliseconds.
 * \return \c true if there is data to be read. \c false if the timeout has expired.
 */
bool SerialLinkRS232::WaitData(size_t millisec)
{
    if (fd < 0)
	return false;
    fd_set rfs;
    struct timeval to = {0,0};
    to.tv_usec = (millisec%1000) * 1000;
    to.tv_sec = millisec / 1000;
    FD_ZERO(&rfs);FD_SET(fd,&rfs);
    int r = select(fd+1,&rfs,NULL,NULL,&to);
    return (r >= 1);
}


