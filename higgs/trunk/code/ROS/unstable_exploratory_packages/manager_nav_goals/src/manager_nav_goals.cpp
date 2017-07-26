/*********************************************************************
*
* Author: Carlos Hernandez @ ASLab
*
*********************************************************************/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <termios.h>
#include <sys/poll.h>
//#include <tf/transform_datatypes.h>

#include <boost/thread.hpp>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class ManagerNode{

private:
	MoveBaseClient ac;
	ros::NodeHandle n;
	ros::Subscriber pose_sub;
	move_base_msgs::MoveBaseGoal goal;  // the current goal

	bool no_goal;

	int kfd;
	struct termios cooked, raw;

	void sendGoal(move_base_msgs::MoveBaseGoal g){
		ac.sendGoal(g,
		            boost::bind(&ManagerNode::done_CB, this, _1, _2)
		            );
	}


public:
	ManagerNode() : ac("Manager_nav_goals", false) {
		pose_sub = n.subscribe<geometry_msgs::PoseStamped>("rviz_goal", 0, boost::bind( &ManagerNode::rvizGoal_CB, this, _1 ));

		no_goal =true;

		// get the console in raw mode
		kfd = 0;
		tcgetattr(kfd, &cooked);
		memcpy(&raw, &cooked, sizeof(struct termios));
		raw.c_lflag &=~ (ICANON | ECHO);
		raw.c_cc[VEOL] = 1;
		raw.c_cc[VEOF] = 2;
		tcsetattr(kfd, TCSANOW, &raw);
	}

	void loop(){
		char c;
		ros::Rate r(10);  // frequency of the loop

		puts("\n------------------------------------------------------------");
		puts("Manager Node already dealing with navigation Goals");
		puts("------------------------------------------------------------");
		puts("c : cancels current goal");
		puts("d : shuts down the Manager");
		puts("s : shows the current goal");

		struct pollfd ufd;
		ufd.fd = kfd;
		ufd.events = POLLIN;

		while( n.ok() ){
			int num;
			if((num = poll(&ufd, 1, 250)) < 0){
				perror("poll():");
				return;
			}
			else if(num > 0){
				if(read(kfd, &c, 1) < 0){
					perror("read():");
					return;
				}
			}
			else
				continue;

			switch(c){
				case 'c':
					ROS_INFO("Cancelling goal...\n");
					ac.cancelGoal();
					no_goal = true;
					ROS_INFO("Goal Cancelled!\n");
					break;
				case 'd':
					ROS_INFO("Shutting down Manger node...\n");
					ros::shutdown();
					ROS_INFO("Done. Bye Manager! \n");
					break;
				case 's':  // show current goal
					if(no_goal)
						ROS_INFO("---> No goal \n");
					else
						ROS_INFO("---> Goal: \nPose[ %f %f %f ] \n", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y, goal.target_pose.pose.position.z);
					break;
			}//switch

			ros::spinOnce();
			r.sleep();

		}// while

	}

	void rvizGoal_CB(const geometry_msgs::PoseStamped::ConstPtr& msg){
		no_goal = false;
		// to solve: this prints seem to queue and only appears once a key is pressed
		ROS_INFO("---> Goal received from rViz: \nPose[ %f %f %f ] \n", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
		goal.target_pose.header = msg->header;
		goal.target_pose.pose = msg->pose;
		sendGoal(goal);

	}

	void done_CB(const actionlib::SimpleClientGoalState& state,
	              const move_base_msgs::MoveBaseResultConstPtr& result)
	{
	    ROS_INFO("Finished in state [%s]", state.toString().c_str());
	}

};


int main(int argc, char** argv){
  ros::init(argc, argv, "Manager_nav_goals");
  ManagerNode manager;

  manager.loop();

  return 0;
}
