/*
 * ObservationModel.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: Carlos Hernandez
 */

#include "ObservationModel.h"

ObservationModel::ObservationModel(int stateSize, int measurementsSize) {
	Hx = Matrix(stateSize,stateSize); Hx = 0.0;
	R = Matrix(stateSize,stateSize); R =0.0;
}

ObservationModel::~ObservationModel() {
	// TODO Auto-generated destructor stub
}

Matrix ObservationModel::getHx(){
	return Hx;
}

Matrix ObservationModel::getR(){
	return R;
}
