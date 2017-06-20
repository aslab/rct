#!/usr/bin/env python

import roslib; roslib.load_manifest('meta_controller')
import rospy
from rosgraph_msgs.msg import Log
from syscall import runCmd, runCmdOutput
from geometry_msgs.msg import PoseStamped
from meta_controller.msg import MetaMessage
from geometry_msgs.msg import PoseWithCovarianceStamped
import numpy as np

class MetaModel:
    current_goal = None

level = ["DEBUG", "INFO", "WARN", "ERROR", "FATAL"]

laser_error_advertised = False
kin_loc_error_advertised = False
first_localization_set = False

meta_model = MetaModel()

meta_msg_pub = None 


MISSION_2 = True
LASER_TIME = 20
state_laser = False
config_time = None

goal_received = 0

def main():
    rospy.init_node('meta_monitor')
    
    global meta_model
    global meta_msg_pub
    global MISSION_2
    
    current_goal_sub = rospy.Subscriber("/move_base_node/current_goal", PoseStamped, current_goal_callback) 
    

    
    
    rospy.loginfo("Meta-monitor Node Launched")
    
    rospy.loginfo("Meta-monitor: Waiting for initial localization")
    wait_for_initial_localization()
    
    
    rospy.Subscriber("/rosout", Log, rosout_callback)
    rospy.Subscriber("/rosout_agg", Log, rosout_callback)
    meta_msg_pub = rospy.Publisher('/meta_events', MetaMessage)
    
    rospy.loginfo("Meta-monitor: Robot has first localization. Ready to monitor system")
    
    
    
    
    rospy.loginfo("Meta-monitor is monitoring system")
    
    global state_laser
    
    while not rospy.is_shutdown():
        rospy.sleep(0.2)
        if not MISSION_2:
            check_system()
#        elif state_laser:
#            check_state()
            

def check_state():
    global config_time
    
    now = rospy.Time.now()
    d = now -config_time
    
    print "Time from laser reconfiguration: "+str(d.to_sec())
    if d.to_sec() > LASER_TIME:
        advertise_laser_error_event()
        
        
def rosout_callback(data): 
    
    
    if str(data.msg).strip() == str("Connectivity Error: Could not find a common time /base_link and /map.") and data.name == "/move_base_node" and not MISSION_2:
        advertise_laser_error_event()
        
    if data.name == "/sicklms" and str(data.msg).strip() == "woah! error!":
        advertise_laser_error_event()
        
    message = data.msg.split(" ")
    
    
    global state_laser
    
    if not state_laser:
        if message[0].strip()== "Costmap2DROS" and MISSION_2:
            advertise_kin_loc_error_event()
            
        if message[0].strip()== "Aborting" and MISSION_2:
            advertise_kin_loc_error_event()
        
def check_system():
    global laser_error_advertised
    
    if laser_error_advertised:
        return
    # print "Rosnode list"
    rosnode_list = runCmdOutput("rosnode list")
    node_to_check="sicklms"
    if rosnode_list.find(node_to_check) == -1 and not laser_error_advertised:
        rospy.logwarn("Problem detected: "+node_to_check+" node not found. Publishing event")
        advertise_laser_error_event()

def current_goal_callback(data):
    global meta_model
    meta_model.current_goal = data
    rospy.loginfo("Current goal received and stored in Meta-model")
    
    
    global goal_received
    
    if MISSION_2 and state_laser:
        goal_received=goal_received+1
        
        if goal_received > 1:
            advertise_laser_error_event()

def amcl_pose_callback(msg):
    global first_localization_set
    first_localization_set = True
    
def wait_for_initial_localization():
    global first_localization_set
    rospy.Subscriber("/amcl_pose", PoseWithCovarianceStamped, amcl_pose_callback)

    while not first_localization_set and not rospy.is_shutdown():
        rospy.sleep(0.2)

def advertise_laser_error_event():
    global laser_error_advertised
    
    if laser_error_advertised:
        return
    
    global meta_model
    global meta_msg_pub    
    #Creating meta_message
    meta_message = MetaMessage("Laser Error", meta_model.current_goal)

    rospy.loginfo("Meta-monitor: Laser Error event detected and advertised")
    #Publishing meta_message
    meta_msg_pub.publish(meta_message)
    
    laser_error_advertised = True
    
    #Added for Mission 2
    
    if MISSION_2:
        global state_laser
        global kin_loc_error_advertised
        state_laser = False
         
        rospy.sleep(10.0)
        kin_loc_error_advertised = False

    
    
def advertise_kin_loc_error_event():
    global kin_loc_error_advertised
    

    
    if kin_loc_error_advertised:
        return
    
    
    kin_loc_error_advertised = True
    
    
    global meta_model
    global meta_msg_pub    
    #Creating meta_message
    meta_message = MetaMessage("Kinect Localization Error", meta_model.current_goal)

    rospy.loginfo("Meta-monitor: Kinect Localization Error event detected and advertised")
    #Publishing meta_message
    meta_msg_pub.publish(meta_message)
    
    kin_loc_error_advertised = True
    
    #Added for Mission 2
    if MISSION_2:
    
        global goal_received
        goal_received = 0
        global state_laser
        global laser_error_advertised
        global config_time
        
        
        rospy.sleep(10.0)
        laser_error_advertised = False
        state_laser = True
        config_time = rospy.Time.now()
    
if __name__ == '__main__':
    main()