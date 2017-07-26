/*
 * @author Francisco J. Arjonilla
 * Last Change: Fri Feb 25 12:00 PM 2011 C
 *
 * C++ dumb implementation for the CORBA servants in higgs that have associated a hardware device.
 * Method invocation is ignored and return null sensible values.
 * For testing purposes of CORBA clients.
 */
#include "servants.h"
#include <iostream>
#include <sstream>

using namespace higgs;
using namespace std;


/****************************************************************************************/
/************************************   Arduino   ***************************************/
/****************************************************************************************/

void Arduino_impl::cambiarReferencia(Referencia ref)
{
    ;
}

void Arduino_impl::encenderPin(Pin p)
{
    ;
}

void Arduino_impl::apagarPin(Pin p)
{
    ;
}

iv_data Arduino_impl::iv_motors()
{
    iv_data ret = {0., 12.};
    return ret;
}

iv_data Arduino_impl::iv_instrumentation()
{
    iv_data ret = {0., 12.};
    return ret;
}

iv_data Arduino_impl::iv_vaio()
{
    iv_data ret = {1., 0.};
    return ret;
}

double Arduino_impl::brujula()
{
    return 0.;
}

void Arduino_impl::acelerometro(double & x, double & y)
{
    x = 0.;
    y = 0.;
}

void Arduino_impl::TurnOn(Device dev)
{
    ;
}

void Arduino_impl::TurnOff(Device dev)
{
    ;
}




/****************************************************************************************/
/************************************     GPS     ***************************************/
/****************************************************************************************/

GPS_coords GPS_impl::position()
{
    GPS_coords ret;
    ret.latitude = 0.;
    ret.longitude = 0.;
    ret.height = 0.;
    return ret;
}

GPS_coords_UTM GPS_impl::position_UTM()
{
    GPS_coords_UTM ret;
    ret.northing = 0.;
    ret.easting  = 0.;
    ret.height   = 0.;
    ret.zone     = 0;
    ret.north    = true;
    return ret;
}

GPS_coords GPS_impl::std_deviation()
{
    GPS_coords ret;
    ret.latitude = 0.;
    ret.longitude = 0.;
    ret.height = 0.;
    return ret;
}

GPS_speed GPS_impl::speed()
{
    GPS_speed ret;
    ret.celerity = 0.;
    ret.heading = 0.;
    ret.height_speed = 0.;
    return ret;
}

higgs::GPS_solution_type GPS_impl::solution_type()
{
    return UNKNOWN;
}

CORBA::Short GPS_impl::satellites()
{
    return 0;
}

/****************************************************************************************/
/************************************    laser    ***************************************/
/****************************************************************************************/

laser_data * laser_impl::get_data()
{
    laser_data_var ret;
    ret->length(181);
    for (int i = 0; i < 181; i++)
      {
	ret[i].angle = ( ((float) (i - 90)) / 360.f ) * 2.f * 3.14159f;
	ret[i].distance = 1.f;
      }
    return ret._retn(); // Destruction managed by caller.
}

/****************************************************************************************/
/************************************    wrist    ***************************************/
/****************************************************************************************/

char * wrist_impl::get_full_state(higgs::wrist::wrist_axis axis)
{
    return CORBA::string_dup(
	    "Parameters are not accessible. \n"
	    "This is the dumb virtual servant for wrist.\n"
	    );
}

char * wrist_impl::get_status(higgs::wrist::wrist_axis axis)
{
    return CORBA::string_dup(
	    "Status is not accessible. \n"
	    "This is the dumb virtual servant for wrist.\n"
	    );
}

void wrist_impl::set_max_accel(CORBA::Float accel, higgs::wrist::wrist_axis axis)
{
    ;
}

void wrist_impl::set_max_speed(CORBA::Float speed, higgs::wrist::wrist_axis axis)
{
    ;
}

void wrist_impl::set_position(CORBA::Float position, higgs::wrist::wrist_axis axis)
{
    ;
}


void wrist_impl::set_diff_position(CORBA::Float diff, higgs::wrist::wrist_axis axis)
{
    ;
}


CORBA::Float wrist_impl::get_position(higgs::wrist::wrist_axis axis)
{
    return 0.f;
}

CORBA::Float wrist_impl::get_speed(higgs::wrist::wrist_axis axis)
{
    return 0.f;
}

CORBA::Float wrist_impl::get_current(higgs::wrist::wrist_axis axis)
{
    return 0.f;
}


CORBA::Boolean wrist_impl::is_ready(higgs::wrist::wrist_axis axis)
{
    return true;
}

void wrist_impl::wait(higgs::wrist::wrist_axis axis)
{
    ;
}


/****************************************************************************************/
/************************************  Pioneer2AT  **************************************/
/****************************************************************************************/

Pioneer2AT_State Pioneer2AT_impl::getRobotState    ()
{
    Pioneer2AT_State ret;
    ret.motorsEnabled = true;
    ret.sonarsEnabled = true;
    ret.emergencyStop = false;
    ret.connected = true;
    ret.running = false;
    ret.moving = false;
    ret.leftMotorStalled = false;
    ret.rightMotorStalled = false;
    ret.leftBreakTriggered = true;
    ret.rightBreakTriggered = true;
    ret.battery = 12.f;
    ret.newReadings = false;
    ret.timeStamp = getTime();
    return ret;
}
Pioneer2AT_Movement Pioneer2AT_impl::getRobotMovement ()
{
    Pioneer2AT_Movement ret;
    ret.speed = 0.f;
    ret.leftSpeed = 0.f;
    ret.rightSpeed = 0.f;
    ret.rotSpeed = 0.f;
    ret.maxSpeed = 0.f;
    ret.maxRotSpeed = 0.f;
    ret.absMaxSpeed = 0.f;
    ret.absMaxRotSpeed = 0.f;
    ret.accel = 0.f;
    ret.rotAccel = 0.f;
    ret.headingDone = true;
    ret.movementDone = true;
    ret.timeStamp = getTime();
    return ret;
}
Pioneer2AT_Position Pioneer2AT_impl::getRobotPosition ()
{
    Pioneer2AT_Position ret;
    ret.x = 0.f;
    ret.y = 0.f;
    ret.t = 0.f;
    ret.heading = 0.f;
    ret.distanceDiff = 0.f;
    ret.headingDiff = 0.f;
    ret.timeStamp = getTime();
    return ret;
}

void Pioneer2AT_impl::getRobotSensing  ( higgs::Pioneer2AT_Sensing_out sensing )
{
    ;
}

CORBA::Boolean Pioneer2AT_impl::isReady     () {return true;}
CORBA::Boolean Pioneer2AT_impl::isConnected () {return true;}
CORBA::Boolean Pioneer2AT_impl::isRunning   () {return false;}
CORBA::Boolean Pioneer2AT_impl::isStalled   () {return false;}
CORBA::Boolean Pioneer2AT_impl::isEmergency () {return false;}
CORBA::Boolean Pioneer2AT_impl::isMoving    () {return false;}
CORBA::Boolean Pioneer2AT_impl::isEnabled   () {return true;}
CORBA::Boolean Pioneer2AT_impl::isBreaked   () {return true;}
CORBA::Float Pioneer2AT_impl::getBattery  () {return 12.f;}
TimeStamp_Struct Pioneer2AT_impl::getTime()
{
    TimeStamp_Struct ret;
    ret.secs = 0;
    ret.usecs = 0;
    return ret;
}
void Pioneer2AT_impl::setTimeToNow() {;}

void Pioneer2AT_impl::init            () {;}
CORBA::Long Pioneer2AT_impl::connect         () {return 0;}
void Pioneer2AT_impl::start           () {;}
void Pioneer2AT_impl::stop            () {;}
void Pioneer2AT_impl::disconnect      () {;}
void Pioneer2AT_impl::finish          () {;}
void Pioneer2AT_impl::setCycleTime    ( CORBA::ULong ms ) {;}
CORBA::ULong Pioneer2AT_impl::getCycleTime    () {return 0;}
CORBA::ULong Pioneer2AT_impl::getRefreshTime  () {return 0;}
void Pioneer2AT_impl::setRefreshTime  ( CORBA::ULong ms ) {;}

CORBA::Float Pioneer2AT_impl::getVelocity         () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getMaxVelocity      () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getAbsMaxVelocity   () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getLeftVelocity     () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getRightVelocity    () {return 0.f;}    
CORBA::Float Pioneer2AT_impl::getAcceleration     () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getDeceleration     () {return 0.f;} 
CORBA::Float Pioneer2AT_impl::getRotVelocity      () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getMaxRotVelocity   () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getAbsMaxRotVelocity() {return 0.f;}
CORBA::Float Pioneer2AT_impl::getRotAcceleration  () {return 0.f;}
CORBA::Boolean Pioneer2AT_impl::isHeadingDone      () {return 0.f;}
CORBA::Boolean Pioneer2AT_impl::isMovementDone     () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getHeading          () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getHeadingDiff      () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getDistanceDiff     () {return 0.f;}

void Pioneer2AT_impl::enableMotors        (                                       ) {;}
void Pioneer2AT_impl::disableMotors       (                                       ) {;}
CORBA::Boolean Pioneer2AT_impl::areMotorsEnabled    (                                       ) {return true;}
void Pioneer2AT_impl::setVelocity         (    CORBA::Float vel                          ) {;}
CORBA::Boolean Pioneer2AT_impl::setMaxVelocity      (    CORBA::Float maxVel                      ) {return true;}
CORBA::Boolean Pioneer2AT_impl::setAbsMaxVelocity   (    CORBA::Float maxVel                      ) {return true;}
void Pioneer2AT_impl::setLRVelocity       (    CORBA::Float leftVel,    CORBA::Float rightVel ) {;}
void Pioneer2AT_impl::setAcceleration     (    CORBA::Float accel                       ) {;}
void Pioneer2AT_impl::setDeceleration     (    CORBA::Float decel                       ) {;}
void Pioneer2AT_impl::setRotVelocity      (    CORBA::Float rotVel                      ) {;}
CORBA::Boolean Pioneer2AT_impl::setMaxRotVelocity   (    CORBA::Float maxRotVel                   ) {return true;}
CORBA::Boolean Pioneer2AT_impl::setAbsMaxRotVelocity(    CORBA::Float maxRotVel                   ) {return true;}
CORBA::Boolean Pioneer2AT_impl::setAbsMaxRotAccel   (    CORBA::Float maxRotAccel                 ) {return true;}
CORBA::Boolean Pioneer2AT_impl::setAbsMaxRotDecel   (    CORBA::Float maxRotDecel                 ) {return true;}
void Pioneer2AT_impl::setRotAcceleration  (    CORBA::Float rotAccel                    ) {;}
void Pioneer2AT_impl::moveDistance        (    CORBA::Float distance                    ) {;}
void Pioneer2AT_impl::setHeading          (    CORBA::Float heading                     ) {;}
void Pioneer2AT_impl::setDeltaHeading     (    CORBA::Float delta                       ) {;}

CORBA::Float Pioneer2AT_impl::getX             () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getY             () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getTh            () {return 0.f;}
CORBA::Float Pioneer2AT_impl::getCompass       () {return 0.f;}
void Pioneer2AT_impl::resetPosition    () {;}

CORBA::Boolean Pioneer2AT_impl::hasSonars           () {return true;}
CORBA::Boolean Pioneer2AT_impl::areSonarsEnabled    () {return true;}
void Pioneer2AT_impl::enableSonars        () {;}
void Pioneer2AT_impl::disableSonars       () {;}
CORBA::Boolean Pioneer2AT_impl::hasFrontBumpers     () {return true;}    
CORBA::Boolean Pioneer2AT_impl::hasRearBumpers      () {return true;}
CORBA::UShort Pioneer2AT_impl::getNumSonars        () {return 16;}
CORBA::UShort Pioneer2AT_impl::getNumFrontBumpers  () {return 8;}
CORBA::UShort Pioneer2AT_impl::getNumRearBumpers   () {return 8;}
CORBA::UShort Pioneer2AT_impl::getClosestSonar     () {return 0;}
CORBA::ULong Pioneer2AT_impl::getClosestSonarRange() {return 0;}
CORBA::ULong Pioneer2AT_impl::getSonarRange       (    CORBA::UShort numSonar ) {return 0;}
CORBA::Boolean Pioneer2AT_impl::hasSonarNewReadings (    CORBA::UShort numSonar ) {return false;}

