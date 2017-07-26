#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include <joy/Joy.h>

#include <math.h>


class TeleopHiggs
{
public:
  TeleopHiggs();

private:
  void joyCallback(const joy::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  int reset;
  
};


TeleopHiggs::TeleopHiggs():
  linear_(2),
  angular_(1)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("Higgs/command_velocity", 1);


  joy_sub_ = nh_.subscribe<joy::Joy>("joy", 10, &TeleopHiggs::joyCallback, this);

  reset=0;

}

void TeleopHiggs::joyCallback(const joy::Joy::ConstPtr& joy)
{

	geometry_msgs::Twist cmdvel;
	if( joy->buttons[3] )
	{
	  reset=0;
	  cmdvel.angular.z = -0.05*(joy->axes[angular_])*abs(joy->axes[angular_]);
	  cmdvel.angular.x = 0.0;
	  cmdvel.angular.y = 0.0;
	  cmdvel.linear.x = 0.1*(joy->axes[linear_]+4)*abs(joy->axes[linear_]); // 4 is the offset to have wiimote 45º
	  cmdvel.linear.z = 0.0;
	  cmdvel.linear.y = 0.0;
	  vel_pub_.publish(cmdvel);
	}

	else if(reset==0)
	{
	  reset=1;
	  cmdvel.angular.z = 0.0;
	  cmdvel.angular.x = 0.0;
	  cmdvel.angular.y = 0.0;
	  cmdvel.linear.x = 0.0;
	  cmdvel.linear.z = 0.0;
	  cmdvel.linear.y = 0.0;
	  vel_pub_.publish(cmdvel);
	}
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_Higgs");
  TeleopHiggs teleop_Higgs;

  ros::spin();
}
