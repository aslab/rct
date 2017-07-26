/*
 * HiggsStateModel.cpp
 *
 *  Created on: Dec 12, 2010
 *      Author: Carlos Hernandez
 */

#include "HiggsModels.h"


HiggsStateModel::HiggsStateModel(double tstep) : PredictionModel(5) {

	dt = tstep;

	// jacobian
	Fx(1,1)= 1;
	Fx(1,3)= dt; // sin(theta)*inc_t
	Fx(2,2)= 1;
	Fx(2,3)= dt; // cos(theta)*inc_t
	Fx(3,3)= 0;
	Fx(1,4)= 0; // v*cos(theta)*inc_t
	Fx(2,4)= 0; // -v*sin(theta)*inc_t
	Fx(4,4)= 1;
	Fx(4,5)= dt; // inc_t
	Fx(5,5)= 0;

	// model covariance matrix Q -- to be adjusted
	Q(1,1)= 0.2;
	Q(2,2)= 0.2;
	Q(3,3)= 0.1;
	Q(4,4)= 5;
	Q(5,5)= 3;

	A = IdentityMatrix(5);
	A(1,3)= dt; // sin(theta)*inc_t
	A(2,3)= dt; // cos(theta)*inc_t
	A(3,3)= 0;
	A(4,5)= dt; // inc_t
	A(5,5)= 0;

	// input matrix B
	B = Matrix(5,2); B = 0.0;
	B(3,1)= 1; // review?
	B(5,2)= 1;

}

ColumnVector HiggsStateModel::f(ColumnVector x, ColumnVector u){
	return A*x+B*u;
}


double HiggsStateModel::getTstep(){
	return dt;
}

void HiggsStateModel::setTstep(double tstep){
	dt = tstep;
}

void HiggsStateModel::update(){
	// update transition matrix A
	A(1,3) = dt/1000*sin(state(4));
	A(2,3) = dt/1000*cos(state(4));

	// update jacobian of A
	Fx(1,3)= dt/1000*sin(state(4)); // sin(theta)*inc_t
	Fx(2,3)= dt/1000*cos(state(4)); // cos(theta)*inc_t
	Fx(3,3)= 0;
	Fx(1,4)= dt/1000*cos(state(4))*state(3); // v*cos(theta)*inc_t
	Fx(2,4)= -dt/1000*sin(state(4))*state(3); // -v*sin(theta)*inc_t
}

void HiggsStateModel::setModelParameters(ColumnVector & s){
	state = s;
}


HiggsObservationModel::HiggsObservationModel() : ObservationModel(5,5){
	Hx = IdentityMatrix(5);

	R(1,1)= 1;
	R(2,2)= 1;
	R(3,3)= 0.2;
	R(4,4)= 4;
	R(5,5)= 4;
}

ColumnVector HiggsObservationModel::h(ColumnVector x){
	return x;	// since for this model h is the identity
}

void HiggsObservationModel::update(){
	// for now this functionality is provided by getR and setR
}

Matrix HiggsObservationModel::getR(){
	return R;
}

void HiggsObservationModel::setR(Matrix newR){
	R = newR;
}





