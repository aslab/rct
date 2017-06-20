/*
 * PredictionModel.h
 *
 *  Created on: Feb 28, 2011
 *      Author: Carlos Hernandez
 */

#ifndef PREDICTIONMODEL_H_
#define PREDICTIONMODEL_H_

#include <newmat/newmat.h>

using namespace NEWMAT;

class PredictionModel {
public:
	PredictionModel(int stateSize);
	virtual ~PredictionModel();

	Matrix		 		 fwP(Matrix P);
	virtual ColumnVector f(ColumnVector x, ColumnVector u)=0;
	virtual void		 update()=0;

protected:
	Matrix Fx;
	Matrix Q;


};

#endif /* PREDICTIONMODEL_H_ */
