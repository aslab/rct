#!/usr/bin/env python

# @author: Carlos Hernandez
# @organization: ASLab
# @summary: node to write the waypoints of a patrolling mission into a file
# @status: initial version

import roslib; roslib.load_manifest('create_patrol_mission')
import rospy
from geometry_msgs.msg import PoseStamped

import sys
import getopt
import numpy

filename = 'mission'
mission_path = []

def main(argv):
    global filename, mission_path
    
    # parsing of main arg ------------------------------
    try:
        opts, args = getopt.getopt(argv, "hf:", ['help', "file="])
    
    except getopt.GetoptError:
        # put here usage instructions
        sys.exit(2)
        
        
    for opt, arg in opts:                
        if opt in ("-h", "--help"):      
            # put here usage instructions
            print "you can specify the filename to save the mission waypoints with -f filename. If none is given, mission is the name of the output file"                   
            sys.exit()
        elif opt == '-f':
            filename = arg
    #------------------------------------------------------        
    
    rospy.init_node('mission_creator_node')
    
    rospy.loginfo("Mission creator node started")
    print "Enter 'q' to end creating the mission. It will be saved as a text file with the coordinates of the waypoints"
    #Subscribe to the goal topic of rviz
    rospy.Subscriber("/goal", PoseStamped, new_goal_callback)
    
    # working loop
    while not rospy.is_shutdown():
        rospy.sleep(2)
        if raw_input() == 'q':     
            x = [[1, 2], [0, 1]]     
            numpy.savetxt(filename, mission_path)
            print "mission saved in: " + filename
            rospy.loginfo("Mission creator node finished")
            return


def new_goal_callback(msg):
    global mission_path
    # add new goal waypoint to mission_path array
    waypoint = [msg.pose.position.x, msg.pose.position.y, msg.pose.position.z, msg.pose.orientation.w, msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z]
    mission_path.append(waypoint)
    print 'waypoint added'

if __name__ == '__main__':
    main(sys.argv[1:]) # first argv is the name of the script, so we chop it off
