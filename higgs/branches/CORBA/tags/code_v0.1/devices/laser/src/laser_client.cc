/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <iostream>
#include "laserC.h"
#include "CosNamingC.h"
#include "../../../lib/CORBA_utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    CORBA_BEGIN_CLIENT(argc, argv);
    CORBA_GET_REFERENCE(higgs::laser, laser, "LASCOR");

    higgs::laser_data_var data = laser->get_data();
    cout << "Received " << data->length() << " readings." << endl;
    for (CORBA::ULong i = 0; i < data->length(); i++)
	cout << data[i].angle*180.f/3.141592654f << "º\t" << data[i].distance << "m" << endl;

    CORBA_END_CLIENT;
    return 0;
}





