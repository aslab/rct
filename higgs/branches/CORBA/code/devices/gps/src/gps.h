// Created on: Oct 2010
// Last Change: Fri Feb 25 01:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Header for the CORBA servant implementation for the GPS.
 */
#ifndef GPS_IMPL_H
#define GPS_IMPL_H
#include "gpsS.h"
#include "SerialLinkRS232.h"
#include <pthread.h>
#include <vector>
#include <string>
#include <time.h>

class GPS_impl : public POA_higgs::GPS
{
public:
    GPS_impl(const char * serial_device);

    virtual ~GPS_impl();

    virtual higgs::GPS_coords position();
    virtual higgs::GPS_coords_UTM position_UTM();
    virtual higgs::GPS_coords std_deviation();
    virtual higgs::GPS_speed speed();
    virtual higgs::GPS_solution_type solution_type();
    virtual CORBA::Short satellites();

private:
    SerialLinkRS232 device;
    pthread_t thread;

    static void * serial_parser(void * obj);
    typedef std::vector<std::string> fields_t;
    static fields_t parse(const std::string & input, const std::string & delimiter);
    static void update_info(GPS_impl * ref, const fields_t & fields);

    time_t last_msg_time;

    CORBA::Double latitude;
    CORBA::Double longitude;
    CORBA::Double height;
    CORBA::Double northing;
    CORBA::Double easting;
    CORBA::Short  zone;
    CORBA::Boolean north;
    CORBA::Double stdd_latitude;
    CORBA::Double stdd_longitude;
    CORBA::Double stdd_height;
    CORBA::Double celerity;
    CORBA::Double heading;
    CORBA::Double height_speed;
    CORBA::Short  satellites_d;
    higgs::GPS_solution_type sol_type;
};

#endif
