// Created on: Spring 2010
// Last Change: Fri Feb 25 01:00 PM 2011 C
/**
 * Modified by:
 * \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Library for controlling the Laser SICK
 *
 * Original code:
 * Contributed by Paloma de la Puente del grupo de Robótica Móvil.
 */

// ProtLMS.h: interface for the CProtLMS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTLMS_H__19D356B1_EA11_4C05_8CD7_4931CF9CE513__INCLUDED_)
#define AFX_PROTLMS_H__19D356B1_EA11_4C05_8CD7_4931CF9CE513__INCLUDED_

#include "PortCOM.h"

#define PI 3.14159265358979

#define CRC16_GEN_POL 0x8005

#define PROT_LMS_OK						0
#define PROT_LMS_ERROR					-1
#define PROT_LMS_ERROR_NACK				-2
#define PROT_LMS_ERROR_MISS_ACK			-3
//#define PROT_LMS_ERROR_ANSWER_TIMEOUT	-4
#define PROT_LMS_ERROR_ANSWER_LENGTH	-5
//#define PROT_LMS_ERROR_READFILE		-6
#define PROT_LMS_ERROR_TELEGRAM_FORMAT  -7
#define PROT_LMS_ERROR_TELEGRAM_NACK	-8
#define PROT_LMS_ERROR_TELEGRAM_CRC     -9
#define PROT_LMS_ERROR_TELEGRAM_STATUS  -10
#define PROT_LMS_ERROR_BAD_PARAMETER	-11
#define PROT_LMS_ERROR_OPERATION_ABORTED	-12
#define PROT_LMS_ERROR_DATA_EXPECTED	-13

#define PROT_LMS_UNIT_MM		1
#define PROT_LMS_UNIT_CM		2
#define PROT_LMS_UNIT_10_CM		3

#define PROT_LMS_MAX_RANGE_8M		8.191f
#define PROT_LMS_MAX_RANGE_16M		16.383f
#define PROT_LMS_MAX_RANGE_32M		32.767f

//ESPECIAL MODES
#define PROT_LMS_MODE_NOT_INIT		-1
#define PROT_LMS_MODE_INSTALLATION		0x00
//#define PROT_LMS_MODE_CALIBRATION		0x01
//#define PROT_LMS_MODE_RESET_PASSWD		0x02
//#define PROT_LMS_MODE_DIAGNOSTIC		0x10
//MONITORING MODES
//#define PROT_LMS_MODE_ALL_SCAN_CONT		0x24
#define PROT_LMS_MODE_SCAN_ON_REQUEST	0x25  //default at startup
//Monitoring with parameters
//#define PROT_LMS_MODE_1_VALUE_CONT		0x29




class ProtLMS  
{
public:
    ProtLMS();
    virtual ~ProtLMS();
    int Init(const char device[]);
    void Done();
    //This is same to ChangeMode 0x40,0x41....
    int ChangeMode(int mode);
    int ChangeBaudRate(int baud);
    int ChangeMaxRange(float max_range);
    int ChangeVariant(int scan_angle,float scan_resolution);

    int MeasuredValuesAll(float* measures_x,float* measures_y,int* reflec,int* num_measures);
    int MeasuredValuesAll(float* measures,int* num_measures);
    int MeasuredValuesAll(int* num_measures,int* measures);

    //NOT NOW	
    int ActivateLaser(bool active);
    int ChangeModeReflectPartCont(int num_part,int* begin_part,int* end_part);

    int LMSType(char* cad);//Only returns a string with LMS ID
    int Status(char* cad);
    int MeasuredValuesReflect(float* measures_x,float* measures_y,int* reflec,int* num_measures);
    void Reset();

    int Start();
    int Stop();
    int readLMSdata(int* num, int* values);

private:
    bool contin;
    PortCOM port;	

    unsigned char telegram_out[1000];
    unsigned char telegram_in[1000];
    int num_read;

    //parametros actuales del escaner
    int mode;
    float max_range;
    int scan_angle;
    float scan_resolution;
    int num_measures;
    //precalculados
    float sen_alfa[401];
    float cos_alfa[401];
};

#endif // !defined(AFX_PROTLMS_H__19D356B1_EA11_4C05_8CD7_4931CF9CE513__INCLUDED_)
