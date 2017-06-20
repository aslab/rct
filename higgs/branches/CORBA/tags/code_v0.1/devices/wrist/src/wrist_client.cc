/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <fstream>

#include "wristC.h"
#include "Exception.h"
#include "CosNamingC.h"

/*
 * Usage:
 * No parameters: Locate servant through NameServer.
 * 1 parameter: If IOR, use that object. If "ior", get IOR from file "ior".
 */
int main(int argc, char* argv[])
{
    TRY
	std::cout << "Starting CORBA client test program for wrist";
    // Initialize the ORB.
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // Check arguments and get the servant.
    CORBA::Object_var obj;
    if (argc != 2)
      {
	CosNaming::NamingContext_var inc;
	CosNaming::Name name;
	try
	  {
	    CORBA::Object_var rootContextObj = 
		orb->resolve_initial_references("NameService");
	    // Narrow to the correct type
	    inc = CosNaming::NamingContext::_narrow(rootContextObj);

	    name.length(1);
	    name[0].id = "wrist";
	  }
	catch (const CosNaming::NamingContext::NotFound &)
	  {
	    cerr << "Object with name wrist not found" << endl;
	    throw 0;
	  }
	catch (const CORBA::Exception & e)
	  {
	    cerr << "Resolve failed: " << e << endl;
	    throw 0;
	  }
	// Locate the object.
	obj = inc->resolve(name);
      }
    else
      {
	// Load IOR from file.
	ifstream file;
	string str;
	if (strcmp(argv[1], "ior") == 0)
	  {
	    file.open("ior");
	    file >> str;
	    cout << str << endl;
	  }
	else
	    str = argv[1];
	// Get reference from arguments and convert to object.
	obj = orb->string_to_object(str.c_str());
	if (file.is_open())
	    file.close();
      }

    if (CORBA::is_nil(obj))
	error_exception("Nil wrist_server reference.");
    higgs::wrist_var wrist;
    wrist = higgs::wrist::_narrow(obj);
    //std::cout << orb->object_to_string(wrist) << std::endl;
    if (CORBA::is_nil(wrist))
	error_exception("Wrong type for wrist reference.");

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



    CATCH
	catch(const CORBA::Exception& e) {
	    // Handles CORBA exceptions
	    cerr << endl << e << endl;
	}

    return 0;
}
