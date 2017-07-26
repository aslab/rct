/*
 * EKalman.h
 *
 *  Created on: Dec 12, 2010
 *      Author: chcorbato
 *
 * Description: the EKalman class encapsulates the functionality of the extended
 * 				Kalman filter. It needs a pointer to an StateModel object
 * 				(attribute model)
 */

#ifndef EKALMAN_H_
#define EKALMAN_H_

#include <opencv/cv.h>
#include <newmat/newmat.h>
#include "StateModel.h"

using namespace NEWMAT;

void array2CvMat(double* a, CvMat* m);

class EKalman {
public:
	EKalman(StateModel* m);
	virtual ~EKalman();

	void estimate(double* c);
	void reset();


private:
	StateModel* model;		// pointer to the state model

	// for the OpenCV kalman
	CvKalman*	kalman;
	CvMat*		measurement;
	CvMat*		control;
	CvMat*		jacob;		// for the jacobian of A in the prediction step
	CvRandState rng;

	// auxiliary variables
};

#endif /* EKALMAN_H_ */
