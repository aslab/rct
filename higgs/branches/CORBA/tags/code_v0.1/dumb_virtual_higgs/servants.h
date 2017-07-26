/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#ifndef SERVANTS_H
#define SERVANTS_H

#include "ArduinoS.h"
#include "gpsS.h"
#include "laserS.h"
#include "wristS.h"
#include "Pioneer2ATS.h"

// Arduino implementation declarations.
class Arduino_impl : public POA_higgs::Arduino
{
public:
    virtual void cambiarReferencia(higgs::Referencia ref);
    virtual void encenderPin(higgs::Pin p);
    virtual void apagarPin(higgs::Pin p);
    virtual higgs::iv_data iv_motors();
    virtual higgs::iv_data iv_instrumentation();
    virtual higgs::iv_data iv_vaio();
    virtual double brujula();
    virtual void acelerometro(double & x, double & y);
    virtual void TurnOn(higgs::Device dev);
    virtual void TurnOff(higgs::Device dev);
};

// GPS implementation declarations.
class GPS_impl : public POA_higgs::GPS
{
public:
    virtual higgs::GPS_coords position();
    virtual higgs::GPS_coords_UTM position_UTM();
    virtual higgs::GPS_coords std_deviation();
    virtual higgs::GPS_speed speed();
    virtual higgs::GPS_solution_type solution_type();
    virtual CORBA::Short satellites();
};

// laser implementation declarations.
class laser_impl : public POA_higgs::laser
{
public:
    virtual higgs::laser_data * get_data();
};

// wrist implementation declarations.
class wrist_impl : public POA_higgs::wrist
{
public:
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
};

// Pioneer2AT implementation declarations.
class Pioneer2AT_impl : public POA_higgs::Pioneer2AT
{
public:
    // Data exchanging methods --------------------------------------------
    virtual higgs::Pioneer2AT_State    getRobotState    ();
    virtual higgs::Pioneer2AT_Movement getRobotMovement ();
    virtual higgs::Pioneer2AT_Position getRobotPosition ();

    virtual void getRobotSensing  ( higgs::Pioneer2AT_Sensing_out sensing );

    // Robot fast state checking ------------------------------------------
    virtual CORBA::Boolean isReady     ();         // True if software loaded correctly
    virtual CORBA::Boolean isConnected ();         // True if connection established+Ready
    virtual CORBA::Boolean isRunning   ();         // True if ARrobot running+Connected
    virtual CORBA::Boolean isStalled   ();         // True if some motor stalled
    virtual CORBA::Boolean isEmergency ();         // True if emergency situation
    virtual CORBA::Boolean isMoving    ();         // True if completing a movement
    virtual CORBA::Boolean isEnabled   ();         // True if motors enabled+Running
    virtual CORBA::Boolean isBreaked   ();         // True if any break triggered
    virtual CORBA::Float  getBattery  ();         // Battery voltage
    virtual higgs::TimeStamp_Struct getTime();
    virtual void setTimeToNow();

    // CORBA object remote control ----------------------------------------
    virtual void            init            ();
    virtual CORBA::Long     connect         ();
    virtual void            start           ();
    virtual void            stop            ();
    virtual void            disconnect      ();
    virtual void            finish          ();
    virtual void            setCycleTime    ( CORBA::ULong ms );
    virtual CORBA::ULong getCycleTime    ();
    virtual CORBA::ULong getRefreshTime  ();
    virtual void            setRefreshTime  ( CORBA::ULong ms );

    // Movement information -----------------------------------------------
    virtual CORBA::Float  getVelocity         ();
    virtual CORBA::Float  getMaxVelocity      ();
    virtual CORBA::Float  getAbsMaxVelocity   ();
    virtual CORBA::Float  getLeftVelocity     ();
    virtual CORBA::Float  getRightVelocity    ();    
    virtual CORBA::Float  getAcceleration     ();
    virtual CORBA::Float  getDeceleration     (); 
    virtual CORBA::Float  getRotVelocity      ();
    virtual CORBA::Float  getMaxRotVelocity   ();
    virtual CORBA::Float  getAbsMaxRotVelocity();
    virtual CORBA::Float  getRotAcceleration  ();
    virtual CORBA::Boolean isHeadingDone      ();
    virtual CORBA::Boolean isMovementDone     ();
    virtual CORBA::Float  getHeading          ();
    virtual CORBA::Float  getHeadingDiff      ();
    virtual CORBA::Float  getDistanceDiff     ();

    // Movement control ---------------------------------------------------
    virtual void    enableMotors        (                                       );
    virtual void    disableMotors       (                                       );
    virtual CORBA::Boolean areMotorsEnabled    (                                       );
    virtual void    setVelocity         (    CORBA::Float vel                          );
    virtual CORBA::Boolean setMaxVelocity      (    CORBA::Float maxVel                      );
    virtual CORBA::Boolean setAbsMaxVelocity   (    CORBA::Float maxVel                      );
    virtual void    setLRVelocity       (    CORBA::Float leftVel,    CORBA::Float rightVel );
    virtual void    setAcceleration     (    CORBA::Float accel                       );
    virtual void    setDeceleration     (    CORBA::Float decel                       );
    virtual void    setRotVelocity      (    CORBA::Float rotVel                      );
    virtual CORBA::Boolean setMaxRotVelocity   (    CORBA::Float maxRotVel                   );
    virtual CORBA::Boolean setAbsMaxRotVelocity(    CORBA::Float maxRotVel                   );
    virtual CORBA::Boolean setAbsMaxRotAccel   (    CORBA::Float maxRotAccel                 );
    virtual CORBA::Boolean setAbsMaxRotDecel   (    CORBA::Float maxRotDecel                 );
    virtual void    setRotAcceleration  (    CORBA::Float rotAccel                    );
    virtual void    moveDistance        (    CORBA::Float distance                    );
    virtual void    setHeading          (    CORBA::Float heading                     );
    virtual void    setDeltaHeading     (    CORBA::Float delta                       );

    // Position information -----------------------------------------------
    virtual CORBA::Float getX             ();
    virtual CORBA::Float getY             ();
    virtual CORBA::Float getTh            ();
    virtual CORBA::Float getCompass       ();
    virtual void  resetPosition    ();

    // Sensing ------------------------------------------------------------
    virtual CORBA::Boolean         hasSonars           ();
    virtual CORBA::Boolean         areSonarsEnabled    ();
    virtual void            enableSonars        ();
    virtual void            disableSonars       ();
    virtual CORBA::Boolean         hasFrontBumpers     ();    
    virtual CORBA::Boolean         hasRearBumpers      ();
    virtual CORBA::UShort  getNumSonars        ();
    virtual CORBA::UShort  getNumFrontBumpers  ();
    virtual CORBA::UShort  getNumRearBumpers   ();
    virtual CORBA::UShort  getClosestSonar     ();
    virtual CORBA::ULong   getClosestSonarRange();
    virtual CORBA::ULong   getSonarRange       (    CORBA::UShort numSonar );
    virtual CORBA::Boolean         hasSonarNewReadings (    CORBA::UShort numSonar );
};

#endif
