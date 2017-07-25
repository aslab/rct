#!/usr/bin/env python

'''
Created on Nov 10, 2011

@author: chcorbato
@summary: ros node that publishes MetaAction messages from console input
          for testing purposes
'''

import roslib; roslib.load_manifest('Meta_IO_py')
import rospy

import sys, struct
import getopt

# for the sensing messages -----------------------------------
from meta_msgs.msg import NodesList, NodeInfo, ROSTopic, ROSParameter, OMTypes 
#----------------------------------------------------------

OMTYPES = OMTypes()
known_types = [OMTYPES.INTEGER, OMTYPES.DOUBLE, OMTYPES.STRING]

readings = []

#####################################################################
def sensing_CB(msg):
    global readings
    readings = msg.nodes
        
#####################################################################
def main():
    rospy.init_node('node_list_reader')   
    
    sensor_sub = rospy.Subscriber('/node_list', NodesList, sensing_CB)

    print "enter:\n s to get latest sensing \n q to quit"
         
    #------------------------------------------------------        
    # working loop --------------------------------------------------------------------
    while not rospy.is_shutdown():
        a = ''
        a = raw_input()
        if a == 's':
            print "sensing received: -----------------------"
            for x in readings:
                print "-----------"
                print "Node:  " + x.node_name
                print 'status: ' + str(x.status)
                print 'parameters:'
                for p in x.params:
                    if p.type not in known_types:
                        print '\t' + p.name + '\t UNSUPPORTED TYPE'
                    else:
                        value = struct.unpack(p.type, p.value)
                        print '\t' + p.name + '\t' + repr(value[0])
                print 'connectors:'
                for t in x.subs:
                    print '\t' + t.name + ' (IN)'
                for t in x.pubs:
                    print '\t' + t.name + ' (OUT)'
                print 'log:'
                for s in x.errors :
                    print '\t' + s   
            print "-----------------------------------------"
            print "\n"+"enter:\n s to get latest sensing \n q to quit"

        if a == 'q':
            rospy.loginfo("...node_list_reader ended")
            return
        
    # termination -----------------------------------------------------------------
    rospy.loginfo("...node_list_reader ended")       
    

if __name__ == '__main__':
	try:
	    main()
	except rospy.ROSInterruptException: pass
