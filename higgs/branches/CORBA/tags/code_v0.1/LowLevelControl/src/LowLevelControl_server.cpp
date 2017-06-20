/*
 * LowLevelControl.cpp
 *
 *  Created on: Jan 25, 2011
 *      Author: Carlos Hernandez
 *
 * Description: server program for the LOwLevelControl CORBA module
 */

#include <iostream>

#include "CosNamingC.h"
#include "LowLevelControl_impl.h"
#include "../../lib/CORBA_utils.h"

using namespace higgs;
using namespace std;


int main(int argc, char* argv[])
{

	CORBA_BEGIN_SERVER(argc, argv);

	LowLevelControl_impl controller_servant(nameservice);

	higgs::HiggsMovement_var controller_var = controller_servant._this();

    cout << "LowLevelControl Module Servant created" << endl;

    CORBA_REGISTER_REFERENCE(controller_var, "HIGGSMOVEMENT");

    // Accept requests
    cout << "LowLevelControl Module Server Ready !!" << endl;

    // launch ECL loop (has its own thread)
    controller_servant.start();

    CORBA_END_SERVER;


    return 0;

}
