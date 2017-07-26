#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>

#include <ros/ros.h>


#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>


using namespace std;



ros::Subscriber point_cloud_2_sub;

ros::Publisher point_cloud_pub;

bool first_arrived;

sensor_msgs::PointCloud point_cloud;

void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& point_cloud_2_ptr)
{


//    if (point_cloud_pub.getNumSubscribers() <= 0)
//    {
//      //ROS_DEBUG ("[point_cloud_converter] Got a PointCloud2 with %d points on %s, but no subscribers.", msg->width * msg->height, nh_.resolveName (points2_in_).c_str ());
//      return;
//    }

    // Convert to the old point cloud format
    if (!sensor_msgs::convertPointCloud2ToPointCloud(*point_cloud_2_ptr, point_cloud))
    {
      ROS_ERROR ("[point_cloud_converter] Conversion from sensor_msgs::PointCloud to sensor_msgs::PointCloud2 failed!");
      return;
    }

    first_arrived = true;
    ROS_INFO("PointCloud2 arrived!");
    //point_cloud_pub.publish (point_cloud);
}

void timerCallback(const ros::TimerEvent& e)
{

	if(first_arrived)
	{
		ROS_INFO("Publishing point cloud");
		point_cloud_pub.publish(point_cloud);
	}
}

// Startup routine.
int main( int argc, char** argv )
{
	ros::init(argc, argv, "PointCloud2_to_PointCloud");

	ROS_INFO("Starting PointCloud2 to PointCloud converter");

	ros::NodeHandle private_nh;


	string input_topic = "camera/depth/points";
	string output_topic = "camera/rgb/points_PointCloud";


	point_cloud_2_sub=private_nh.subscribe<sensor_msgs::PointCloud2>(input_topic,1,pointCloudCallback);
	point_cloud_pub = private_nh.advertise<sensor_msgs::PointCloud>(output_topic, 1);

	ros::Timer timer = private_nh.createTimer(ros::Duration(0.03), timerCallback);

	first_arrived = false;

	ROS_INFO("Converter ready!");

	ros::spin();
	return 0;
}
