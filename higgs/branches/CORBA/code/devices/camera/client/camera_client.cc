#include <fstream>
#include <iostream>
#include <vector>
#include <dc1394/dc1394.h>

#include "CameraC.h"
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
	std::cout << "Starting CORBA client test program for Camera" << std::endl;
	// Initialize the ORB.
	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

	// Check arguments and get the servant.
	CORBA::Object_var obj;
	if (argc != 4)
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
		name[0].id = "Camera";
	      }
	    catch (const CosNaming::NamingContext::NotFound &)
	      {
		std::cerr << "Object with name Camera not found" << std::endl;
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
	higgs::Camera_var camera;
	camera = higgs::Camera::_narrow(obj);
	if (CORBA::is_nil(camera))
	  {
	    std::cerr << "Wrong type for Camera reference." << std::endl;
	    throw 0;
	  }

	camera->init();
	cout << "Resolution: " << camera->getRes() << endl;
	cout << "Gain: " << camera->getGain() << endl;
	cout << "Brightness: " << camera->getBright() << endl;

	cout << "    ---" << endl;
	if (camera->getRes() != higgs::Res_640x480)
	  {
	    camera->changeRes(higgs::Res_640x480);
	    sleep(3);
	    cout << "Resolution: " << camera->getRes() << endl;
	  }
	int image_width = camera->getDeviceWidth();
	int image_height = camera->getDeviceHeight();
	cout << "Image size: " << image_width << "x" << image_height << endl;

	higgs::ImagenData * bayer = camera->getImagen(2, true);
	cout << "Image received. Buffer size: " << bayer->length() << endl;

	unsigned char * rgb = new unsigned char[bayer->length() * 3];
	dc1394_bayer_decoding_8bit(bayer->get_buffer(), rgb, image_width, image_height,
                        DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_BILINEAR);

	cout << "Image decoded." << endl;

	/*
	// Dump image to ASCII text1280x960.
	ofstream red("matlab/red");
	ofstream green("matlab/green");
	ofstream blue("matlab/blue");
	for (int j = 0; j < image_height; j++)
	  {
	    for (int i = 0; i < image_width; i++)
	      {
		int pixel = (image_width * j + i) * 3;
		red   << (int)rgb[pixel + 0] << " ";
		green << (int)rgb[pixel + 1] << " ";
		blue  << (int)rgb[pixel + 2] << " ";
	      }
	    red << endl;
	    green << endl;
	    blue << endl;
	  }
	cout << "Image dumped." << endl;
	*/

	int filter[image_height * image_width];
	for (int i = 0; i < image_height * image_width; i++)
	  {
	    // Red detector
	    filter[i] = rgb[3*i + 0] -rgb[3*i + 1] - rgb[3*i + 2];
	    if (filter[i] < 0)
		filter[i] = 0;
	    // TODO: Hallar centro de gravedad.
	  }


	delete rgb;
	delete bayer;
      }
    catch(const CORBA::Exception& e) {
	// Handles CORBA exceptions
	std::cerr << std::endl << e << std::endl;
    }

    return 0;
}
