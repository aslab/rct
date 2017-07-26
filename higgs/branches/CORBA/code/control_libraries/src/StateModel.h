/*
 * StateModel.h
 *
 *   Created on: Dec 25, 2010
 *       Author: chcorbato
 *
 *  Description: the StateModel class defines the interface to access and
 *  			 manipulate an object that contains the state model of a system
 */

#ifndef STATEMODEL_H_
#define STATEMODEL_H_

// newmat configuration /////////////////
#define WANT_STREAM
#include <newmat/newmat.h>
/////////////////////////////////////////

#include <math.h>

using namespace NEWMAT;

class StateModel {
public:

	// write methods
	void setStateSize(int s);			// size of A
	void setMeasurementSize(int s);		// size of H
	void setInputSize(int s);			// size of u

	void setTransitionMatrix(double* m);
	void setTransitionJacobian(double* m);
	void setInputMatrix(double* m);
	void setModelCovariance(double* m);
	void setMeasurementMatrix(double* m);
	void setMeasurementJacobian(double* m);
	void setMeasurementCovariance(double* m);

	void setTransitionMatrix(Matrix m);
	void setTransitionJacobian(Matrix m);
	void setInputMatrix(Matrix m);
	void setModelCovariance(Matrix m);
	void setMeasurementMatrix(Matrix m);
	void setMeasurementJacobian(Matrix m);
	void setMeasurementCovariance(Matrix m);

	void setTstep(double t);

	void updateState(double *s);	// updates the vector state and the model according to it
	void resetState();
	void updateMeasurement(double *m, double *cov);

	// read methods
	int getStateSize();			// size of A
	int getMeasurementSize();	// size of H
	int getInputSize();			// size of u

	double* getState();
	double* getMeasurement();

	double* getTransitionMatrix();
	double* getTransitionJacobian();
	double* getInputMatrix();
	double* getModelCovariance();
	double* getMeasurementMatrix();
	double* getMeasurementJacobian();
	double* getMeasurementCovariance();

	double getTstep();

protected:

	int stateSize;
	int inputSize;
	int measurementSize;

	double	tstep;						// in milliseconds

	// Higgs state model
	ColumnVector	state;				// state estimation vector (updated estimate x(k|k)) [x y v theta w]
	ColumnVector	measurement;		// sensors' measurements vector   [x y v theta w]

	Matrix	transition_mtrx;	// transition matrix for the process model (A)
	Matrix	transition_jacob;	// jacobian of the transition matrix
	Matrix	input_mtrx;			// input matrix for the process model (B)
	Matrix	model_cov;			// model covariances matrix (Q)
	Matrix	measurement_mtrx;	// observation model (H)
	Matrix	measurement_jacob;	// observation model jacobian
	Matrix	measurement_cov;	// measurements covariance matrix (R)

	void updateModel();

	double * r;	// auxiliary pointer

};

#endif /* STATEMODEL_H_ */
