/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include "gps.h"
#include <iostream>
#include <sstream>

using namespace higgs;
using namespace std;

GPS_impl::GPS_impl(const char * serial_device)
: device(serial_device)
{
    if(!device.Open())
      {
	std::cerr << "Could not open serial device " << serial_device << std::endl;
	throw 0;
      }

    unsigned char init_message[] =
	"LOG BESTPOSA ONTIME 1\r\n"
	"LOG BESTVELA ONTIME 1\r\n"
	"LOG BESTUTMA ONTIME 1\r\n";
    device.Send(init_message, strlen((char*)init_message));

    last_msg_time = time(0);
    sol_type = PENDING;

    if (pthread_create(&thread, 0, serial_parser, this))
      {
	std::cerr << "Could not create thread." << std::endl;
	throw 0;
      }
}

GPS_impl::~GPS_impl()
{
    device.Close();
    pthread_cancel(thread);
}

GPS_coords GPS_impl::position()
{
    GPS_coords ret;
    ret.latitude = latitude;
    ret.longitude = longitude;
    ret.height = height;
    return ret;
}

GPS_coords_UTM GPS_impl::position_UTM()
{
    GPS_coords_UTM ret;
    ret.northing = northing;
    ret.easting  = easting;
    ret.height   = height;
    ret.zone     = zone;
    ret.north    = north;
    return ret;
}

GPS_coords GPS_impl::std_deviation()
{
    GPS_coords ret;
    ret.latitude = stdd_latitude;
    ret.longitude = stdd_longitude;
    ret.height = stdd_height;
    return ret;
}

GPS_speed GPS_impl::speed()
{
    GPS_speed ret;
    ret.celerity = celerity;
    ret.heading = heading * 2 * 3.14159265 / 360;
    ret.height_speed = height_speed;
    return ret;
}

higgs::GPS_solution_type GPS_impl::solution_type()
{
    return sol_type;
}

CORBA::Short GPS_impl::satellites()
{
    return satellites_d;
}

GPS_impl::fields_t GPS_impl::parse(const string & input, const string & delimiter)
{
    fields_t ret(1);
    ret.reserve(30);
    int field = 0;
    for (size_t i = 0; i < input.length(); i++)
      {
	if (delimiter.find_first_of(input[i]) != string::npos) // If delimiter
	  {
	    field++;
	    ret.push_back(string());
	  }
	else
	    ret[field].append(1,input[i]);
      }
    return ret;
}

template<class T>
T convert_string(const string &str)
{
    stringstream s;
    s << str;
    T ret;
    s >> ret;
    return ret;
}


void GPS_impl::update_info(GPS_impl * ref, const fields_t & fields)
{
    try{
	if (fields[0].compare("BESTPOSA") == 0 && fields.size() == 32)
	  {
	    ref->latitude = convert_string<double>(fields[12]);
	    ref->longitude = convert_string<double>(fields[13]);
	    ref->height = convert_string<double>(fields[14]);
	    ref->stdd_latitude = convert_string<double>(fields[17]);
	    ref->stdd_longitude = convert_string<double>(fields[18]);
	    ref->stdd_height = convert_string<double>(fields[19]);
	    ref->satellites_d = convert_string<int>(fields[24]);

	    // Announce that solution has been found.
	    const string & solution_status = fields[10];
	    const string & solution_type = fields[11];
	    if (solution_status.compare("SOL_COMPUTED") == 0)
	      {
		if (solution_type.compare("SINGLE") == 0)
		    ref->sol_type = SINGLE;
		else if (solution_type.compare("WAAS") == 0)
		    ref->sol_type = SBAS;
		else if (solution_type.compare("NARROW_FLOAT") == 0)
		    ref->sol_type = DIFFERENTIAL;
		else
		    ref->sol_type = UNKNOWN;
	      }
	    else
	      {
		if (solution_status.compare("INSUFFICIENT_OBS") == 0)
		    ref->sol_type = PENDING;
		else
		    ref->sol_type = UNKNOWN;
	      }
	    cout << "[" << ref->last_msg_time << "] " << solution_status << " type " << solution_type << endl;
	  }
	else if (fields[0].compare("BESTUTMA") == 0 && fields.size() == 34)
	  {
	    ref->northing = convert_string<double>(fields[14]);
	    ref->easting = convert_string<double>(fields[15]);
	    ref->zone = convert_string<int>(fields[12]);
	    ref->north = convert_string<char>(fields[17]) >= 'N';
	  }
	if (fields[0].compare("BESTVELA") == 0 && fields.size() == 19)
	  {
	    ref->celerity = convert_string<double>(fields[14]);
	    ref->heading = convert_string<double>(fields[15]);
	    ref->height_speed = convert_string<double>(fields[16]);
	  }
    }catch(...){}
}

void * GPS_impl::serial_parser(void * obj)
{
    GPS_impl * ref = (GPS_impl *)obj;
    unsigned char c;
    std::string buffer;
    while (1)
      {
	ref->device.Receive(&c, 1);
	if (c == '\r')
	  {
	    size_t begin = buffer.find_last_of("#");
	    if (begin == string::npos)
		continue;
	    buffer.erase(0, begin + 1);

	    fields_t fields = parse(buffer, ",;*");
	    buffer.clear();

	    //for (size_t i = 0; i < fields.size(); i++)
		//cout << "Field " << i << ": " << fields[i] << endl;
	    //cout << "-------------------------------------------"<<endl;
	    update_info(ref, fields);
	    ref->last_msg_time = time(0);
	  }
	else
	    buffer += c;

	// Track receive time. If it is longer than 3 seconds restart.
	time_t now = time(0);
	if (now > ref->last_msg_time + 3)
	  {
	    cout << "More than 3s since last message received! Reverting to unknown state." << endl;
	    ref->sol_type = UNKNOWN;
	  }

      }
    return 0;
}

