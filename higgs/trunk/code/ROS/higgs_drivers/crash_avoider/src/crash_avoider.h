/** Crash Prevention
 * This class protects the higgs robot based on Pioneer 2AT reducing the allowed speed
 * at which it can move, based on the nearness of obstacles read by the sonar sensors.
 *
 * rho is the distance from the cir to the center of the robot.
 * omega is the rotational speed. Positive is counter-clockwise, looking from above the robot.
 *
 *
 *
 *
 *
 */
#ifndef CRASH_AVOIDER
#define CRASH_AVOIDER

class crash_avoider
{
public:
  double security_d; // Minimum security distance from robot edge to the obstacle. Default 0.05m.
  
  crash_avoider();

  // Use any of these four.
  // Reduce the speed values automatically.
  void reduce_speed(double & linear, double & angular, const double sonar_readings[16]);
  //void reduce_speed_cir(double & rho, double & omega);
private:
  double get_Vi(double rho, double omega);
  double get_Vd(double rho, double omega);
  double get_rho(double Vi, double Vd);
  double get_omega(double Vi, double Vd);

  // These two return the factor between 0 and 1 by which the speed should be reduced to move securely.
  //double reduction_factor(const double Vi, const double Vd);
  double reduction_factor_cir(const double rho, const double omega, const double sonar_readings[16]);

  double get_vmax(int sonar_index, const double sonar_readings[16]);

};

#endif
