/*
 * EKalman.cpp
 *
 *  Created on: Dec 12, 2010
 *	  Modified: Feb 28, 2011
 *      Author: Carlos Hernandez
 */

#include "EKalman.h"


EKalman::EKalman(int stateSize, int measurementSize) {
	x	   = ColumnVector(stateSize);
	x_pred = ColumnVector(stateSize);
	z_pred = ColumnVector(measurementSize);
	P = Matrix(stateSize,stateSize);
	P_pred = Matrix(stateSize,stateSize);
	K = Matrix(stateSize,measurementSize);
	S = Matrix(measurementSize,measurementSize);
}

EKalman::~EKalman() {

}

ColumnVector EKalman::predict(PredictionModel & model,ColumnVector input){
	x_pred = model.f(x, input);
	P_pred = model.fwP(P);
	return x_pred;
}

ColumnVector EKalman::correct(ObservationModel & omodel, ColumnVector z){
	z_pred = omodel.h(x_pred);

	S = omodel.getR()+omodel.getHx()*P_pred*(omodel.getHx()).t();
	K = P_pred*(omodel.getHx()).t()*S.i();

	x = x_pred + K*(z-z_pred);
	P = P_pred - K*S*K.t();
	return x;
}

// to initialize the kalman filter from an initial state
void EKalman::init(ColumnVector x_init, Matrix P_init) {
	x = x_init;
	P = P_init;
}

Matrix EKalman::getP(){
	return P;
}


