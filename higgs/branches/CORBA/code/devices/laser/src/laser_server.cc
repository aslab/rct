// Created on: Spring 2010
// Last Change: Fri Feb 25 01:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief CORBA servant implementation, creation and publication for the laser module.
 */
#include "ProtLMS.h"
#include "../../../lib/CORBA_utils.h"

#include "laserS.h"
#include "CosNamingC.h"

#include <pthread.h>

#define SERIAL_DEVICE "/etc/higgs/devices/laser_dev"
//#define SERIAL_DEVICE "/dev/ttyS0"



using namespace std;


class laser_impl : public virtual POA_higgs::laser
{
    ProtLMS laser;
    const int sweep; // Angular span.
    const float angle_resolution;
    pthread_t thread;

    higgs::laser_data_var data;
public:
    laser_impl() :
	sweep(100), // Allowed values 100 and 180 (degrees).
	angle_resolution(1.0f) // Valid values 1.0f, 0.5f and 0.25f(only for sweep = 100).
      {
	if (laser.Init(SERIAL_DEVICE) != PROT_LMS_OK)
	    throw 0;
	//if (laser.ChangeBaudRate(38400) != PROT_LMS_OK);
	    //throw 0;
	if (laser.ChangeVariant(sweep, angle_resolution) != PROT_LMS_OK)
	    throw 0;
	if (laser.Start() != PROT_LMS_OK)
	    throw 0;
	if (pthread_create(&thread, 0, serial_parser, this))
	  {
	    std::cout << "Could not create thread." << std::endl;
	    throw 0;
	  }
      }

    static void * serial_parser(void * obj)
      {
	laser_impl * ref = (laser_impl *)obj;
	ref->data = new higgs::laser_data;
	int i = 0;
	int *values = new int[1000];
	while (i < 3)
	  {
	    int num = 0;
	    // Can check serial timeout and desynchronization.
	    int read_ret = ref->laser.readLMSdata(&num, values);
	    if (read_ret != PROT_LMS_OK)
	      {
		std::cout << "Error while fetching data: " << read_ret << std::endl;
		i++;
		continue;
	      }
	    else
		i = 0;
	    if (num > 401)
	      {
		std::cout << "Future segmentation fault. Aborting." << std::endl;
		exit(0);
	      }

	    ref->data->length(num);
	    for (int i = 0; i < num; i++)
	      {
		CORBA::Float angle = (float)i * ref->angle_resolution - (float)ref->sweep / 2.f;
		ref->data[i].angle = angle*2.f*3.141592654f/360.f;
		ref->data[i].distance = (float)values[i] / 1000.f;
	      }
	  }

	delete values;
	std::cout << "Desynchronized or communication broken. Aborting." << std::endl;
	exit(0);
      }

    virtual ~laser_impl()
      {
	pthread_cancel(thread);
	laser.Stop();
      }

    virtual higgs::laser_data * get_data()
      {
	higgs::laser_data_var ret(data); // Deep copy.
	return ret._retn(); // Destruction managed by caller.
      }
};

//************************************************************************************


int main(int argc, char * argv[])
{
    CORBA_BEGIN_SERVER(argc, argv);

    laser_impl laser;
    higgs::laser_var laser_var = laser._this();

    CORBA_REGISTER_REFERENCE(laser_var, "LASCOR");
    CORBA_END_SERVER;
    return 0;
}
