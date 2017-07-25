#!/usr/bin/env python

# @author: Carlos Hernandez
# @organization: ASLab
# @summary: node to simulate kinects scan from stageros base_scan topic
# @status: electric version - still not working

import roslib; roslib.load_manifest('higgs_stage_sim')
import rospy
from sensor_msgs.msg import LaserScan

import math

pub = 0

correct_baudrate = 5600

def main():
    global pub
    #=====================================================================
    # Initialization and configuration 
    rospy.init_node('fake_laser_scan_node')      
    rospy.loginfo("fake_laser_scan_node started")
    
    #Subscribe to rviz /goal topic so as to handle it in this action client
    rospy.Subscriber("/base_scan", LaserScan, stage_scan_cb)
    pub = rospy.Publisher('/scan', LaserScan)
          
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
   
    

if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass