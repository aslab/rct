/*
 * WorldModel_server.cpp
 *
 *  Created on: Jan 25, 2011
 *      Author: Carlos Hernandez
 * Description: server program for the CORBA WorldModel module
 */

#include <iostream>

#include "CosNamingC.h"
#include "WorldModel_impl.h"
#include "../../lib/CORBA_utils.h"

using namespace higgs;
using namespace std;


int main(int argc, char* argv[])
{

	CORBA_BEGIN_SERVER(argc, argv);

	WorldModel_impl wmodel_servant;
	higgs::WorldModel_var wmodel_var = wmodel_servant._this();
    cout << "WorldModel Module Servant created" << endl;

    CORBA_REGISTER_REFERENCE(wmodel_var, "WORLDMODEL");

    // Accept requests
    cout << "WorldModel Module Server Ready !!" << endl;
    CORBA_END_SERVER;


    return 0;

}
