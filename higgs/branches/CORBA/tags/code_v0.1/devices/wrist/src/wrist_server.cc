/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <fstream>
#include <sstream>

#include "wrist.h"
#include "CosNamingC.h"

#include "../../../lib/CORBA_utils.h"

#define SERIAL_DEVICE "/etc/higgs/devices/wrist_dev"

wrist_servant * wr;
CosNaming::NamingContext_var inc;

void finish_servant(int sig)
{
    TRY;
    cout << "Signal catched! " << sig << endl;

    CosNaming::Name name;
    name.length(1);
    name[0].id = "wrist";
    inc->unbind(name);

    delete wr; // FIXME: It is not detached from the POA.
    exit(0);
    CATCH
}

int main(int argc, char* argv[])
{
    TRY;
    signal(SIGHUP, finish_servant);
    signal(SIGINT, finish_servant);
    signal(SIGQUIT, finish_servant);
    //signal(SIGABRT, finish_servant);
    signal(SIGTERM, finish_servant);
    signal(SIGTSTP, finish_servant);

    CORBA_BEGIN_SERVER(argc,argv);

    // Create a reference to the servant
    wr = new wrist_servant(SERIAL_DEVICE);
    higgs::wrist_var wrist = wr->_this();

    CORBA_REGISTER_REFERENCE(wrist,"wrist");

    CORBA_END_SERVER;
	CATCH;

    return 0;
}
