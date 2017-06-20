/*
 * WorldModel_impl.h
 *
 *  Created on: Jan 24, 2011
 *      Author: Carlos Hernandez
 * Description: CORBA servant class for the WorldModel interface
 */

#ifndef WORLDMODEL_IMPL_H_
#define WORLDMODEL_IMPL_H_

#include "WorldModelS.h"
#include "CosNamingC.h"

#include <HiggsStateModel.h>

using namespace higgs;

class WorldModel_impl : public POA_higgs::WorldModel{

public:

	WorldModel_impl();
	virtual ~WorldModel_impl();

	// for CORBA StateModel client /////////////////////////////////
	virtual matrix*	getTransitionMatrix();
	virtual matrix*	getTransitionJacobian();
	virtual matrix*	getInputMatrix();
	virtual matrix*	getModelCovariance();
	virtual matrix*	getMeasurementMatrix();
	virtual matrix*	getMeasurementJacobian();
	virtual matrix*	getMeasurementCovariance();

	virtual matrix*	getState();
	virtual matrix*	getMeasurement();

	virtual short	getStateSize();

	virtual void	updateState( const matrix & s);
	virtual void	updateMeasurement();	//update the measurements in the StateModel from those already available
	virtual void	setTstep(double t);
	/////////////////////////////////////////////////////////////


	// methods for perceptors
	virtual void updateRobotModel();	//updates RobotStateModel accordingly to the current state

	virtual void updateRobotState( const higgs::RobotState & s ); //not used

	virtual void	setLaserReading( const higgs::laser_data & lreadings );
	virtual void	setCompassReading( double a ); // Valor en radianes de la brújula. 0 North, pi/2 West, as defined in Arduino.idl
	virtual void	setOdometryReading( double linVel, double rotVel );  // update in the WM the latest values of velocity coming from odometry
	virtual void	setUTMReading( const higgs::GPS_coords_UTM & coords, const higgs::GPS_coords & deviation );
	virtual void	setUTMReference( const higgs::GPS_coords_UTM & coords );


	// methods for actuators
	virtual higgs::RobotState	getCurrentRobotState();
	virtual higgs::laser_data*	getLaserReading();
	virtual Pose				getPosition();


private:

	higgs::RobotState	currentRobotState;

	laser_data			laserReading;
	double				compassReading;
	GPS_coords_UTM		referencePoint;

	// for StateModel (to maintain synchronized with the previous attributes)
	HiggsStateModel		model;
	double 				measurements[5];		// [x y vlin theta rot_vel]
	double 				measurements_cov[25];


};

#endif /* WORLDMODEL_IMPL_H_ */
