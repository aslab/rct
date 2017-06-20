#ifndef __SerialLinkRS232_HPP
#define __SerialLinkRS232_HPP

#include <termios.h>

class SerialLinkRS232
{
	private :
		int fd;
		// Structure defined in /bits/termios.h
		struct termios newtio;
		char * device;

	public :
		SerialLinkRS232(const char * dev);
		~SerialLinkRS232();
		bool Open(unsigned int speed = B9600);
		void Close();
		bool Send(unsigned char * data,size_t size);
		bool Receive(unsigned char * data, size_t size, unsigned short timeout = 50);
		bool EmptyBuffers();

		
		bool isOpen() {return fd>=0;} ///< If Open has been called already.
		bool WaitData(size_t millisec = 100);
};	


#endif // SerialLinkRS232_H
