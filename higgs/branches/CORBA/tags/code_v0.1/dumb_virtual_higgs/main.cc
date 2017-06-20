/* This project emulates the higgs devices with artificial data for testing purposes
 * of the modules that go on top of Higgs' devices.
 */
#include "servants.h"
#include "CosNamingC.h"
#include "../lib/CORBA_utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    CORBA_BEGIN_SERVER(argc, argv);

    // Create objects.
    Arduino_impl Arduino;
    GPS_impl GPS;
    laser_impl laser;
    wrist_impl wrist;
    Pioneer2AT_impl Pioneer2AT;

    // Get the CORBA servant.
    higgs::Arduino_var Arduino_var = Arduino._this();
    higgs::GPS_var GPS_var = GPS._this();
    higgs::laser_var laser_var = laser._this();
    higgs::wrist_var wrist_var = wrist._this();
    higgs::Pioneer2AT_var Pioneer2AT_var = Pioneer2AT._this();

    // Register to NameServer.
    CORBA_REGISTER_REFERENCE(Arduino_var, "Arduino");
    CORBA_REGISTER_REFERENCE(GPS_var, "GPS");
    CORBA_REGISTER_REFERENCE(laser_var, "LASCOR");
    CORBA_REGISTER_REFERENCE(wrist_var, "wrist");
    CORBA_REGISTER_REFERENCE(Pioneer2AT_var, "PIONEER");
    CORBA_END_SERVER;
    return 0;
}
