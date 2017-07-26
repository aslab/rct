/*
 * simpleEKalman.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: guest
 */

#include <cstdlib>
#include <math.h>
#include <iostream>

#include <newmat/newmat.h>
#include "EKalman.h"
#include "PredictionModel.h"
#include "ObservationModel.h"

using namespace std;

#define COV 0.01



class SimpleModel : public PredictionModel{
public:
	SimpleModel() : PredictionModel(1)	{
		Fx = 1.0;
		Q = 0.00001;
	}

	ColumnVector f(ColumnVector x, ColumnVector u){
		return x;
	}

	void update(){}
};


class OSimpleModel : public ObservationModel{
public:
	OSimpleModel() : ObservationModel(1,1){
		Hx = 1.0;
		R = COV;
	}

	ColumnVector h(ColumnVector x){
		return x;
	}

	void update(){}

};

double sampleGaussian(double mean, double cov){
	double med =0;
	for(int i=0;i<12;i++){
		med+=rand()/(float)RAND_MAX;
	}

	med-=6;

	double x = mean + med*sqrt(cov);

	return x;
}

int main(){

	ColumnVector x_est = ColumnVector(1);
	ColumnVector x_real = ColumnVector(1);
	ColumnVector z_real = ColumnVector(1);
	Matrix P_init = Matrix(1,1); P_init = 1.0;
	x_real = 2.0;
	x_est = 2.0;
	ColumnVector input = ColumnVector(1); input = 0.0;
	cout<<"--vectors created"<<endl;

	SimpleModel model;
	OSimpleModel omodel;
	EKalman filter(1,1);
	cout<<"--objects created"<<endl;

	filter.init(x_est, P_init);

	cout<<"--filter initialised"<<endl;

	for(int i=0; i< 50; i++){
		// update models with current estimation and measurements info
		model.update();

		z_real(1) = sampleGaussian(2,COV);

		omodel.update();

		filter.predict(model,input);


		x_est = filter.correct(omodel, z_real);

		//cout << 2-x_est(1) <<" : "<< 2-z_real(1) << endl;
		cout << (filter.getP())(1,1)<<endl;

	}







}
