/*
 * EKalman.h
 *
 *  Created on: Dec 12, 2010
 *      Author: chcorbato
 *
 * Description: the EKalman class encapsulates the functionality of the extended
 * 				Kalman filter. It needs a pointer to an StateModel object
 * 				(attribute model)
 */

#ifndef EKALMAN_H_
#define EKALMAN_H_

#include <newmat/newmat.h>
#include "PredictionModel.h"
#include "ObservationModel.h"


using namespace NEWMAT;


class EKalman {
public:
	EKalman(int stateSize, int measurementSize);
	virtual ~EKalman();

	void estimate(double* c);
	void reset();


private:
	ColumnVector	x;
	ColumnVector	x_pred;
	ColumnVector	z_pred;
	Matrix			P;		// state covariance
	Matrix			P_pred;

	Matrix	K;					// kalman gain
	Matrix  S;					// innovation covariance


	// auxiliary variables
public:
	void init(ColumnVector x_init, Matrix P_init);
	ColumnVector predict(PredictionModel & model, ColumnVector input);
	ColumnVector correct(ObservationModel & omodel, ColumnVector z);
	Matrix getP();
};

#endif /* EKALMAN_H_ */
