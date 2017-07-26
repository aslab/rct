/* Helper macros for CORBA typical procedures.
 * \author Francisco J. Arjonilla García
 * \year 2010-2011
 *
 * These macros rely upon configuration files located under /etc/higgs. These are:
 * nameservice.ip Contains the ip or address and optionally the port of the nameserver. Format: ns.com:80
 * listen_endpoint.ip The IPv4 address where the servants should listen on. (i.e. the localhost address)
 */
#ifndef CORBA_UTILS_H
#define CORBA_UTILS_H

/*
 * A typical servant executable would be something like:

#include "implementation.h"
#include "CosNamingC.h"
#include "../../lib/CORBA_utils.h"

int main(int argc, char* argv[])
{
    CORBA_BEGIN_SERVER(argc, argv);

    implementation_t impl();
    higgs::implementation_t_var implvar = impl._this();

    CORBA_REGISTER_REFERENCE(implvar, "IMPL");
    CORBA_END_SERVER;
    return 0;
}

 *
 *
 * And a typical client:
 *

#include <iostream>
#include "implementationC.h"
#include "CosNamingC.h"
#include "../../lib/CORBA_utils.h"

int main(int argc, char* argv[])
{
    CORBA_BEGIN_CLIENT(argc, argv);
    CORBA_GET_REFERENCE(module::implementation, impl, "IMPL");

    impl->do_things();

    CORBA_END_CLIENT;
    return 0;
}

*/

#include <fstream>
#include <iostream>
#include <string>

/******** CLIENTS ********/

// Initializes the Root POA and gets the NameService.
#define CORBA_BEGIN_CLIENT(argc, argv) \
    try { \
	int argc_ext = argc + 2; \
	char * argv_ext[argc_ext]; \
	memcpy(argv_ext, argv, argc * sizeof(char *)); \
	std::string ns_iior = "NameService=corbaloc::"; \
	ifstream fs_ip("/etc/higgs/nameservice.ip"); \
	if (!fs_ip) \
	  { \
	    std::cerr << "Error: /etc/higgs/nameservice.ip could not be opened." << endl; \
	    exit(1); \
	  } \
	char c_ip[200]; \
	fs_ip.getline(c_ip, 200); \
	ns_iior += c_ip; \
	ns_iior += "/NameService"; \
	argv_ext[argc] = (char *)"-ORBInitRef"; \
	argv_ext[argc + 1] = (char *)ns_iior.c_str(); \
	std::cout << "Starting " << argv[0] << " ..." << endl; \
	std::cout << "Initializing client ORB and NameService..." << endl; \
	CORBA::ORB_var orb = CORBA::ORB_init(argc_ext, argv_ext); \
	CORBA::Object_var rootContextObj = orb->resolve_initial_references("NameService"); \
	CosNaming::NamingContext_var nameservice; \
	try { \
	    nameservice = CosNaming::NamingContext::_narrow(rootContextObj); \
	} catch (const CORBA::Exception& ex) { \
	    cerr << "Oops, I cannot access the Naming Service!" <<endl; \
	    cerr << ex << endl; \
	    exit(1); \
	}

	// It can be used also in servers.
#define CORBA_GET_REFERENCE(type, obj_var, name) \
	type##_var obj_var; \
	  { \
	    CORBA::Object_var obj; \
	    try { \
		CosNaming::Name cn_name; \
		cn_name.length(1); \
		cn_name[0].id = name; \
		obj = nameservice->resolve(cn_name); \
	    } catch (const CosNaming::NamingContext::NotFound &) { \
		cerr << "Object with name " << name << " not found" << endl; \
		throw 0; \
	    } catch (const CORBA::Exception & e) { \
		cerr << "Resolve failed: " << e << endl; \
		throw 0; \
	    } \
	    obj_var = type::_narrow(obj); \
	    if (CORBA::is_nil(obj_var)) { \
		cerr << "Wrong type for " << name << " reference." << endl; \
		throw 0; \
	    } \
	  }


#define CORBA_END_CLIENT \
    } catch(const CORBA::Exception& e) { \
	cerr << endl << e << endl; \
    } catch(...) {cerr << "Unknown exception raised." << endl; }


/******** SERVERS ********/

// Initializes the Root POA, the POA manager and gets the NameService.
#define CORBA_BEGIN_SERVER(argc, argv) \
    try { \
	int argc_ext = argc + 4; \
	char * argv_ext[argc_ext]; \
	memcpy(argv_ext, argv, argc * sizeof(char *)); \
	std::string ns_iior = "NameService=corbaloc::"; /* NameService arguments */ \
	ifstream fs_ip("/etc/higgs/nameservice.ip"); \
	if (!fs_ip) \
	  { \
	    std::cerr << "Error: /etc/higgs/nameservice.ip could not be opened." << endl; \
	    exit(1); \
	  } \
	char c_ip[200]; \
	fs_ip.getline(c_ip, 200); \
	ns_iior += c_ip; \
	ns_iior += "/NameService"; \
	argv_ext[argc] = (char *)"-ORBInitRef"; \
	argv_ext[argc + 1] = (char *)ns_iior.c_str(); \
	std::string s_ep = "iiop:/" "/"; /* ListenEndpoints arguments */ \
	ifstream fs_ep("/etc/higgs/listen_endpoint.ip"); \
	if (!fs_ep) \
	  { \
	    std::cerr << "Error: /etc/higgs/listen_endpoint.ip could not be opened." << endl; \
	    exit(1); \
	  } \
	fs_ip.getline(c_ip, 200); \
	s_ep += c_ip; \
	argv_ext[argc + 2] = (char *)"-ORBListenEndpoints"; \
	argv_ext[argc + 3] = (char *)s_ep.c_str(); \
	std::cout << "Starting " << argv[0] << " ..." << endl;/* Initialize ORB */ \
	std::cout << "Initializing server POA manager and NameService..." << endl; \
	CORBA::ORB_var orb = CORBA::ORB_init(argc_ext, argv_ext); \
	CORBA::Object_var obj_poa = orb->resolve_initial_references("RootPOA"); \
	PortableServer::POA_var poa = PortableServer::POA::_narrow(obj_poa); \
	PortableServer::POAManager_var poa_manager = poa->the_POAManager(); \
	poa_manager->activate(); \
	CORBA::Object_var rootContextObj = orb->resolve_initial_references("NameService"); \
	CosNaming::NamingContext_var nameservice; \
	try { \
	    nameservice = CosNaming::NamingContext::_narrow(rootContextObj); \
	} catch (const CORBA::Exception& ex) { \
	    cerr << "Oops, I cannot access the Naming Service!" <<endl; \
	    cerr << ex << endl; \
	    exit(1); \
	}

#define CORBA_REGISTER_REFERENCE(obj_var, name) \
	  { \
	    std::cout << "Registering " << name << " ..." << endl; \
	    CosNaming::Name cn_name; \
	    cn_name.length(1); \
	    cn_name[0].id = name; \
	    nameservice->rebind(cn_name, obj_var); \
	  }

#define CORBA_END_SERVER \
	cout << "The server is ready. Awaiting for incoming requests." << endl; \
	orb->run(); \
	CORBA_END_CLIENT;

#endif

