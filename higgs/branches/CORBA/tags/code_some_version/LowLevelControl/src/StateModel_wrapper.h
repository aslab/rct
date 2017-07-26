/*
 * StateModel_wrapper.h
 *
 *  Created on: Jan 26, 2011
 *      Author: guest
 *
 *
 */

#ifndef STATEMODEL_WRAPPER_H_
#define STATEMODEL_WRAPPER_H_


#include "WorldModelC.h"
#include "StateModel.h"

using namespace higgs;

class StateModel_wrapper : public StateModel{
public:
	StateModel_wrapper(WorldModel_var wm);

	void updateState(double* s);
	void updateMeasurement();

	double* getState();
	double* getMeasurement();
	void	setTstep(double t);

	double* getTransitionMatrix();
	double* getTransitionJacobian();
	double* getInputMatrix();
	double* getModelCovariance();
	double* getMeasurementMatrix();
	double* getMeasurementJacobian();
	double* getMeasurementCovariance();

private:

	WorldModel_var	wmodel;
};

#endif /* STATEMODEL_WRAPPER_H_ */
