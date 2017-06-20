/*
 * HiggsModels.h
 *
 *   Created on: Dec 12, 2010
 *       Author: Carlos Hernandez
 *
 *  Description: classes that define concrete (state-based) prediction and observation models of Higgs
 */
#ifndef HIGGSMODELS_H_
#define HIGGSMODELS_H_

#include "PredictionModel.h"
#include "ObservationModel.h"

#include <math.h>

using namespace NEWMAT;




class HiggsStateModel: public PredictionModel {
	// Higgs state model
	// state vector [x y v theta w]
	// input vector u = [v w]
public:
	HiggsStateModel(double tstep);

	ColumnVector f(ColumnVector x, ColumnVector u);
	void update();

	void setTstep(double tstep);
	double getTstep();

	void setModelParameters(ColumnVector & s); // they are in the state vector for this model

private:
	Matrix A;
	Matrix B;
	double dt;

	ColumnVector state;

};

class HiggsObservationModel : public ObservationModel
{
	// sensors' measurements vector   [x y v theta w]
public:

	HiggsObservationModel();

	ColumnVector h(ColumnVector x);

	void update();

	Matrix getR();
	void setR(Matrix newR);


};

#endif /* HIGGSMODELS_H_ */
