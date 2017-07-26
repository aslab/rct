/*
 * HiggsStateModel.h
 *
 *   Created on: Dec 12, 2010
 *       Author: chcorbato
 *
 *  Description: the HiggsStateModel class implements actual methods to work
 *  			 with the state model of the higgs robot
 */
#ifndef HIGGSSTATEMODEL_H_
#define HIGGSSTATEMODEL_H_

#include "StateModel.h"

using namespace NEWMAT;

/*
 * This is a passive class that contains data that can be accessed or modified
 * by other classes
 *
 */


class HiggsStateModel: public StateModel {
	// Higgs state model
	// state vector [x y v theta w]
	// sensors' measurements vector   [x y v theta w]
public:
	HiggsStateModel();

	// Higgs model allows for updating the diagonal noise matrix
	void updateMeasurement(double *m, double *cov);

	void updateModel();

};

#endif /* HIGGSSTATEMODEL_H_ */
