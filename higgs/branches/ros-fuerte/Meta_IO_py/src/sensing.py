'''
Created on Sep 24, 2012

@author: Carlos Hernandez
@organization: ASLab

@summary: class for monitoring info about nodes with ROS tools and publishing it in a ROS topic
@status: v1 - basic functionality working
@note: developed from from OMRosDrivers_py/src/sensing.py

'''

import roslib; roslib.load_manifest('Meta_IO_py')
import rospy
import rosnode
import rosparam
import roslib.scriptutil as scriptutil

from rosgraph_msgs.msg import Log

# for the sensing perception ------------------------------
from meta_msgs.msg import NodesInfoList
from meta_msgs.msg import NodeInfo
from meta_msgs.msg import ROSTopic
from meta_msgs.msg import ROSParameter, OMTypes
#----------------------------------------------------------

import socket, struct

#####################################################################

known_types = [int, float, str]

OMTYPES = OMTypes()

class OMRosSensor():
    
    
    ID = '/rosnode'
    
    nodes = []
    logBuffer = []

    def __init__(self):   
        # subscribers to sensing topics
        self.subs_rosout = rospy.Subscriber("/rosout", Log, self.error_sensing_CB)
        self.subs_rosoutagg = rospy.Subscriber("/rosout_agg", Log, self.error_sensing_CB)
              
        # publisher for nodes
        self.pub_nodes = rospy.Publisher('/nodes_list', NodesInfoList, latch=True)


    #####################################################################   
    def sense(self):
    # @summary: basic cycle of the OMRosSensor
        
        # get the list of nodes     
        registered_nodes = rosnode.get_node_names()

        # create the list of NodeInfo objects
        self.nodes = [self.get_node_info(node_name=x) for x in registered_nodes]
    
        nodelist = NodesInfoList(None, self.nodes)
	nodelist.header.stamp = rospy.Time.now()
        #print self.nodes
        #print "\n ------------------- \n"
        # publish nodes
        self.pub_nodes.publish(nodelist)
        self.logBuffer = []
        
    
        # print '---- cycle ---------------------------------------------------\n \n'


    #####################################################################
    
    def get_node_info(self, node_name):
        def topic_type(t, pub_topics):
        #@summary: auxiliary function to obtain the type of a topic
            matches = [t_type for t_name, t_type in pub_topics if t_name == t]
            if matches:
                return matches[0]
            return 'unknown'
        
        master = scriptutil.get_master() # obtain the ros master
            
        # @todo: would be interesting to rosnode_ping if the node is not accessible from master send node in error
        # but the method hangs, don't know why
        
        # go through the master system state first
        try:
            pub_topics = master.getPublishedTopics(self.ID, '/')
            pub_topics = pub_topics[2]
            state = master.getSystemState(self.ID)
            state = state[2]
            
        except socket.error:
            raise ROSNodeIOException("Unable to communicate with master!")
        
        # gather info about the node parameters
        # use: rosparam.list_params(ns) and rosparam.get_param(param), ns= name space of the node
        param_names = rosparam.list_params(node_name)
        params = []
        for p in param_names:
            parameter = ROSParameter()
            parameter.name = p.replace(node_name+'/', "")
            v = rosparam.get_param(p)
            if type(v) in known_types :
                if type(v) is int :
                    parameter.type = OMTYPES.INTEGER
                elif type(v) is str :
                    parameter.type = OMTYPES.STRING
                elif type(v) is float :
                    parameter.type = OMTYPES.DOUBLE
                parameter.value = struct.pack(parameter.type, v)
            else :
                parameter.value = []
            params.append(parameter)
            
        # srvs = [t for t, l in state[2] if node_name in l] #eventually for services   
        
        # lists of pub and subs topics names
        pubs = [t for t, l in state[0] if node_name in l]
        subs = [t for t, l in state[1] if node_name in l]        
        # create double list with topic names and types
        published = None
        subscribed = None
        if len(pubs) <> 0 :
            published = [ROSTopic(p, topic_type(p, pub_topics)) for p in pubs]
        if len(subs) <> 0 :   
            subscribed = [ROSTopic(p, topic_type(p, pub_topics)) for p in subs]
            
        # add log information 
        # @todo: maybe also filter with errors from refs2ignore
        errors = []    
        for l in self.logBuffer:
            if l.name == node_name:
                level = ''
                if l.level == 8:
                    level = ' ERROR'
                entry = l.msg + level
                errors.append( entry )
        
        return NodeInfo(node_name, 1, subscribed, published, params, errors)

    
    #####################################################################
    # CallBacks
    #####################################################################
    def error_sensing_CB(self, data):
        self.logBuffer.append(data)
        
                
        
