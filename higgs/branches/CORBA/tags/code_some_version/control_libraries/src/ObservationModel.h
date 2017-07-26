/*
 * ObservationModel.h
 *
 *  Created on: Feb 28, 2011
 *      Author: Carlos Hernandez
 */

#ifndef OBSERVATIONMODEL_H_
#define OBSERVATIONMODEL_H_

#include <newmat/newmat.h>

using namespace NEWMAT;

class ObservationModel {
public:
	ObservationModel(int stateSize, int measurementsSize);
	virtual ~ObservationModel();

	virtual ColumnVector h(ColumnVector x)=0;
	virtual void update()=0;

	Matrix getHx();
	Matrix getR();

protected:
	Matrix Hx;
	Matrix R;
};

#endif /* OBSERVATIONMODEL_H_ */
