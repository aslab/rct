#include <iostream>
#include "crash_avoider.h"
#include <cmath>

using namespace std;

/* Parameters. Sets the position and angles of the sonars, the distance between wheels
 * and the parameters for determining the curve distance_to_obstacle - Vmax.
 * Unless specified, all parameters and variables are in meters and radians.
 */

const double security_d = 0.05; // Security distance before the robot crashes.
// The span in meters by which the speed is reduced between 0 and 1m/s, with
// Vmax = 0 occurring when the robot is at the crash + security distance.
const double distance_at_which_1meter_per_second_is_allowed = 1.5;

const double a = 0.2; // Distance from center to wheels.



const double pi = 3.141592653589793238462643383279502;
const double alpha[] = { // Angles of the sonars. 0 is right.
	0,
	2*pi/9,
	3*pi/9,
	4*pi/9,
	5*pi/9,
	6*pi/9,
	7*pi/9,
	pi,
	pi,
	11*pi/9,
	12*pi/9,
	13*pi/9,
	14*pi/9,
	15*pi/9,
	16*pi/9,
	0 };
const double x[] = { // X coordinate of the sonars.
	0.136,
	0.119,
	0.079,
	0.027,
	-0.027,
	-0.079,
	-0.119,
	-0.136,
	-0.136,
	-0.119,
	-0.079,
	-0.027,
	0.027,
	0.079,
	0.119,
	0.136 };
const double y[] = { // Y coordinate of the sonars.
	0.147,
	0.193,
	0.227,
	0.245,
	0.245,
	0.227,
	0.193,
	0.147,
	-0.144,
	-0.189,
	-0.223,
	-0.241,
	-0.241,
	-0.223,
	-0.189,
	-0.144 };
const double crash_d[] = { // Distance from the sonar to the robot edge.
	0.12,
	0.17,
	0.11,
	0.09,
	0.09,
	0.11,
	0.17,
	0.12,
	0.12,
	0.17,
	0.11,
	0.08,
	0.08,
	0.11,
	0.17,
	0.12 };



crash_avoider::crash_avoider()
{
  security_d = 0.05;
}

/* Modifies the linear and angular speeds of the robot.
 */
void crash_avoider::reduce_speed(double & linear, double & angular, const double sonar_readings[16])
{
    // Firstly convert linear and angular speeds to Vi and Vd.
    // Vi is the speed of the left wheels, positive going forward.
    // Vd is the speed of the right wheels, positive going forward.
    if (angular > 0.000001 && angular < 0.000001) // NaN protection.
	angular = 0.000001;
    double Vi = linear - angular * a;
    double Vd = linear + angular * a;

    // Convert to rho and omega.
    double rho = (Vi+Vd)/(Vi-Vd) * a;
    double omega = (Vd-Vi) / (2*a);

    double factor = reduction_factor_cir(rho, omega, sonar_readings);

    linear *= factor;
    angular *= factor;
}


double crash_avoider::get_Vi(double rho, double omega)
{
    return - ( (rho + a) * omega );
}
double crash_avoider::get_Vd(double rho, double omega)
{
    return - ( (rho - a) * omega );
}
double crash_avoider::get_rho(double Vi, double Vd)
{
    return ( (Vi + Vd) / (Vi - Vd) ) * a;
}
double crash_avoider::get_omega(double Vi, double Vd)
{
    return ( Vi - Vd ) / (2*a) ;
}



/** Calculates the effective reduction factor.
 */
double crash_avoider::reduction_factor_cir(const double rho, const double omega, const double sonar_readings[16])
{
  double reduction_factor = 1;
  double r; // Distance from cir to sonar.
  double gamma; // Position angle of the sonar with respect to the cir.
  double theta; // Angle between alpha and gamma.
  double v; // Absolute speed of the sonars. Perpendicular to cir.
  double vmax; // The maximum speed at which the sonar is allowed to approximate the obstacle. Colinear with sonar heading.

  cout << "INPUT (rho, omega) = (" << rho << ", " << omega << ")" << endl;

  for (int i = 0; i < 16; i++)
    {
      /* DEBUG */cout << " ************************** Iteration    ---> " << i << " <---" << endl;
      r = sqrt( (y[i]*y[i]) + ((rho - x[i])*(rho - x[i])) );
      gamma = atan(y[i]/(x[i] - rho));
      /* DEBUG */cout << "(r, gamma) = (" << r << ", " << gamma * 180 / pi << ")" << endl;

      theta = gamma + pi/2 - alpha[i];
      v = r * omega;

      vmax = get_vmax(i, sonar_readings);

      /* DEBUG */cout << "(v, theta) = (" << v << ", " << theta * 180 / pi << ")   Vmax = " << vmax << endl;

      /* DEBUG */cout << "(v*cos(theta), cos(theta)) = (" << v*cos(theta) << ", " << cos(theta) << ")" << endl;

      if (v*cos(theta) > vmax)
	{
	  double partial_factor = vmax / v;
	  /* DEBUG */cout << "### partial_factor: " << partial_factor << "  ###" << endl;
	  if (partial_factor < reduction_factor)
	      reduction_factor = partial_factor;
	}
    }
  /* DEBUG */cout << "reduction_factor: " << reduction_factor << endl;
  return reduction_factor;
}


/* Determines VMax with the distance to obstacle, using the parameters that define the curve.
 * The curve has two segments. The first one has 0 slope and has value of Vmax = 0. This stops
 * the robot in case it is trying to move towards a near obstacle.
 * The next segment increments linearly the speed from the crash distance plus a distance margin.
 */
double crash_avoider::get_vmax(int sonar_index, const double sonar_readings[16])
{
    double stop = crash_d[sonar_index] + security_d;
    double sonar = sonar_readings[sonar_index];
    if (sonar < stop)
	return 0;
    else
	/* line calculation:
	 * y=mx+b
	 * (1): 0=m*stop+b
	 * (2): 1=m*(stop+span_1mps)+b
	 * Resolving,
	 * (3): (2)-(1) m=1/span_1mps
	 * (3) in (1) b=stop/span_1mps
	 */
	return (sonar - stop) / distance_at_which_1meter_per_second_is_allowed;
}
