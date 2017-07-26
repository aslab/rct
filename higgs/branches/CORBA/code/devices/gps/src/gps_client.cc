// Last Change: Fri Feb 25 01:00 PM 2011 C
/** \author chcorbato
 * \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief TAO client example for GPS interface
 *
 * This file implements a TAO CORBA client for making data requests to a GPS_impl
 * server object through the standard io
 */


#include <iostream>
#include <iomanip>

#include "gpsC.h"
#include "CosNamingC.h"
#include "../../../lib/CORBA_utils.h"

using namespace std;

/**
 * enter a 'h' character for help, or other characters for requesting different data
 * from the GPS server object
 */
int main(int argc, char* argv[])
{
    CORBA_BEGIN_CLIENT(argc, argv);
    CORBA_GET_REFERENCE(higgs::GPS, gps, "GPS");

    cout.precision(12);

    char command = 'h';
    do {
	higgs::GPS_coords pos;
	higgs::GPS_speed speed;

	switch(command){

	    case 'h':
		cout << "Usage: 'h' for help \n \t 'q' to exit \n \t 'p' to get position \n"
		    "\t 'v' to get speed \n \t 's' to get num satellites \n \t"
		    " 'd' to get standard deviation error \n \t 't' to get type of solution" << endl;
		break;

	    case 'q':
		break;

	    case 'p':
		pos = gps->position();
		cout << "Latitud: " << pos.latitude << endl
		    << "Longitud: " << pos.longitude << endl
		    << "Altitud: " << pos.height << endl;
		break;

	    case 'd':
		pos = gps->std_deviation();
		cout << "Desviación típica de la Latitud: " << pos.latitude << endl
		    << "Desviación típica de la Longitud: " << pos.longitude << endl
		    << "Desviación típica de la Altitud: " << pos.height << endl;
		break;

	    case 'v':
		speed = gps->speed();
		cout << "Velocidad (m/s): " << speed.celerity << endl
					       << "Orientación (deg): " << speed.heading * 180. / 3.14159 << endl
									   << "Ascensión (m/s): " << speed.height_speed << endl;
		break;

	    case 's':
		cout << "Numero de satélites: "
		    << gps->satellites() << endl;
		break;

	    case 't':
		std::string sol;
		higgs::GPS_solution_type sol_type = gps->solution_type();
		switch (sol_type)
		  {
		    case higgs::PENDING: sol = "Pending"; break;
		    case higgs::SINGLE: sol = "Single"; break;
		    case higgs::SBAS: sol = "SBAS"; break;
		    case higgs::DIFFERENTIAL: sol = "Differential"; break;
		    case higgs::UNKNOWN: sol = "Unknown"; break;
		  }
		cout << "Tipo de solución: " << sol << endl;
		break;
	}

	scanf("%c", &command);
    } while (command != 'q');

    CORBA_END_CLIENT;
    return 0;

}
