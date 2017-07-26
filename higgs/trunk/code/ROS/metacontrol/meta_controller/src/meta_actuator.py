#!/usr/bin/env python

import roslib; roslib.load_manifest('meta_controller')
import rospy
from rosgraph_msgs.msg import Log
from syscall import runCmd, runCmdOutput
from move_base_msgs.msg import MoveBaseGoal, MoveBaseAction
from geometry_msgs.msg import PoseStamped
from meta_controller.msg import MetaMessage
import actionlib
import numpy as np

move_base_client = None

laser_error_handled = False
kin_loc_error_handled = False

def main():
    
    global move_base_client
    rospy.init_node('meta_actuator')
    
    rospy.loginfo("Meta-actuator Node launched")
    
    #Subscribe to meta-messages
    rospy.Subscriber("/meta_events", MetaMessage, meta_event_callback)
        
    #Create a move_base action client
    move_base_client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    
    rospy.loginfo("Meta-actuator ready and waiting for events")    

    rospy.spin()


def meta_event_callback(msg):
    global laser_error_handled
    global kin_loc_error_handled
    
    rospy.loginfo("Meta-actuator: Event received: %s. Handling event...", msg.event)

    interrupt_system()

    if msg.event == "Laser Error":# and not laser_error_handled:
        laser_error_handled = True
        laser_error_handling()
        
    elif msg.event == "Kinect Localization Error":# and not kin_loc_error_handled:
        kin_loc_error_handled = True
        kin_loc_error_handling()
    
    restablish_system(msg.meta_model)

def interrupt_system():
    
    global move_base_client

    while not move_base_client.wait_for_server(rospy.Duration(1.0)) and not rospy.is_shutdown():
        rospy.loginfo("Waiting for the move_base action server to come up")    
    
    if rospy.is_shutdown():
        return
    
    
    rospy.loginfo("Meta-actuator: Interrupting system by canceling all goals")
    move_base_client.cancel_all_goals()
    rospy.loginfo("Meta-actuator: System interrupted") 
    

def laser_error_handling():
    rospy.loginfo("Meta-actuator: Launching System's Reconfiguration by inserting Kinect node")
    
    runCmd("rosnode kill /sicklms &")
    #Launch kinect node to replace laser_scan
    runCmd("roslaunch meta_controller kinect_reconfiguration.launch &")
 #   rospy.loginfo("Kinect Reconfiguration launcher has been launched.")
     
    rospy.sleep(10.0)
    rospy.loginfo("Meta-actuator: System's Reconfiguration has been completed")

def kin_loc_error_handling():
    rospy.loginfo("Meta-actuator: Launching System's Reconfiguration by inserting Laser node into system")
    
    runCmd("rosnode kill /kinect_laser &")
    #Launch kinect node to replace laser_scan
    runCmd("roslaunch meta_controller laser_reconfiguration.launch &")
 #   rospy.loginfo("Kinect Reconfiguration launcher has been launched.")
     
    rospy.sleep(10.0)
    rospy.loginfo("Meta-actuator: System's Reconfiguration for Kinect Localization Error has been completed")



def restablish_system(meta_model):
    global move_base_client
    
    rospy.loginfo("Meta-actuator: Re-establishing system's state...")
    if meta_model != None:
        goal = MoveBaseGoal() 
        goal.target_pose = meta_model
        goal.target_pose.header.stamp = rospy.Time.now()
        move_base_client.send_goal(goal)
    
    rospy.loginfo("Meta-actuator: System's state re-established!")

if __name__ == '__main__':
    main()