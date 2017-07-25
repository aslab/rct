#!/usr/bin/env python

# @author: Carlos Hernandez
# @organization: ASLab
# @summary: node to stamp a covariance (zero) in a pose message
# @status: fuerte version - ToDo - generalize by setting as parameters the topics to subs/pub

import roslib; roslib.load_manifest('mission_manager')
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseWithCovariance

#=====================================================================    


pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped)


def main():
    
    #=====================================================================
    # Initialization and configuration 
    rospy.init_node('cov_stamper_node')      
    rospy.loginfo("cov_stamper_node started")
    
    subs = rospy.Subscriber("/initialpose_nocov", PoseWithCovariance, pose_received_CB() )
      
    # working loop -------------------------------------------------------
    while not rospy.is_shutdown():        
        rospy.sleep(2)
        
    rospy.loginfo("node shutdown")
    
#-------------------------------------------------    
  
def pose_received_CB(msg):
    global  pub
    pub.publish(PoseWithCovarianceStamped(msg.header, PoseWithCovariance(msg.pose, None)))
    rospy.loginfo("position with covariance stamped published")
  
#=====================================================================    

if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass
