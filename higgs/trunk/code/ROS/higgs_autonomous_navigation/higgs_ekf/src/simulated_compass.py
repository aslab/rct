#!/usr/bin/env python

import roslib; roslib.load_manifest('simulated_compass')
import rospy
from geometry_msgs.msg import Quaternion
from nav_msgs.msg import Odometry
from sensor_msgs.msg import Imu

first = 1

def callback(odom):
    pub = rospy.Publisher('compass_fake', sensor_msgs.msg.Imu)

    if first:
        first = 0
        ref = odom.pose.orientation
        
        
    
    imu_data = Imu
    imu_data.orientation
    pub.publish()
    

def main():
    rospy.init_node('simulated_compass')
    
    rospy.Subscriber("/base_pose_ground_truth", nav_msgs.msg.Odometry, callback)
    rospy.spin()

if __name__ == '__main__':
    main()