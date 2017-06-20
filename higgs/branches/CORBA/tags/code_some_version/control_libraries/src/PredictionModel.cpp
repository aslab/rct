/*
 * PredictionModel.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: Carlos Hernandez
 */

#include "PredictionModel.h"

PredictionModel::PredictionModel(int stateSize) {
	Fx = Matrix(stateSize,stateSize); Fx = 0.0;
	Q = Matrix(stateSize,stateSize); Q =0.0;
}

PredictionModel::~PredictionModel() {
	// TODO Auto-generated destructor stub
}

Matrix PredictionModel::fwP(Matrix P){
	return Fx*P*Fx.t()+Q;

}
