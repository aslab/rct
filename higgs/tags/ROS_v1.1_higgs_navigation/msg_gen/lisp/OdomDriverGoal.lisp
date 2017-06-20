; Auto-generated. Do not edit!


(cl:in-package higgs_navigation-msg)


;//! \htmlinclude OdomDriverGoal.msg.html

(cl:defclass <OdomDriverGoal> (roslisp-msg-protocol:ros-message)
  ((target_pose
    :reader target_pose
    :initarg :target_pose
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped)))
)

(cl:defclass OdomDriverGoal (<OdomDriverGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OdomDriverGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OdomDriverGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name higgs_navigation-msg:<OdomDriverGoal> is deprecated: use higgs_navigation-msg:OdomDriverGoal instead.")))

(cl:ensure-generic-function 'target_pose-val :lambda-list '(m))
(cl:defmethod target_pose-val ((m <OdomDriverGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_navigation-msg:target_pose-val is deprecated.  Use higgs_navigation-msg:target_pose instead.")
  (target_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OdomDriverGoal>) ostream)
  "Serializes a message object of type '<OdomDriverGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OdomDriverGoal>) istream)
  "Deserializes a message object of type '<OdomDriverGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OdomDriverGoal>)))
  "Returns string type for a message object of type '<OdomDriverGoal>"
  "higgs_navigation/OdomDriverGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OdomDriverGoal)))
  "Returns string type for a message object of type 'OdomDriverGoal"
  "higgs_navigation/OdomDriverGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OdomDriverGoal>)))
  "Returns md5sum for a message object of type '<OdomDriverGoal>"
  "257d089627d7eb7136c24d3593d05a16")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OdomDriverGoal)))
  "Returns md5sum for a message object of type 'OdomDriverGoal"
  "257d089627d7eb7136c24d3593d05a16")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OdomDriverGoal>)))
  "Returns full string definition for message of type '<OdomDriverGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%geometry_msgs/PoseStamped target_pose # goal~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OdomDriverGoal)))
  "Returns full string definition for message of type 'OdomDriverGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%geometry_msgs/PoseStamped target_pose # goal~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OdomDriverGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OdomDriverGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'OdomDriverGoal
    (cl:cons ':target_pose (target_pose msg))
))
