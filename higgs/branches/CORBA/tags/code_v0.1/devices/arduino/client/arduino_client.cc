/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <fstream>
#include <iostream>

#include "ArduinoC.h"
#include "CosNamingC.h"

using namespace std;

/*
 * Usage:
 * No parameters: Locate servant through NameServer.
 * 1 parameter: If IOR, use that object. If "ior", get IOR from file "ior".
 */
int main(int argc, char* argv[])
{
    try
      {
	std::cout << "Starting CORBA client test program for Arduino" << std::endl;
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
		name[0].id = "Arduino";
	      }
	    catch (const CosNaming::NamingContext::NotFound &)
	      {
		std::cerr << "Object with name Arduino not found" << std::endl;
		throw 0;
	      }
	    catch (const CORBA::Exception & e)
	      {
		std::cerr << "Resolve failed: " << e << std::endl;
		throw 0;
	      }
	    // Locate the object.
	    obj = inc->resolve(name);
	  }
	else
	  {
	    // Load IOR from file.
	    ifstream file;
	    std::string str;
	    if (strcmp(argv[1], "ior") == 0)
	      {
		file.open("ior");
		file >> str;
		std::cout << str << std::endl;
	      }
	    else
		str = argv[1];
	    // Get reference from arguments and convert to object.
	    obj = orb->string_to_object(str.c_str());
	    if (file.is_open())
		file.close();
	  }

	if (CORBA::is_nil(obj))
	  {
	    std::cerr << "Nil Arduino reference." << std::endl;
	    throw 0;
	  }
	higgs::Arduino_var arduino;
	arduino = higgs::Arduino::_narrow(obj);
	if (CORBA::is_nil(arduino))
	  {
	    std::cerr << "Wrong type for Arduino reference." << std::endl;
	    throw 0;
	  }

	// Test accelerometer.
	double x,y;
	arduino->acelerometro(x, y);
	std::cout << "Accel readings: X=" << x << " Y=" << y << std::endl;

	// Test compass.
	std::cout << "Compass reading = " << arduino->brujula() * 180. / 3.14159269 << std::endl;

	// Test I/V sensors.
	higgs::iv_data inst = arduino->iv_instrumentation();
	higgs::iv_data mot = arduino->iv_motors();
	higgs::iv_data vaio = arduino->iv_vaio();

	cout << "******************************************" << endl;

	cout << "Uinst: " << inst.volts << " V" << endl;
	cout << "Iinst: " << inst.current << " A" << endl;

	cout << "Umot: " << mot.volts << " V" << endl;
	cout << "Imot: " << mot.current << " A" << endl;

	cout << "Charge: " << vaio.volts * 100 << "%" << endl;
	int m, h, s;
	s = vaio.current;
	m = s / 60;
	s -= m*60;
	h = m / 60;
	m -= h*60;
	cout << "Estimated charge duration: " << h << ":" << m << ":" << s << endl;
	usleep(200000);

	// Test servo.
	arduino->cambiarReferencia(100);
	sleep(1);
	arduino->cambiarReferencia(95);
	sleep(1);
	arduino->cambiarReferencia(90);
	sleep(1);
	arduino->cambiarReferencia(85);
	sleep(1);
	arduino->cambiarReferencia(80);
	sleep(1);
	arduino->cambiarReferencia(90);


	// Test switches.
	arduino->TurnOff(higgs::DevWrist);
	arduino->TurnOff(higgs::DevLaser);
	arduino->TurnOff(higgs::DevCamera);
	arduino->TurnOff(higgs::DevGPS);
	arduino->TurnOff(higgs::DevServo);
	arduino->TurnOff(higgs::DevSensors);

	sleep(2);
	arduino->TurnOn(higgs::DevCamera);
	sleep(1);
	arduino->TurnOff(higgs::DevCamera);
	sleep(1);
	arduino->TurnOn(higgs::DevGPS);
	sleep(1);
	arduino->TurnOff(higgs::DevGPS);
	sleep(1);
	arduino->TurnOn(higgs::DevServo);
	sleep(1);
	arduino->TurnOff(higgs::DevServo);
	sleep(1);
	arduino->TurnOn(higgs::DevSensors);
	sleep(1);
	arduino->TurnOff(higgs::DevSensors);

	arduino->TurnOn(higgs::DevWrist);
	arduino->TurnOn(higgs::DevLaser);
	arduino->TurnOn(higgs::DevCamera);
	arduino->TurnOn(higgs::DevGPS);
	arduino->TurnOn(higgs::DevSensors);
	arduino->TurnOn(higgs::DevServo);

      }
    catch(const CORBA::Exception& e) {
	// Handles CORBA exceptions
	std::cerr << std::endl << e << std::endl;
    }

    return 0;
}
