// Created on: November 2010
// Last Change: Fri Feb 25 03:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Declaration of the CORBA servant.
 */
#ifndef __WRIST_HPP
#define __WRIST_HPP

#include <stdlib.h>
#include <stdio.h>

#include "SerialLinkRS232.h"
#include "powercube_telegram.h" 
#include "wristS.h"


#define POWERCUBE_PITCH	13
#define POWERCUBE_ROLL	14

class wrist_servant : public POA_higgs::wrist
{
public:
    wrist_servant(const char * serial_device);
    ~wrist_servant();

    virtual char * get_full_state(higgs::wrist::wrist_axis axis);
    virtual char * get_status(higgs::wrist::wrist_axis axis);

    virtual void set_max_speed(CORBA::Float speed, higgs::wrist::wrist_axis axis);
    virtual void set_max_accel(CORBA::Float accel, higgs::wrist::wrist_axis axis);

    virtual void set_position(CORBA::Float position, higgs::wrist::wrist_axis axis);
    virtual void set_diff_position(CORBA::Float diff, higgs::wrist::wrist_axis axis);

    virtual CORBA::Float get_position(higgs::wrist::wrist_axis axis);
    virtual CORBA::Float get_speed   (higgs::wrist::wrist_axis axis);
    virtual CORBA::Float get_current (higgs::wrist::wrist_axis axis);

    virtual CORBA::Boolean is_ready(higgs::wrist::wrist_axis axis);
    virtual void wait(higgs::wrist::wrist_axis axis);
    //void test();

private:
    SerialLinkRS232 device;

    CORBA::Float position_pitch;
    CORBA::Float position_roll;

    void reset();
    PowerCubeModuleState cube_state(higgs::wrist::wrist_axis axis);
    static int adr(higgs::wrist::wrist_axis axis);

    static void * check_supervisor(void *);
    pthread_t supervisor_thread;

    // For restoring after reset in case of error.
    static float max_speed_pitch, max_accel_pitch, max_speed_roll, max_accel_roll;
};

#endif // __WRIST_HPP
