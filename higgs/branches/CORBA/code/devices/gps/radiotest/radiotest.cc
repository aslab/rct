/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
/* Program for sending data through the serial port to test the GPSd radio communications.
 * Call minicom on the serial port first to set the transmission parameters, on both the
 * transmitter, which is this program for, and the receiver, which can be read by a 'cat'.
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argv, char * argc[])
{
    FILE * fd = fopen("/dev/ttyS0", "a");
    if (!fd)
	return 1;
    for (unsigned char i = ' ';; i++)
      {
	if (i == '~')
	    i = ' ';
	usleep(1000000);
	fprintf(fd, "%c", i);
	fflush(fd);
      }
    return 0;
}
