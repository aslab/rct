/*
 * EKalman.cpp
 *
 *  Created on: Dec 12, 2010
 *      Author: guestchanged
 */

#include "EKalman.h"


// auxiliary function to translate an array into a opencv matrix CvMat
void array2CvMat(double* a, CvMat* m){

	for(int i=0; i < m->cols*m->rows; i++)
		m->data.db[i] = a[i];
}

EKalman::EKalman(StateModel* m) {
	// TODO Auto-generated constructor stub
	model = m;

	measurement = cvCreateMat( model->getMeasurementSize(), 1, CV_32FC1 );
	control = cvCreateMat(model->getInputSize(), 1, CV_32FC1 );

	kalman = cvCreateKalman( model->getStateSize(), model->getMeasurementSize(), model->getInputSize() );

	// initialize kalman's model matrices with those from the model
	array2CvMat(model->getTransitionMatrix(), kalman->transition_matrix);
	array2CvMat(model->getModelCovariance(), kalman->process_noise_cov);
	array2CvMat(model->getInputMatrix(), kalman->control_matrix);
	array2CvMat(model->getMeasurementMatrix(), kalman->measurement_matrix);
	array2CvMat(model->getMeasurementCovariance(), kalman->measurement_noise_cov);

	cvRandInit( &rng, 0, 1, -1, CV_RAND_UNI );

	// initialize state covariances post and pre-correction
	cvSetIdentity( kalman->error_cov_post, cvRealScalar(1));
	cvSetIdentity( kalman->error_cov_pre, cvRealScalar(1));

	// initialize state estimation post-correction
	cvSetIdentity( kalman->state_post, cvRealScalar(0));

}

EKalman::~EKalman() {
	// TODO Auto-generated destructor stub
	cvReleaseKalman( &kalman );
}

// to initialize the kalman filter from an initial state
void EKalman::reset() {
	// copy the state from the model to the kalman member
	array2CvMat(model->getState(), kalman->state_post);
}

void EKalman::estimate(double* c){

	// input to the kalman filter for this step //////////////////////////////////////////////////////
	// actualize the control action
	array2CvMat(c, control);

	// actualize measurements and covariances
	// make sure to update them in the model (this is external to the Kalman)
	array2CvMat( model->getMeasurement(), measurement); // assign measurements
	array2CvMat( model->getMeasurementCovariance(), kalman->measurement_noise_cov); // assign measurement covariance matrix to kalman

	// actualize transition matrix
	array2CvMat(model->getTransitionMatrix(), kalman->transition_matrix);
	array2CvMat(model->getTransitionJacobian(), jacob);

    ///////////////////////////////////////////////////////////////////////////////////////////////////

	// prediction step: this substitutes the call to cvKalmanPredict for this non-linear system ///////
    CV_FUNCNAME( "cvKalmanPredict" );

    __BEGIN__;

    if( !kalman )
        CV_ERROR( CV_StsNullPtr, "" );

    /* update the state */
    /* x'(k) = A*x(k) */
    CV_CALL( cvMatMulAdd( kalman->transition_matrix, kalman->state_post, 0, kalman->state_pre ));

    if( control && kalman->CP > 0 )
        /* x'(k) = x'(k) + B*u(k) */
        CV_CALL( cvMatMulAdd( kalman->control_matrix, control, kalman->state_pre, kalman->state_pre ));

    /* update error covariance matrices */
    /* temp1 = jA*P(k) */
    CV_CALL( cvMatMulAdd( jacob, kalman->error_cov_post, 0, kalman->temp1 ));

    /* P'(k) = temp1*jAt + Q */
    CV_CALL( cvGEMM( kalman->temp1, jacob, 1, kalman->process_noise_cov, 1,
                     kalman->error_cov_pre, CV_GEMM_B_T ));

    __END__;
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // correction step
	cvKalmanCorrect( kalman, measurement );

	// we actualize the new state in the model
	model->updateState(kalman->state_post->data.db);

}



