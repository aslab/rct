/*
 * HiggsStateModel.cpp
 *
 *  Created on: Dec 12, 2010
 *      Author: guest
 */

#include "HiggsStateModel.h"


HiggsStateModel::HiggsStateModel() {

	stateSize = 5;
	inputSize = 2;
	measurementSize = 5;

	state = ColumnVector(stateSize);
	measurement = ColumnVector(measurementSize);

	// transition matrix A  (variable elements are marked with a comment)
	transition_mtrx = IdentityMatrix(stateSize);
	transition_mtrx(1,3)= 0.2; // sin(theta)*inc_t
	transition_mtrx(2,3)= 0.2; // cos(theta)*inc_t
	transition_mtrx(3,3)= 0;
	transition_mtrx(4,5)= 0.2; // inc_t
	transition_mtrx(5,5)= 0;

	// transition jacobian
	transition_jacob = IdentityMatrix(stateSize);
	transition_jacob(1,3)= 0.2; // sin(theta)*inc_t
	transition_jacob(2,3)= 0.2; // cos(theta)*inc_t
	transition_jacob(3,3)= 0;
	transition_jacob(1,4)= 0; // v*cos(theta)*inc_t
	transition_jacob(2,4)= 0; // -v*sin(theta)*inc_t
	transition_jacob(4,5)= 0.2; // inc_t
	transition_jacob(5,5)= 0;

	// input matrix B
	input_mtrx = 	 Matrix(stateSize,inputSize);
	input_mtrx =	 0.0;
	input_mtrx(3,1)= 1; // review?
	input_mtrx(5,2)= 1;

	// model covariance matrix Q -- to be adjusted
	model_cov = DiagonalMatrix(stateSize);
	model_cov(1,1)= 0.2;
	model_cov(2,2)= 0.2;
	model_cov(3,3)= 0.1;
	model_cov(4,4)= 5;
	model_cov(5,5)= 3;

	// observation model matrix H (constant)
	measurement_mtrx = IdentityMatrix(measurementSize);

	// observation model jacobian (constant)
	measurement_jacob = IdentityMatrix(measurementSize);

	// measurement covariance matrix R  (this can be updated with info from sensors) -- to be adjusted
	model_cov= DiagonalMatrix(measurementSize);
	model_cov(1,1)= 1;
	model_cov(2,2)= 1;
	model_cov(3,3)= 0.2;
	model_cov(4,4)= 4;
	model_cov(5,5)= 4;

	resetState();
}


// two vectors are passed as arguments:
// r contains the measurements
// cov contains the diagonal covariances (to be squared here)
void HiggsStateModel::updateMeasurement(double* m, double* cov){
	measurement << m;
	for(int i=1; i<=measurementSize; i++)
		if( cov[i-1]!=0 )
			measurement_cov(i,i) = cov[i-1];
}

void HiggsStateModel::updateModel(){
	// update transition matrix A
	transition_mtrx(1,3) = tstep/1000*sin(state(4));
	transition_mtrx(2,3) = tstep/1000*cos(state(4));

	// update jacobian of A
	transition_jacob(1,3)= tstep/1000*sin(state(4)); // sin(theta)*inc_t
	transition_jacob(2,3)= tstep/1000*cos(state(4)); // cos(theta)*inc_t
	transition_jacob(3,3)= 0;
	transition_jacob(1,4)= tstep/1000*cos(state(4))*state(3); // v*cos(theta)*inc_t
	transition_jacob(2,4)= -tstep/1000*sin(state(4))*state(3); // -v*sin(theta)*inc_t
}





