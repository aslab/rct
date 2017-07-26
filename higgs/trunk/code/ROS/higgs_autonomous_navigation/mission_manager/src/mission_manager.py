#!/usr/bin/env python

import roslib; roslib.load_manifest('mission_manager')
import rospy
from std_msgs.msg import String
from move_base_msgs.msg import MoveBaseGoal, MoveBaseAction
import actionlib
from actionlib_msgs.msg import GoalStatusArray
import numpy as np
from geometry_msgs.msg import PoseWithCovarianceStamped


import roslib.packages

action_lib_states = ["PENDING", "ACTIVE", "PREEMPTED", "SUCCEEDED","ABORTED","REJECTED",
"PREEMPTING", "RECALLING", "RECALLED", "LOST"]

current_status = 0

first_localization_set = False

def main():
    
    rospy.init_node('mission_manager_node')
    
    rospy.loginfo("Mission manager node started")
    
    
    rospy.loginfo("Mission manager: Loading mission path")
    #Get mission path
    pkg_path = roslib.packages.get_pkg_dir('mission_manager')
    mission_path = np.fromfile(pkg_path+"/missions/patrol_sala_calculo_py.txt", dtype=float, sep=" ")
    mission_path=mission_path.reshape(np.size(mission_path,0)/7,7)
    
    rospy.loginfo("Mission manager: Mission path successfully loaded")

   
    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    
    
    #Wait for action server of navigator
    while not client.wait_for_server(rospy.Duration(2.0)) and not rospy.is_shutdown():
        rospy.loginfo("Mission manager: Waiting for the move_base action server to come up")

    rospy.loginfo("Mission manager: move_base action is now available")


    rospy.loginfo("Mission manager: Waiting for initial localization")
    rospy.sleep(rospy.Duration(2.0))
    wait_for_initial_localization()
    rospy.loginfo("Mission manager: Robot has first localization. Ready to send goals")

    #Subscribe to goal status to check on systems goal status
    rospy.Subscriber("/move_base/status", GoalStatusArray, goal_status_callback)
    
    global current_status


    #Sending goals
    for i in range(0, np.size(mission_path,0)):
        print "Sending goal "+str(i+1)+":"
        print str(mission_path[i])
        goal = get_move_base_goal(mission_path, i)
        
        
        client.send_goal(goal)
        result = str(client.wait_for_result())
        
        if current_status != 3:
            rospy.loginfo("Mission manager: will not move for a while because goal is not mine!")
        
        rospy.loginfo("Mission manager: I wait for next goal")
        rospy.sleep(rospy.Duration(5.0))
        rospy.loginfo("Mission manager: Wait ended!")
            
        #Here I will wait for the goal to succeed
        while action_lib_states[current_status] !="SUCCEEDED" and not rospy.is_shutdown():
            print "Will note move to the next goal because state is "+action_lib_states[current_status]
            rospy.sleep(rospy.Duration(0.5))
        
        
        
        if rospy.is_shutdown():
            return

        print "Result "+result
    
    
    #Cancel all goals before exiting
    client.cancel_all_goals()
    
    rospy.loginfo("Mission completed!")

#    raw_input("Press Enter to cancel current goal...")
#    client.cancel_goal()
#
#    raw_input("Press Enter to cancel all goals...")
#    client.cancel_all_goals()


def wait_for_initial_localization():
    global first_localization_set

    rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, amcl_pose_callback)

    while not first_localization_set:
        rospy.sleep(0.2)
        
    
        
def amcl_pose_callback(msg):
    global first_localization_set
    
    first_localization_set = True


def goal_status_callback(msg):
    global current_status
    current_status = msg.status_list[0].status
#    rospy.loginfo("Current_status: %s",action_lib_states[current_status]) 

def get_move_base_goal(mission_path, i):
    goal = MoveBaseGoal()    
    goal.target_pose.header.frame_id = "/map"
    goal.target_pose.header.stamp = rospy.Time.now()
    
    goal.target_pose.pose.position.x = mission_path[i][0]
    goal.target_pose.pose.position.y = mission_path[i][1]
    goal.target_pose.pose.position.z = mission_path[i][2]
    goal.target_pose.pose.orientation.w = mission_path[i][3]
    goal.target_pose.pose.orientation.x = mission_path[i][4]
    goal.target_pose.pose.orientation.y = mission_path[i][5]
    goal.target_pose.pose.orientation.z =mission_path[i][6]

    return goal
    
if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass