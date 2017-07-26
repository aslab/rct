// Created on: Spring 2010
// Last Change: Fri Feb 25 01:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Testing client for the Laser module.
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





