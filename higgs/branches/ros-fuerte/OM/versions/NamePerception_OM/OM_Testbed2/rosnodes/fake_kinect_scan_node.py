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
kscan = LaserScan()
kscan.angle_min = -math.pi/6
kscan.angle_max =  math.pi/6
kscan.range_max = 8.0
kscan.range_max = 0.6

def main():
    global pub
    #=====================================================================
    # Initialization and configuration 
    rospy.init_node('fake_kinect_scan_node')      
    rospy.loginfo("fake_kinect_scan_node started")
    
    #Subscribe to rviz /goal topic so as to handle it in this action client
    rospy.Subscriber("/base_scan", LaserScan, stage_scan_cb)
    pub = rospy.Publisher('/scan', LaserScan)
      
    # working loop -------------------------------------------------------
    while not rospy.is_shutdown():
        rospy.sleep(2)
        
    rospy.loginfo("node shutdown")
    
  
#=====================================================================
    
def stage_scan_cb(msg):
    global pub, kscan
    kscan.header = msg.header
    kscan.angle_increment = msg.angle_increment
    print len(msg.ranges)
    kscan.ranges = msg.ranges[121:242] # stageros sends 361 ranges
    # @todo: add noise to the ranges, and publish kscan instead of msg
    pub.publish(msg)
    
    

if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass