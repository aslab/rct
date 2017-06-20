/*
 * LowLevelControl_impl.cpp
 *
 *  Created on: Jan 25, 2011
 *      Author: Carlos Hernandez
 */

#include "LowLevelControl_impl.h"

using namespace higgs;
using namespace std;



LowLevelControl_impl::LowLevelControl_impl(CosNaming::NamingContext_var nameservice) {
	//Save the nameservice IOR
	nameServiceVar = nameservice;

	// get CORBA objects /////////////////////////////////////
	try{

		//Get the reference for Arduino
		CORBA_GET_REFERENCE(higgs::Arduino, arduino_v, "Arduino");
		cout<<"Arduino reference successfully obtained!"<<endl;
		//Save arduino's IOR in a local attribute
		arduino = arduino_v;

		//Get the reference for the GPS Module
		CORBA_GET_REFERENCE(higgs::GPS, gps_v, "GPS");
		cout<<"GPS reference successfully obtained!"<<endl;
		//Save gps's IOR in a local attribute
		gps = gps_v;

		//Get the reference for the Pioneer Module
		CORBA_GET_REFERENCE(higgs::Pioneer2AT, pioneer_v, "PIONEER"); //TODO - Change the module namespace to "higgs when operative
		cout<<"Pioneer reference successfully obtained!"<<endl;
		//Save Pioneer'IOR in a local attribute
		pioneer = pioneer_v;

		//Get the reference for the Pioneer Module
		CORBA_GET_REFERENCE(higgs::WorldModel, wm_v, "WORLDMODEL"); //TODO - Change the module namespace to "higgs when operative
		cout<<"WorldModel reference successfully obtained!"<<endl;
		//Save WorldModel'IOR in a local attribute
		wmodel = wm_v;

	CORBA_END_CLIENT;
	/////////////////////////////////////////////////////////////
	tstep = 10000;
	smodel->setTstep( ((double) tstep)/1000 );

}

LowLevelControl_impl::~LowLevelControl_impl() {
	// TODO Auto-generated destructor stub
}



// HiggsMovement interface //////////////////////////////////////

void LowLevelControl_impl::setNameServiceAddr(CosNaming::NamingContext_var nameservice){
	nameServiceVar = nameservice;
}

// set robot linear and angular velocities
void LowLevelControl_impl::setMovement( double v, double w ){
	command[0] = v; //vel_command
	command[1] = w; //rot_command
}

// method to start the control loop in coded in run()
void LowLevelControl_impl::start(){
	pthread_create(&thread, NULL,
			&(LowLevelControl_impl::threadRun),
			this);
}

// method to stop the control loop in coded in run()
void LowLevelControl_impl::stop(){
	pthread_cancel(thread);
}

////////////////////////////////////////////////////////////////




// threaded method that runs the control loop (rutn method)
void * LowLevelControl_impl::threadRun(void *obj){
	LowLevelControl_impl* o = (LowLevelControl_impl*)(obj);
	o->run();
	return 0;
}

// method implementing the control loop that reads the sensors, updates the readings in the world model
void LowLevelControl_impl::run(){

	struct timeval start, end;
	long useconds=0;

	// instantiate kalman connected with model
	filter = new EKalman(smodel);

	// loop for sense-perceive(kalman)-act -----------------------------------------
	// this loop is to be executed each tstep
	while(1){
		gettimeofday(&start, NULL);

		// sense	---------------------------
		//put sensing in the worldmodel
		wmodel->setCompassReading( arduino->brujula() );
		wmodel->setGPSReading( gps->position(), gps->std_deviation() ); // this also should update the x,y in RobotState in WM
		wmodel->setOdometryReading( pioneer->getVelocity(), pioneer->getRotVelocity() );

		// perceive-kalman	-------------------
		smodel->updateMeasurement();//update measurements to the model (from the wm) (including covariances and so)
		filter->estimate(command); //this updates the perceived state in the model and the model accordingly

		// actuate	---------------------------
		pioneer->setVelocity(command[0]);
		pioneer->setRotVelocity(command[1]);


		// sleep for the time necessary to maintain tstep
		gettimeofday(&end, NULL);
		useconds = end.tv_usec - start.tv_usec;
		usleep(tstep-useconds);

	}//while
	//--------------------------------------------------------------------------------------
}
