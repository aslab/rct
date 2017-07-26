/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <iostream>

#include "CosNamingC.h"

#include "gps.h"
#include "../../../lib/CORBA_utils.h"

//#define SERIAL_DEVICE "/etc/higgs/devices/gps_dev"
#define SERIAL_DEVICE "/dev/ttyS0"

using namespace std;

int main(int argc, char* argv[])
{
    CORBA_BEGIN_SERVER(argc, argv);

    GPS_impl gps(SERIAL_DEVICE);
    higgs::GPS_var gps_var = gps._this();

    CORBA_REGISTER_REFERENCE(gps_var, "GPS");

    // Accept requests
    cout << "GPS server Ready !!" << endl;
    CORBA_END_SERVER;


    return 0;


}
