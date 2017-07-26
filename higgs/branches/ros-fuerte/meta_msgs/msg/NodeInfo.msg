# This message holds info of a ROS node
# replaces RosSingularity.msg
# 

# Possible levels of operations
#byte OK=1
#byte ERROR=0

string node_name # the name of the node
byte status # status of the ros node regarding master connectivity
ROSTopic[] subs
ROSTopic[] pubs
ROSParameter[] params # the parameters of the node
string[] errors # latest history of relevant messages sent to rosout from the node