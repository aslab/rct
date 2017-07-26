#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include <ros/ros.h>

#include <sensor_msgs/Imu.h>

//Includes for CORBA
#include "CORBA_utils.h"
#include "idl_compiled/ArduinoC.h"
#include "idl_compiled/CosNamingC.h"

#include "tf/tf.h"


using namespace std;

double compass_reading = 0;

ros::Publisher imu_pub;


int loop_rate_hz = 20;

sensor_msgs::Imu imu_data;

higgs::Arduino_var corba_arduino;


void angle_normalization(double *ang){
	while(*ang <= -M_PI)
		*ang += 2*M_PI;
	while (*ang > M_PI)
		*ang -= 2*M_PI;
}

void setup_imu_msg(){

	imu_data.header.frame_id = "base_link";

	//Orientation - all these values must be float
	//imu_data.orientation.setRPY(0, 0, compass_reading);
	imu_data.orientation.x = 0;
	imu_data.orientation.y = 0;
	imu_data.orientation.z = 0;
	imu_data.orientation.w = 0;

	boost::array<double, 9> orientation_covariance =
										{{1e-6, 0, 0,
										0., 1e-6, 0.,
										0., 0., 0.05}};
	imu_data.orientation_covariance = orientation_covariance;

	//Angular velocity
	imu_data.angular_velocity.x = 0;

	imu_data.angular_velocity.y = 0;
	imu_data.angular_velocity.z = 0;

	boost::array<double, 9> angular_velocity_covariance =
												{{-1., 0, 0,
												   0, -1., 0,
												    0, 0, -1.}};
	imu_data.angular_velocity_covariance = angular_velocity_covariance;



	//Linear acceleration
	imu_data.linear_acceleration.x = 0;
	imu_data.linear_acceleration.y = 0;
	imu_data.linear_acceleration.z = 0;

	boost::array<double, 9> linear_acceleration_covariance =
												{{-1., 0, 0,
												   0, -1., 0,
												   0, 0, -1.}};

	imu_data.linear_acceleration_covariance = linear_acceleration_covariance;

}

void publish_Imu()
{
	imu_data.header.stamp = ros::Time::now();


	// get orientation


	//Orientation - all these values must be float
	//imu_data.orientation.setRPY(0, 0, compass_reading);
	//imu_data.orientation.z = sin(compass_reading);
	//imu_data.orientation.w = cos(compass_reading);

	imu_data.orientation = tf::createQuaternionMsgFromYaw(compass_reading);



	/** Publishing Imu data **/

	double compass_reading_degree = compass_reading * 180 / M_PI;
	ROS_DEBUG("Publishing compass value (%lg degree) at rate %d hz",compass_reading_degree, loop_rate_hz);
	imu_pub.publish(imu_data);


}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "higgs_arduino");
	ROS_INFO("Higgs Arduino CORBA ROS node initialized");

	ros::NodeHandle private_nh;

	//Advertise topic
	imu_pub = private_nh.advertise<sensor_msgs::Imu>("/higgs_arduino/Imu", 10);



	//Advertise param
	private_nh.param("/higgs_arduino/loop_rate_hz", loop_rate_hz, 10);

	//Create loop rate to set program rate
	ros::Rate loop_rate(loop_rate_hz);

	/** CORBA Initialization**/
	ROS_INFO("Initializing Arduino CORBA client");
	CORBA_BEGIN_CLIENT(argc, argv);
	ROS_INFO("CORBA client initialized");
	ROS_INFO("Getting reference for Arduino CORBA Servant");
	//Get the reference for Arduino
	CORBA_GET_REFERENCE(higgs::Arduino, arduino_v, "Arduino");
	ROS_INFO("Reference for Arduino CORBA Servant Gotten!");
	corba_arduino = arduino_v;

	ROS_INFO("Publishing IMU of compass reading:");

	double compass_reference = corba_arduino->brujula();
	ROS_INFO("Reference angle: %f", compass_reference);

	setup_imu_msg();

	//Main loop
	while(ros::ok())
	{
		/*Get compass reading from Arduino CORBA Servant**/
		compass_reading = corba_arduino->brujula() - compass_reference;
		angle_normalization(&compass_reading);

		/*Publish IMU data into topic**/
		publish_Imu();
		ros::spinOnce();
		loop_rate.sleep();
	}

	ROS_INFO("Stopping Arduino CORBA Client");
	CORBA_END_CLIENT;

	printf("\nHiggs Arduino CORBA ROS node successfully ended\n");
	return 0;
}
