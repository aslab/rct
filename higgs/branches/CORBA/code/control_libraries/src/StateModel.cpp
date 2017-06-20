/*
 * StateModel.cpp
 *
 *  Created on: Dec 25, 2010
 *      Author: guest
 */

#include "StateModel.h"


int StateModel::getStateSize(){
	return stateSize;
}

int StateModel::getInputSize(){
	return inputSize;
}

int StateModel::getMeasurementSize(){
	return measurementSize;
}

double* StateModel::getInputMatrix(){
	return input_mtrx.Store();
}

double* StateModel::getMeasurement(){
	return measurement.Store();
}

double* StateModel::getMeasurementCovariance(){
	return measurement_cov.Store();
}

double* StateModel::getMeasurementJacobian(){
	return measurement_jacob.Store();
}

double* StateModel::getMeasurementMatrix(){
	return measurement_mtrx.Store();
}

double* StateModel::getModelCovariance(){
	return model_cov.Store();

}

double* StateModel::getState(){
	return state.Store();

}

double* StateModel::getTransitionJacobian(){
	return transition_jacob.Store();
}

double* StateModel::getTransitionMatrix(){
	return transition_mtrx.Store();
}

double StateModel::getTstep(){
	return tstep;
}

///////////////////
/*Matrix StateModel::getInputMatrix(){
	return input_mtrx;
}

ColumnVector StateModel::getMeasurement(){
	return r;
}

Matrix StateModel::getMeasurementCovariance(){
	return measurement_cov;
}

Matrix StateModel::getMeasurementJacobian(){
	return measurement_jacob;
}

Matrix StateModel::getMeasurementMatrix(){
	return measurement_mtrx;
}

Matrix StateModel::getModelCovariance(){
	return model_cov;
}

ColumnVector StateModel::getState(){
	return state;
}

Matrix StateModel::getTransitionJacobian(){
	return transition_jacob;
}

Matrix StateModel::getTransitionMatrix(){
	return transition_mtrx;
}*/
/////////////////////////////////////////

void StateModel::resetState(){
	state = 0.0;
}

void StateModel::setStateSize(int s){
	stateSize = s;
}

void StateModel::setMeasurementSize(int s){
	measurementSize = s;
}

void StateModel::setInputSize(int s){
	inputSize = s;
}

void StateModel::setInputMatrix(double* m){ //use getStateSize to calculate length of m array
	input_mtrx << m;
}

void StateModel::setMeasurementCovariance(double* m){
	measurement_cov << m;
}

void StateModel::setMeasurementJacobian(double* m){
	measurement_jacob << m;
}

void StateModel::setMeasurementMatrix(double* m){
	measurement_mtrx << m;
}

void StateModel::setModelCovariance(double* m){
	model_cov << m;
}

void StateModel::setTransitionJacobian(double* m){
	transition_jacob << m;
}

void StateModel::setTransitionMatrix(double* m){
	transition_mtrx << m;
}

void StateModel::setInputMatrix(Matrix m){ //use getStateSize to calculate length of m array
	input_mtrx = m;
}

void StateModel::setMeasurementCovariance(Matrix m){
	measurement_cov = m;
}

void StateModel::setMeasurementJacobian(Matrix m){
	measurement_jacob = m;
}

void StateModel::setMeasurementMatrix(Matrix m){
	measurement_mtrx = m;
}

void StateModel::setModelCovariance(Matrix m){
	model_cov = m;
}

void StateModel::setTransitionJacobian(Matrix m){
	transition_jacob = m;
}

void StateModel::setTransitionMatrix(Matrix m){
	transition_mtrx = m;
}

void StateModel::setTstep(double t){
	tstep = t;
}

void StateModel::updateState(double *s){
	state << s;
	updateModel();

}

void StateModel::updateMeasurement(double *m, double *cov){}


void StateModel::updateModel(){}

