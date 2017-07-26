/*
 * StateModel_wrapper.cpp
 *
 *  Created on: Jan 26, 2011
 *      Author: guest
 */


#include "StateModel_wrapper.h"

using namespace higgs;


// utility functions ////////////////////////////////////////////
higgs::matrix* darray2matrix(double *a, int size){
	matrix * m = new matrix(size);
	for(int i=0; i < m->length(); i++){
		(*m)[i] = a[i];
	}
	return m;
}
double* matrix2darray(higgs::matrix* m){
	double * a = new double[m->length()];
	for(int i=0; i < m->length(); i++){
		a[i] = (*m)[i];
	}
	return a;
}
/////////////////////////////////////////////////////////////////

StateModel_wrapper::StateModel_wrapper(WorldModel_var s) {
	wmodel = s;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Methods to be a StateModel client

void StateModel_wrapper::updateState(double* s){
	matrix * p = darray2matrix( s, wmodel->getStateSize());
	wmodel->updateState(*p);
	delete p;
}

void StateModel_wrapper::updateMeasurement(){
	wmodel->updateMeasurement();
}

void StateModel_wrapper::setTstep(double t){
	wmodel->setTstep(t);
}

// all this functions should manage memory better, as in updateState
double* StateModel_wrapper::getState(){
	return matrix2darray( wmodel->getState() );
}

double* StateModel_wrapper::getMeasurement(){
	return matrix2darray( wmodel->getMeasurement() );
}

double* StateModel_wrapper::getTransitionMatrix(){
	return matrix2darray( wmodel->getTransitionMatrix() );
}

double* StateModel_wrapper::getTransitionJacobian(){
	return matrix2darray( wmodel->getTransitionJacobian() );
}

double* StateModel_wrapper::getInputMatrix(){
	return matrix2darray( wmodel->getInputMatrix() );
}

double* StateModel_wrapper::getModelCovariance(){
	return matrix2darray( wmodel->getModelCovariance() );
}
double* StateModel_wrapper::getMeasurementMatrix(){
	return matrix2darray( wmodel->getMeasurementMatrix() );
}

double* StateModel_wrapper::getMeasurementJacobian(){
	return matrix2darray( wmodel->getMeasurementJacobian() );
}

double* StateModel_wrapper::getMeasurementCovariance(){
	return matrix2darray( wmodel->getMeasurementCovariance() );
}

