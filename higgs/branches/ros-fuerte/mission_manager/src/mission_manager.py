#!/usr/bin/env python

# @author: Arturo Bajuelos, Carlos Hernandez
# @organization: ASLab
# @summary: node to handle patrol missions. It receives input from the mission file and dynamically from rviz, and commands accordingly the move_base action server
# @status: electric version - still not working

import sys
import getopt
import numpy as np
from collections import deque


import roslib; roslib.load_manifest('mission_manager')
import rospy
from std_msgs.msg import String, Bool
from move_base_msgs.msg import MoveBaseGoal, MoveBaseAction
import actionlib
from actionlib_msgs.msg import GoalStatusArray
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseStamped

import roslib.packages

action_lib_states = ["PENDING", "ACTIVE", "PREEMPTED", "SUCCEEDED","ABORTED","REJECTED",
"PREEMPTING", "RECALLING", "RECALLED", "LOST"]

current_status = 0

first_localization_set = False

filename = 'mission'
client = 0  # the actionlib client
mission_path = 0

def main(argv):
    global filename, client, mission_path
    
    rospy.init_node('mission_manager_node')
    
    # parsing of main arg ------------------------------
    try:
        opts, args = getopt.getopt(argv, "hf:", ['help', "file="])
    
    except getopt.GetoptError:
        # put here usage instructions
        sys.exit(2)
        
        
    for opt, arg in opts:                
        if opt in ("-h", "--help"):      
            # put here usage instructions
            print "Specify the filename of the mission with -f filename."                                   
            sys.exit()
        elif opt == '-f':
            filename = arg
            rospy.loginfo("mission file loaded")
        else :
            print "you have to specify the filename of the mission with -f filename."
            rospy.logfatal("you have to specify the filename of the mission with -f filename.")                                   
            sys.exit()
            
    #=====================================================================
    # Initialization and configuration
       
    rospy.loginfo("Mission manager node started")

    #Get mission path
    rospy.loginfo("Mission manager: Loading mission path")
    mission_path = np.fromfile(filename, dtype=float, sep=" ")
    mission_path = mission_path.reshape(np.size(mission_path,0)/7,7)
    mission_path = deque(mission_path)
    
    rospy.loginfo("Mission manager: Mission path successfully loaded")

   
    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    
    
    #Wait for action server of navigator
    while not client.wait_for_server(rospy.Duration(2.0)) and not rospy.is_shutdown():
        rospy.loginfo("Mission manager: Waiting for the move_base action server to come up")

    rospy.loginfo("Mission manager: move_base action is now available")

    # system is blocked till an initial localisation estimation is provided via rviz
    rospy.loginfo("Mission manager: Waiting for initial localization (use rviz to provide or other node)")
    rospy.sleep(rospy.Duration(2.0))
    wait_for_initial_localization()
    rospy.loginfo("Mission manager: Robot has first localization. Ready to send goals")

    #Subscribe to goal status to check on systems goal status
    # rospy.Subscriber("/move_base/status", GoalStatusArray, goal_status_callback)
    
    #Subscribe to rviz /goal topic so as to handle it in this action client
    rospy.Subscriber("/goal", PoseStamped, new_goal_callback)
    
    
    global current_status
    #=====================================================================
    # application code
    print "enter:\n - 'q' to end mission\n - 's' to stop the system\n - 'r' to resume patrolling"
    print "        (probably you'll need to enter 's' and 'q' twice because of a bug)"
    print "-- to move the robot somewhere else use rviz --\n"

   
    # start by sending the first goal -----------------------------------
    client.send_goal(get_current_waypoint(mission_path), done_cb=waypoint_reached_cb)
    print "sent first waypoint"
    
    # working loop -------------------------------------------------------
    while not rospy.is_shutdown():
        rospy.sleep(2)
        
        if raw_input() == 'q':
            rospy.loginfo("cancelling all goals")
            client.cancel_all_goals()     
            rospy.loginfo("Mission ended by user")
            return
        
        if raw_input() == 's':
            rospy.loginfo("cancelling all goals")
            client.cancel_all_goals()
            print "enter 'r' to resume patrolling"
            
        if raw_input() == 'r':
            client.send_goal(get_current_waypoint(mission_path), done_cb=waypoint_reached_cb)
    
    
    #Cancel all goals before exiting
    client.cancel_all_goals()    
    rospy.loginfo("Mission completed!")

#-- end of main ----------------------------------------------------------------------


#-- methods to wait for initial position -----------------------------------------------


def wait_for_initial_localization():
    global first_localization_set
    pub = rospy.Publisher("/localization_request", Bool)
    rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, initial_pose_callback)
    while not first_localization_set:
        pub.publish(Bool(True))
        rospy.sleep(0.5)
                
def initial_pose_callback(msg):
    global first_localization_set    
    first_localization_set = True

  
#------------------------------------------------------------------
#-- waypoints - goals management methods -----------------------------------

def goal_status_callback(msg):
    global current_status
    current_status = msg.status_list[0].status
#    rospy.loginfo("Current_status: %s",action_lib_states[current_status]) 

def get_next_waypoint(mission_path):
    goal = MoveBaseGoal()    
    goal.target_pose.header.frame_id = "/map"
    goal.target_pose.header.stamp = rospy.Time.now()
    mission_path.rotate(-1)
    waypoint = mission_path[0]
    goal.target_pose.pose.position.x = waypoint[0]
    goal.target_pose.pose.position.y = waypoint[1]
    goal.target_pose.pose.position.z = waypoint[2]
    goal.target_pose.pose.orientation.w = waypoint[3]
    goal.target_pose.pose.orientation.x = waypoint[4]
    goal.target_pose.pose.orientation.y = waypoint[5]
    goal.target_pose.pose.orientation.z = waypoint[6]
    print str(waypoint)
    return goal

# recursive in the sense that once the goal is achieved, that triggers this same function
def waypoint_reached_cb(state, result):
    global client
    # check if goal not achieved do nothing
    if action_lib_states[state] != "SUCCEEDED" :
        print "stop"
        return
    #if goal reached
    print "sending next goal"
    client.send_goal(get_next_waypoint(mission_path), done_cb=waypoint_reached_cb)

def get_current_waypoint(mission_path):
    goal = MoveBaseGoal()    
    goal.target_pose.header.frame_id = "/map"
    goal.target_pose.header.stamp = rospy.Time.now()
    waypoint = mission_path[0]
    goal.target_pose.pose.position.x = waypoint[0]
    goal.target_pose.pose.position.y = waypoint[1]
    goal.target_pose.pose.position.z = waypoint[2]
    goal.target_pose.pose.orientation.w = waypoint[3]
    goal.target_pose.pose.orientation.x = waypoint[4]
    goal.target_pose.pose.orientation.y = waypoint[5]
    goal.target_pose.pose.orientation.z = waypoint[6]
    print str(waypoint)
    return goal


#------------------------------------------------------------------
#-- dealing with external goals that temporarily override the patrolling 

def new_goal_callback(msg):
    global client
    print "external goal received"
    # send new goal to the action server (implicitly server forgets about previous goals)
    goal = MoveBaseGoal()
    goal.target_pose = msg
    client.send_goal(goal, done_cb=external_goal_reached_cb)
    
def external_goal_reached_cb(state, result):
    
    global client, mission_path
    # check if goal not achieved do nothing
    if action_lib_states[state] != "SUCCEEDED" :
        print "stop and cancel external goal"
        return
    print "external goal achieved, continuing patrol"
    client.send_goal(get_current_waypoint(mission_path), done_cb=waypoint_reached_cb)

#------------------------------------------------------------------

 
if __name__ == '__main__':

    try:
        main(sys.argv[1:]) # first argv is the name of the script, so we chop it off
    except rospy.ROSInterruptException: pass