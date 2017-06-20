/*
 * WorldModel_impl.cpp
 *
 *  Created on: Jan 24, 2011
 *      Author: chcorbato
 */

#include "WorldModel_impl.h"

#include "../../lib/CORBA_utils.h"

#include <iostream>

using namespace higgs;
using namespace std;


// utility functions ////////////////////////////////////////////
higgs::matrix* darray2matrix(double *a, int size){
	higgs::matrix * m = new matrix(size);
	for(int i=0; i < m->length(); i++){
		m[i] = a [i];
	}
	return m;
}
double* a;
double* matrix2darray(matrix m){
	a = new double[m.length()];
	for(int i=0; i < m.length(); i++){
		a[i] = m[i];
	}
	return a;
}
/////////////////////////////////////////////////////////////////


WorldModel_impl::WorldModel_impl() {

	//Set initial values for Robot State
	currentRobotState.x = 0;
	currentRobotState.y = 0;
	currentRobotState.theta = 0;
	currentRobotState.vel = 0;
	currentRobotState.rot_vel = 0;
}

WorldModel_impl::~WorldModel_impl() {
	// TODO Auto-generated destructor stub
}

void WorldModel_impl::setLaserReading( const higgs::laser_data & lreadings ){
	laserReading = lreadings;
}

// Valor en radianes de la brújula. 0 North, pi/2 West, as defined in Arduino.idl
void WorldModel_impl::setCompassReading( double a ){
	measurements[3] = a;
}

// update in the WM the latest values of velocity coming from odometry
void WorldModel_impl::setOdometryReading( double linVel, double rotVel ){
	measurements[2] = linVel;
	measurements[4] = rotVel;
}

void WorldModel_impl::setUTMReading( const higgs::GPS_coords_UTM & coords, const higgs::GPS_coords & deviation ){// do the actual math

	if( (coords.zone == referencePoint.zone) && (coords.zone == referencePoint.zone) ){

		currentRobotState.x = referencePoint.easting - coords.easting;
		currentRobotState.y = referencePoint.northing - coords.northing;

		measurements[0] = currentRobotState.x;
		measurements[1] = currentRobotState.y;

		// missing to update gps deviations into measurements_cov
		measurements[0] = deviation.latitude*deviation.latitude;
		measurements[6] = deviation.longitude*deviation.longitude;
	}

	else{
		/* return some error*/
	}

}

higgs::RobotState WorldModel_impl::getCurrentRobotState(){
	return currentRobotState;
}

higgs::laser_data* WorldModel_impl::getLaserReading(){
	return &laserReading;
}

Pose WorldModel_impl::getPosition(){
	static Pose position;
	position.x		= currentRobotState.x;
	position.y		= currentRobotState.y;
	position.alpha	= currentRobotState.theta;
	return position;
}

void WorldModel_impl::setUTMReference(const higgs::GPS_coords_UTM & coords){
	referencePoint = coords;
}


void WorldModel_impl::updateRobotModel(){
	model.updateModel();
}

// this method is not used, if other perceptor would have better estimation of state it can set it with it
void WorldModel_impl::updateRobotState( const higgs::RobotState & s){

	static double c[5];
	c[0] = s.x;
	c[1] = s.y;
	c[3] = s.vel;
	c[3] = s.theta;
	c[4] = s.rot_vel;
	model.updateState(c); // state vector [x y v theta w]

	currentRobotState.x = s.x;
	currentRobotState.y = s.y;
	currentRobotState.theta = s.theta;
	currentRobotState.vel = s.vel;
	currentRobotState.rot_vel = s.rot_vel;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Methods to be a StateModel server

void WorldModel_impl::updateState(const matrix & s){
	model.updateState( matrix2darray(s) );
}

void WorldModel_impl::updateMeasurement(){
	model.updateMeasurement(measurements, measurements_cov);
}

void WorldModel_impl::setTstep(double t){
	model.setTstep(t);
}

short WorldModel_impl::getStateSize(){
	return model.getStateSize();
}

matrix* WorldModel_impl::getState(){
	return darray2matrix( model.getState(), model.getStateSize() );
}

matrix* WorldModel_impl::getMeasurement(){
	return darray2matrix( model.getMeasurement(), model.getMeasurementSize() );
}

matrix* WorldModel_impl::getTransitionMatrix(){
	return darray2matrix( model.getTransitionMatrix(), model.getStateSize()*model.getStateSize());
}

matrix* WorldModel_impl::getTransitionJacobian(){
	return darray2matrix( model.getTransitionJacobian(), model.getStateSize()*model.getStateSize() );
}

matrix* WorldModel_impl::getInputMatrix(){
	return darray2matrix( model.getInputMatrix(), model.getInputSize()*model.getStateSize() );
}

matrix* WorldModel_impl::getModelCovariance(){
	return darray2matrix( model.getModelCovariance(), model.getStateSize()*model.getStateSize() );
}
matrix* WorldModel_impl::getMeasurementMatrix(){
	return darray2matrix( model.getMeasurementMatrix(), model.getMeasurementSize()*model.getMeasurementSize() );
}

matrix* WorldModel_impl::getMeasurementJacobian(){
	return darray2matrix( model.getMeasurementJacobian(), model.getMeasurementSize()*model.getMeasurementSize() );
}

matrix* WorldModel_impl::getMeasurementCovariance(){
	return darray2matrix( model.getMeasurementCovariance(), model.getMeasurementSize()*model.getMeasurementSize() );
}

///////////////////////////////////////////////////////////////////////////////////////////
