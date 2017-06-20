/*
 * drive_higgs_odom.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: Carlos Hernandez
 */

#include <iostream>

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>

#include <higgs_navigation/OdomDriverAction.h>

#include <control_toolbox/pid.h>

//typedefs to help us out with the action server so that we don't hace to type so much
  typedef actionlib::SimpleActionServer<higgs_navigation::OdomDriverAction> OdomDriverActionServer;

class OdomDriver{

private:
  //! The node handle we'll be using
  ros::NodeHandle nh_;
  std::string action_name_;
  //! We will be publishing to the "cmd_vel" topic to issue commands
  ros::Publisher cmd_vel_pub_, action_goal_pub_;

  //! We will be listening to TF transforms as well
  tf::TransformListener& tf_;
  //! We will be subscribed to the driver_odom/goal geometry_msgs/PoseStamped as well
  ros::Subscriber goal_sub_;

  higgs_navigation::OdomDriverResult result;
  geometry_msgs::PoseStamped goal;
  double radians, distance;
  bool ang_done, dist_done, done; // to check whether the desired position is reached

  control_toolbox::Pid ang_controller, dist_controller;

protected:
  OdomDriverActionServer* as_;

public:
  OdomDriver(std::string name, tf::TransformListener& tf) :
		    tf_(tf),
		    as_(NULL) {

	as_ = new OdomDriverActionServer(ros::NodeHandle(), "odom_driver", boost::bind(&OdomDriver::executeCb, this, _1), false);

	//set up the publisher for the cmd_vel topic
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);

	ros::NodeHandle action_nh("odom_driver");
	action_goal_pub_ = action_nh.advertise<higgs_navigation::OdomDriverActionGoal>("goal", 1);

	//set up the subscriber for the driver_odom/goal
    //we'll provide a mechanism for some people to send goals as PoseStamped messages over a topic
    //they won't get any useful information back about its status, but this is useful for tools
    //like nav_view and rviz
    ros::NodeHandle simple_nh("odom_driver_simple");
    goal_sub_ = simple_nh.subscribe<geometry_msgs::PoseStamped>("goal", 1, boost::bind(&OdomDriver::goalCB, this, _1));

    // PID parameters
    ang_controller.initPid(-1.0, 0.0, 0.0, 0.3, -0.3);
    dist_controller.initPid(-0.05, 0.0, 0.6, 0.3, -0.3);
    ang_controller.reset();
    dist_controller.reset();


	ROS_INFO("--Odometric driver initialized-----------------------------\n");

    as_->start();
  }

  void goalCB(const geometry_msgs::PoseStamped::ConstPtr& gol){
	  ROS_DEBUG("In ROS goal callback, wrapping the PoseStamped in the action message and re-sending to the server.");
	  ROS_INFO("-- GOAL CAUGHT ----------------------------\n");
	  higgs_navigation::OdomDriverActionGoal action_goal;
	  action_goal.header.stamp = ros::Time::now();
	  action_goal.goal.target_pose = *gol;

	  action_goal_pub_.publish(action_goal);
  }

  void executeCb(const higgs_navigation::OdomDriverGoalConstPtr& goal_){
	  ROS_INFO("-- GOAL CONVERTED and caught again ----------------------------\n");
	  // get angle in radians and distance objectives from the goal
	  geometry_msgs::PoseStamped goal = goalToBaseFrame(goal_->target_pose);
	  radians = tf::getYaw(goal.pose.orientation);
	  while(radians < -M_PI) radians += 2*M_PI;
	  while(radians > M_PI) radians -= 2*M_PI;
	  ROS_INFO("Angle to goal: %f", radians);
	  distance = sqrt( (goal.pose.position.x)*(goal.pose.position.x) + (goal.pose.position.y)*(goal.pose.position.y) );
	  ROS_INFO("Distance to goal: %f", distance);

	  ang_done = dist_done = done = false;
	  radians = distance = 0.0;

	  double distance_now = 0.0, radians_now = 0.0;
	  geometry_msgs::PoseStamped goal_now;
	  geometry_msgs::Twist base_cmd;

	  ros::Rate rate(10.0);
	  ros::NodeHandle n;
	  ros::Time last_time = ros::Time::now();

	  while(n.ok()){
		  ROS_DEBUG("in the loop");
		  if(as_->isPreemptRequested()){

			  // in the case a new goal comes inn
			  if(as_->isNewGoalAvailable()){
		           //if we're active and a new goal is available, we'll accept it, but we won't shut anything down
		           higgs_navigation::OdomDriverGoal new_goal = *as_->acceptNewGoal();

		           // get angle in radians and distance objectives from the goal
		           goal = goalToBaseFrame(new_goal.target_pose);
		           radians = tf::getYaw(goal.pose.orientation);
		     	   while(radians < 0) radians += 2*M_PI;
		     	   while(radians > 2*M_PI) radians -= 2*M_PI;
		     	   distance = sqrt( (goal.pose.position.x)*(goal.pose.position.x) + (goal.pose.position.y)*(goal.pose.position.y) );
			  }

			  else {
				  //notify the ActionServer that we've successfully preempted
				  ROS_DEBUG("Move base preempting the current goal");
				  as_->setPreempted();

				  //we'll actually return from execute after preempting
				  return;
			  }
		  }//if

		  //Control: =================================

		  // get current angle in radians and distance to the goal
		  goal_now = goalToBaseFrame(goal_->target_pose);
		  radians_now = tf::getYaw(goal_now.pose.orientation);
		  while(radians_now < -M_PI) radians_now += 2*M_PI;
		  while(radians_now > M_PI) radians_now -= 2*M_PI;
		  ROS_INFO("radians now: %f", radians_now);
		  distance_now = sqrt( (goal_now.pose.position.x)*(goal_now.pose.position.x) + (goal_now.pose.position.y)*(goal_now.pose.position.y) );
		  ROS_INFO("distance now: %f", distance_now);

		  ros::Time time = ros::Time::now();

		  // calculate control action
		  double ang_comd = ang_controller.updatePid(radians_now - 0.0, time - last_time);
		  double dist_comd = dist_controller.updatePid(distance_now - 0.0, time - last_time);


		  // first head to goal
		  if (!ang_done){
			  if ( std::abs(radians_now) < 0.01 ){
				  ang_done = true;
				  base_cmd.angular.z = 0.0;
				  ROS_INFO("------angle done: %f", radians_now);
			  }
			  else{
				  base_cmd.angular.z = ang_comd;
				  ROS_INFO("command to turn: %f", base_cmd.angular.z);
			  }
		  }
		  //then move the distance to goal
		  else if(!dist_done){

			  if (distance_now < 0.06){
				  dist_done = true;
				  done = true;
				  base_cmd.linear.x = 0.0;
			  	  ROS_INFO("Succeeded: %s", action_name_.c_str());
			  	  ROS_INFO("turning speed: %f", base_cmd.angular.z);
			  	  as_->setSucceeded(higgs_navigation::OdomDriverResult(), "Goal achieved");
			  }
			  else{
				  base_cmd.linear.x = dist_comd;
				  base_cmd.angular.z = ang_comd;
				  ROS_INFO("command speed: %f", base_cmd.linear.x);
				  ROS_INFO("command to turn: %f", base_cmd.angular.z);
			  }
		  }
		  //send the drive command
		  cmd_vel_pub_.publish(base_cmd);

		  if(done)
			  return;
		  last_time = time;

		  rate.sleep();
		  //end control ====================================================
	  }//while

	  //if the node is killed then we'll abort and return
	  as_->setAborted(higgs_navigation::OdomDriverResult(), "Aborting on the goal because the node has been killed");
	  return;
  }

  // to convert the goal given in "odom" into the goal given into "base_footprint"
  geometry_msgs::PoseStamped goalToBaseFrame(const geometry_msgs::PoseStamped& goal_pose_msg){
	    tf::Stamped<tf::Pose> goal_pose, goal_base_pose;
	    poseStampedMsgToTF(goal_pose_msg, goal_pose);

	    //just get the latest available transform... for accuracy they should send
	    //goals in the frame of the planner
	    goal_pose.stamp_ = ros::Time();

	    // convert the goal into robot coordinates
	    try{
	      tf_.transformPose("base_footprint", goal_pose, goal_base_pose);
	      ROS_DEBUG("goal transformation done");  // eliminate when debugged
	    }
	    catch(tf::TransformException& ex){
	      ROS_INFO("Failed to transform the goal pose from %s into the %s frame: %s",
	          goal_pose.frame_id_.c_str(), "base_footprint", ex.what());
	      return goal_pose_msg;
	    }

	    geometry_msgs::PoseStamped goal_base_pose_msg;
	    tf::poseStampedTFToMsg(goal_base_pose, goal_base_pose_msg);
	    return goal_base_pose_msg;
  }

};


int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "odom_driver_node");
  tf::TransformListener tf(ros::Duration(10));

  OdomDriver driver(ros::this_node::getName(), tf);

  //ros::MultiThreadedSpinner s;
  ros::spin();

  return(0);

}
