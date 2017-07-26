/*********************************************************************
*
* Author: Carlos Hernandez @ ASLab
*
*	Parameters:
*			- file : for the text file containing the waypoints of the patrol mission
*			-
*	Description:
*	This file implements the mission_manager for a patrol mission in the higgs_autonomous_navigation
*	It is an action client of the move_base ros node: sends goals to it and subscribes to their
*	It result, so a call back is performed to send a new waypoint once the previous is achieved
*
*********************************************************************/

#include <vector>
#include <fstream>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//#include <tf/transform_datatypes.h>

#include <boost/thread.hpp>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class MissionManagerNode{

private:
	ros::Rate r;
	MoveBaseClient ac;
	ros::NodeHandle n;
	ros::Subscriber pose_sub;			// accepts new goal positions from rviz

	struct{
	class std::vector<move_base_msgs::MoveBaseGoal> path;  // the path to patrol
	std::vector<move_base_msgs::MoveBaseGoal>::iterator goal_iterator;
	} mission;

    // node parameters
    std::string mission_file;


    // reads the waypoints from a file and loads them in mission.path as a vector of goals
	void loadMission(std::string file){
		std::ifstream infile;
		infile.open(mission_file.c_str(), std::ifstream::in);
		if(!infile.is_open()){
			ROS_ERROR("Mision file not found");
		}

		while(infile.good())	{
			getWaypoint(infile);
		}
		// initialize mission iterator
		mission.goal_iterator = mission.path.begin();
	};

	// read waypoint from file line and append it to the mission.path
	void getWaypoint(std::istream& f){
		move_base_msgs::MoveBaseGoal g;
		g.target_pose.header.frame_id = "map";

		f >> g.target_pose.pose.position.x;
		f >> g.target_pose.pose.position.y;
		f >> g.target_pose.pose.position.z;
		f >> g.target_pose.pose.orientation.w;
		f >> g.target_pose.pose.orientation.x;
		f >> g.target_pose.pose.orientation.y;
		f >> g.target_pose.pose.orientation.z;

		mission.path.push_back(g);

	}

	void sendGoal(move_base_msgs::MoveBaseGoal g){

		//g.target_pose.header.stamp = ros::Time::now();

		// when sending a goal, also subscribe to the actionlib state so as to receive callback when it changes in the server
		ac.sendGoal(g,
		            boost::bind(&MissionManagerNode::done_CB, this, _1, _2)
		            );
	}

	void command_next_point(){

	}



public:
	MissionManagerNode(ros::NodeHandle nh) : ac("move_base", true), r(10) {
		n =nh;
		n.param( "file", mission_file, std::string("/usr/local/ros_aslab/higgs_autonomous_navigation/mission_manager/missions/patrol_sala_calculo_new.txt") );

		pose_sub = n.subscribe<geometry_msgs::PoseStamped>("rviz_goal", 0, boost::bind( &MissionManagerNode::rvizGoal_CB, this, _1 ));

	    ROS_INFO("Waiting for action server to start.");
	    ac.waitForServer();
		loadMission(mission_file);
	    ROS_INFO("Mission loaded.");

		// initialize mission iterator
		mission.goal_iterator = mission.path.begin();


	}

	void mission_loop(){

		// send the first goals, the rest are sent in the callback
		sendGoal(*mission.goal_iterator);

		while( n.ok() ){

		}// while

	}

	// Called once when the goal completes
	void done_CB(const actionlib::SimpleClientGoalState& state,
	              const move_base_msgs::MoveBaseResultConstPtr& result)	{

	    ROS_INFO("Finished in state [%s]", state.toString().c_str());

	    //move to next goal in the path
	    if(mission.goal_iterator++ == mission.path.end())
	    		mission.goal_iterator = mission.path.begin();

	    sendGoal(*mission.goal_iterator);

	}


	void rvizGoal_CB(const geometry_msgs::PoseStamped::ConstPtr& msg){
		ROS_INFO("---> Goal received from rViz: \nPose[ %f %f %f ] \n", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header = msg->header;
		goal.target_pose.pose = msg->pose;
		sendGoal(goal);
	}


};


int main(int argc, char** argv){
  ros::init(argc, argv, "mission_manager");
  ros::NodeHandle nh;

  MissionManagerNode manager(nh);
	printf("before loop");
  manager.mission_loop();

  return 0;
}
