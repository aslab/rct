#!/usr/bin/env python

import roslib; roslib.load_manifest('master_monitor')
import rospy
from rosgraph_msgs.msg import Log
from syscall import runCmd, runCmdOutput
from move_base_msgs.msg import MoveBaseGoal, MoveBaseAction
from geometry_msgs.msg import PoseStamped
import actionlib
import numpy as np

class ControlModel:
	current_goal = None

level = ["DEBUG", "INFO", "WARN", "ERROR", "FATAL"]

kinect_recov_launched = False

move_base_client = None

control_model = ControlModel()

def main():
    rospy.init_node('master_monitor')
    
    global move_base_client
    global control_model
    move_base_client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    current_goal_sub = rospy.Subscriber("/move_base_node/current_goal", PoseStamped, current_goal_callback) 
    
    rospy.Subscriber("/rosout", Log, callback)
    rospy.Subscriber("/rosout_agg", Log, callback)
    
    print "Master Listener Node Launched"
    while not rospy.is_shutdown():
		rospy.sleep(0.2)
		check_system()
		
		
def callback(data):
	global level
#	print "Level: "+level[int(np.sqrt(data.level))]+", From node " + data.name + ", a message: "+data.msg.strip()
	
	if str(data.msg).strip() == str("Connectivity Error: Could not find a common time /base_link and /map.") and data.name == "/move_base_node":
		kinect_reconfiguration()
	
#	if data.name == "/sicklms":
#		print "Level: "+level[int(np.sqrt(data.level))]+", From node " + data.name + ", a message: "+data.msg.strip()

	if data.name == "/sicklms" and str(data.msg).strip() == "woah! error!":
		kinect_reconfiguration()


def current_goal_callback(data):
	global control_model
	control_model.current_goal = data
	rospy.loginfo("Current goal received and stored")
	

def kinect_reconfiguration():
	global kinect_recov_launched
	global move_base_client
	global control_model
	
	if kinect_recov_launched:
		rospy.logwarn("Kinect Reconfiguration has been launched")
		return
	kinect_recov_launched = True
	
	while not move_base_client.wait_for_server(rospy.Duration(1.0)) and not rospy.is_shutdown():
		rospy.loginfo("Waiting for the move_base action server to come up")	
	
	if rospy.is_shutdown():
		return
	
	
	rospy.loginfo("Canceling all active goals")
	move_base_client.cancel_all_goals()
	
	
	rospy.loginfo("Launching Kinect Reconfiguration!")
		#Kill SICK laser node
	runCmd("rosnode kill /sicklms &")
	#Launch kinect node to replace laser_scan
	runCmd("roslaunch master_monitor kinect_reconfiguration.launch &")
	rospy.loginfo("Kinect Reconfiguration launcher has been launched.")
	
	
	rospy.sleep(10.0)
	
	
	rospy.loginfo("Re establishing model state...")
	restablish_state()
	rospy.loginfo("Model state loaded...")
	
	
def restablish_state():
	global control_model
	
	if control_model.current_goal != None:
		goal = MoveBaseGoal() 
		goal.target_pose = control_model.current_goal
		goal.target_pose.header.stamp = rospy.Time.now()
		move_base_client.send_goal(goal)
		rospy.loginfo("Last active goal re-established")

def check_system():
	global kinect_recov_launched
	
	if kinect_recov_launched:
		return
   # print "Rosnode list"
   	rosnode_list = runCmdOutput("rosnode list")
   	node_to_check="sicklms"
   	if rosnode_list.find(node_to_check) == -1:
   		rospy.logerr("Problem: "+node_to_check+" node not found. Launching reconfiguration")
   		kinect_reconfiguration()

if __name__ == '__main__':
    main()