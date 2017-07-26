/*
   Author: Carlos Hernandez @ ASLab - UPM    www.aslab.org

	Converts PoseWithCovarianceStamped messages into PoseStamped
	to display in RViz
*/

#include <ros/ros.h>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"


class PoseConverterNode {

protected:
    ros::NodeHandle n;
	ros::Publisher pose_pub;
	ros::Subscriber posecov_sub;	// to receive PoseWithCovariance
	geometry_msgs::PoseStamped pose_msg;
    	std::string publish_frame;	// ros param

public:

	PoseConverterNode(ros::NodeHandle nh){
		n = nh;

		n.param( "publish_frame", publish_frame, std::string("odom_combined") );

		// subscribe to topics
		posecov_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("pose_cov", 1, boost::bind( &PoseConverterNode::poseWcov_CB, this, _1 ));

		// advertise published topics
		pose_pub = n.advertise<geometry_msgs::PoseStamped>("pose",1000);
	}

	virtual ~PoseConverterNode(){}


	void spin(){
		while( n.ok() ){
			ros::spinOnce();
		}
	}

	void poseWcov_CB(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
		pose_msg.header = msg->header;
		pose_msg.header.frame_id = publish_frame;
		pose_msg.pose = msg->pose.pose;
		pose_pub.publish(pose_msg);
	}

};



int main(int argc, char** argv) {
  ros::init(argc, argv, "posewcov2pose");
  ros::NodeHandle n;

  PoseConverterNode *node = new PoseConverterNode(n);

  node->spin();

  delete node;

  printf( "\nQuitting... \n" );
  return 0;

}
