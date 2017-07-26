#!/usr/bin/env python

# @author: Carlos Hernandez
# @organization: ASLab
# @summary: node to provide initial position to navigation/:amcl node
# @status: electric version - still not working: initial position should be published once!!!

import roslib; roslib.load_manifest('OM_Testbed2')
import rospy
from std_msgs.msg import Header, Bool
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseWithCovariance, Pose, Point, Quaternion

#=====================================================================    


position = Point(1.042, -0.979, 0)
orientation = Quaternion( 0, 0, -0.00126122865203, 0.999999204651)
pose = Pose(position, orientation)
posecov = PoseWithCovariance(pose, None)
header = Header()
header.frame_id = "/map"
initial_pose = PoseWithCovarianceStamped(header, posecov)

pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped)


def main():
    
    #=====================================================================
    # Initialization and configuration 
    rospy.init_node('initial_pose_node')      
    rospy.loginfo("initial_pose_node started")
    
    subs = rospy.Subscriber("/localization_request", Bool, localization_request_CB)
      
    # working loop -------------------------------------------------------
    while not rospy.is_shutdown():        
        rospy.sleep(2)
        
    rospy.loginfo("node shutdown")
    
#-------------------------------------------------    
  
def localization_request_CB(msg):  # @todo: this should be offered as a service
    global initial_pose, pub
    if msg.data == True:
        print 'true'
        pub.publish(initial_pose)
        rospy.loginfo("position provided")
  
#=====================================================================    

if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass