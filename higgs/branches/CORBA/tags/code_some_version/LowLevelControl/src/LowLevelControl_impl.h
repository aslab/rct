/*
 * LowLevelControl_impl.h
 *
 *  Created on: Jan 25, 2011
 *      Author: Carlos Hernandez
 *
 *  Realized interface: HiggsMovements
 *
 *  Implements: a low level control loop of Higgs:
 *  - collects readings from sensors and updates a WorldModel with them
 *  - estimates robot state [x y linear_vel theta rotacional_vel] with an extended
 *    Kalman filter
 */

#ifndef LOWLEVELCONTROL_IMPL_H_
#define LOWLEVELCONTROL_IMPL_H_

#include "LowLevelControlS.h"
#include "CosNamingC.h"
#include "ArduinoC.h"
#include "gpsC.h"
#include "laserC.h"
#include "Pioneer2ATC.h"
#include "WorldModelC.h"

#include "../../lib/CORBA_utils.h"

#include <time.h>
#include <pthread.h>

#include "EKalman.h"
#include "StateModel_wrapper.h"

class LowLevelControl_impl : public POA_higgs::HiggsMovement{

public:
	LowLevelControl_impl(CosNaming::NamingContext_var nameservice);
	virtual ~LowLevelControl_impl();

	//HiggsMovement Interface //////////////////////////////////////
	virtual void	setMovement( double v, double w ); // set robot linear and angular velocities
	virtual void	setNameServiceAddr(CosNaming::NamingContext_var nameService);
	virtual void	start();		// launches thread with run (loop)
	virtual void	stop();			// stops thread with loop
	////////////////////////////////////////////////////////////////

private:

	void	run();		// ECL loop
	static void *	threadRun(void *obj);	// thread for run

	pthread_t thread;

	// IORs
	CosNaming::NamingContext_var nameServiceVar;//IOR of the Naming Service Object
	higgs::Arduino_var 		arduino;
	higgs::GPS_var			gps;
	higgs::laser_var		laser;
	higgs::Pioneer2AT_var	pioneer;
	higgs::WorldModel_var 	wmodel;

	// for the extended kalman filter
	EKalman *				filter;
	StateModel_wrapper *	smodel; //local state model for EKalman filter (to be kept update with wmodel)

	double					command[2];  // [vel rotvel]
	long					tstep;		// in microseconds, time step of the loop
};

#endif /* LOWLEVELCONTROL_IMPL_H_ */
