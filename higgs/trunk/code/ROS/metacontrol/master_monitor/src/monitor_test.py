#!/usr/bin/env python
import roslib; roslib.load_manifest('master_monitor')
import rospy
import rospy.timer
import time
from std_msgs.msg import String
from syscall import runCmd, runCmdOutput
from move_base_msgs.msg import MoveBaseGoal

def main():
    
    rospy.init_node('master_test')
    
    now = rospy.get_rostime()
    rospy.loginfo("Current time: %d, %d", now.secs, now.nsecs)
    
    print "Starting Master Test"    
    
    rospy.Subscriber("/grammars", String, grammar_callback) 
    
    goal = MoveBaseGoal()
    
    goal.target_pose.header.frame_id = "base_link"
    goal.target_pose.header.stamp = rospy.Time.now()

    goal.target_pose.pose.position.x = 1.0
    goal.target_pose.pose.orientation.w = 1.0
    
    while not rospy.is_shutdown():
        rospy.sleep(0.2)
        check_system()
    




def check_system():
   # print "Rosnode list"
    rosnode_list = runCmdOutput("rosnode list")
    node_to_check="sicklms"
    if rosnode_list.find(node_to_check) == -1:
        rospy.logerr("Problem: "+node_to_check+" not found")
        


def grammar_callback(msg):
    print "Callback: received "+msg.data


if __name__ == '__main__':

    try:
        main()
    except rospy.ROSInterruptException: pass