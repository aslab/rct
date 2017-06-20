/*
   Author: Carlos Hernandez @ ASLab - UPM    www.aslab.org

	Converts PoseWithCovarianceStamped messages into PoseStamped
	to display in RViz
*/

#include <ros/ros.h>
#include "geometry_msgs/Quaternion.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"

#include "tf/tf.h"

#include <boost/random/normal_distribution.hpp> // for the noise
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>

class SimulatedCompassNode {

protected:
    ros::NodeHandle n;
	ros::Publisher imu_pub;
	ros::Subscriber odom_sub;	// to receive PoseWithCovariance
	sensor_msgs::Imu orientation_msg;
	double ref;	// initial reference angle (it should be 0, but just in case)
	bool first;
	double noise_std; // compass noise standard deviation
	boost::mt19937 gen;
	boost::normal_distribution<> normal_dist;
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > noise;             // glues randomness with mapping


public:

	SimulatedCompassNode(ros::NodeHandle nh):
		noise_std(0.02),           					// initialize noise
		normal_dist(0, noise_std),
		noise(gen, normal_dist)
	{
		first = true;

		// constant values of the Imu message
		orientation_msg.angular_velocity_covariance[0] = -1; // velocity unknown
		orientation_msg.linear_acceleration_covariance[0] = -1;

		/* orientation covariance
	  		 	 	1e6, 0.0, 0.0,   [x, y, z, x, y, z]
					0.0, 1e6, 0.0,
					0.0, 0.0, 0.2                  */
		orientation_msg.orientation_covariance[1] = orientation_msg.orientation_covariance[2] =
				orientation_msg.orientation_covariance[3] = orientation_msg.orientation_covariance[5] =
				orientation_msg.orientation_covariance[6] = orientation_msg.orientation_covariance[7] =
						0.0;
		orientation_msg.orientation_covariance[0] = orientation_msg.orientation_covariance[4] = 1e6;
		orientation_msg.orientation_covariance[8] = noise_std*noise_std; // replace by compass noise

		n = nh; //node handle

		// subscribe to topics
		odom_sub = n.subscribe<nav_msgs::Odometry>("base_pose_ground_truth", 1, boost::bind( &SimulatedCompassNode::odom2imu_CB, this, _1 ));

		// advertise published topics
		imu_pub = n.advertise<sensor_msgs::Imu>("compass_fake",1000);
	}

	virtual ~SimulatedCompassNode(){}


	void spin(){
		while( n.ok() ){
			ros::spinOnce();
		}
	}

	void odom2imu_CB(const nav_msgs::Odometry::ConstPtr& msg){
		if (first){
			first = false;
			ref = tf::getYaw(msg->pose.pose.orientation);
		}
		else{
			orientation_msg.header = msg->header;
			orientation_msg.orientation = tf::createQuaternionMsgFromYaw( tf::getYaw(msg->pose.pose.orientation) - ref + noise() ); // compass reading with noise
			imu_pub.publish(orientation_msg);
			ROS_INFO("Ref: %f \n Orientation: %f \n ", ref, tf::getYaw(msg->pose.pose.orientation) - ref + noise() );
		}
	}

};



int main(int argc, char** argv) {
  ros::init(argc, argv, "simulated_compass");
  ros::NodeHandle n;

  SimulatedCompassNode *node = new SimulatedCompassNode(n);

  node->spin();

  delete node;

  printf( "\nQuitting... \n" );
  return 0;

}
