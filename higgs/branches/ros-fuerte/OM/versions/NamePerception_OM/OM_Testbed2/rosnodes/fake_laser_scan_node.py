#!/usr/bin/env python

# @author: Carlos Hernandez
# @organization: ASLab
# @summary: node to simulate kinects scan from stageros base_scan topic
# @status: electric version - still not working

import roslib; roslib.load_manifest('OM_Testbed2')
import rospy
from sensor_msgs.msg import LaserScan

import math

pub = 0

correct_baudrate = 5600

def main():
    global pub
    
    #=====================================================================
    # Ros Node initialization and configuration 
    rospy.init_node('fake_laser_scan_node')      
    rospy.loginfo("fake_laser_scan_node started")
    
    #Subscribe to rviz /goal topic so as to handle it in this action client
    rospy.Subscriber("/base_scan", LaserScan, stage_scan_cb)
    pub = rospy.Publisher('/scan', LaserScan)
    
    # open port
    result_ok = open_port( rospy.get_param('~port') )
    if not result_ok :
        rospy.logerr('Initialize failed! are you using the correct device path?')
        rospy.signal_shutdown('wrong device path')
        raise rospy.ROSInterruptException()
    
    if rospy.get_param('~baudrate') != correct_baudrate :
        rospy.logerr("Not working")
        raise rospy.ROSInterruptException()
          
    # working loop -------------------------------------------------------
    while not rospy.is_shutdown():
        if rospy.get_param('~baudrate') != correct_baudrate :
            rospy.logerr("Not working")
            
        rospy.sleep(2)
        
    rospy.loginfo("node shutdown")
    
  
#=====================================================================
    
def stage_scan_cb(msg):
    # @todo: add noise to the ranges 
    if rospy.get_param('~baudrate') == correct_baudrate :
        pub.publish(msg)
        
#======================================================================

# function to open the port given by the "port" string input parameter   
# return True if the port could be open, False otherwise
def open_port(port):
    try:
        f = open(port,'r')
    except IOError:
        return False
    
    return True

#======================================================================


if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException: pass
    