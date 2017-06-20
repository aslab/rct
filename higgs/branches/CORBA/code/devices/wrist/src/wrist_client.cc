// Created on: November 2010
// Last Change: Fri Feb 25 04:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Test client for the wrist module with automatic sequence of commands.
 *
 */
#include <fstream>

#include "wristC.h"
#include "Exception.h"
#include "CosNamingC.h"
#include "../../../lib/CORBA_utils.h"

/*
 * Usage:
 * No parameters: Locate servant through NameServer.
 * 1 parameter: If IOR, use that object. If "ior", get IOR from file "ior".
 */
int main(int argc, char* argv[])
{
    CORBA_BEGIN_CLIENT(argc, argv);
    CORBA_GET_REFERENCE(higgs::wrist, wrist, "wrist");

    std::string params_list = wrist->get_full_state(higgs::wrist::ROLL);
    std::string status = wrist->get_status(higgs::wrist::ROLL);
    std::cout << std::endl << "****************  List of parameters  ***************" << std::endl;
    std::cout << params_list;
    std::cout << "   **** STATUS ****" << std::endl;
    std::cout << status;

    wrist->set_max_speed(6.F, higgs::wrist::PITCH);
    wrist->set_max_accel(5.F, higgs::wrist::PITCH);
    wrist->set_max_accel(2.F, higgs::wrist::ROLL);
    wrist->set_max_speed(4.F, higgs::wrist::ROLL);
    float f = .1F;
    for (int i = 0; i < 9; i++)
      {
	wrist->set_position(0.3*f, higgs::wrist::PITCH);
	wrist->set_position(0.3*f, higgs::wrist::ROLL);
	while (!wrist->is_ready(higgs::wrist::PITCH))
	  {
	    std::cout << wrist->get_current(higgs::wrist::PITCH) << std::endl;
	  }
	wrist->wait(higgs::wrist::BOTH);
	f += (f > 0) ? 0.1 : -0.1;
	f *= -1;
      }
    wrist->set_position(0.F, higgs::wrist::BOTH);
    wrist->wait(higgs::wrist::BOTH);


    CORBA_END_CLIENT;

    return 0;
}
