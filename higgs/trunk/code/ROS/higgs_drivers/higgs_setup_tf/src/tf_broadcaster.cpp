#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  ros::Rate r(10);

  tf::TransformBroadcaster broadcaster;

  while(n.ok()){

   // for the laser
   broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),
        ros::Time::now(),"/base_laser_link", "/laser")); //modifed for Higgs

    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.248, 0.0, 0.35)),
        ros::Time::now(),"/base_link", "/base_laser_link")); //modifed for Higgs

    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),
        ros::Time::now(),"/base_footprint", "/base_link")); //modifed for Higgs
    
    // for the kinect
    broadcaster.sendTransform(
          tf::StampedTransform(
            tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.250, 0.02, 0.580)),
            ros::Time::now(),"/base_link", "/openni_camera")); //modifed for Higgs

    r.sleep();

  }
}
