; Auto-generated. Do not edit!


(cl:in-package higgs_arduino_java-msg)


;//! \htmlinclude TestBadDataTypes.msg.html

(cl:defclass <TestBadDataTypes> (roslisp-msg-protocol:ros-message)
  ((Byte_f
    :reader Byte_f
    :initarg :Byte_f
    :type (cl:vector std_msgs-msg:Byte)
   :initform (cl:make-array 2 :element-type 'std_msgs-msg:Byte :initial-element (cl:make-instance 'std_msgs-msg:Byte)))
   (ByteMultiArray_f
    :reader ByteMultiArray_f
    :initarg :ByteMultiArray_f
    :type (cl:vector std_msgs-msg:ByteMultiArray)
   :initform (cl:make-array 1 :element-type 'std_msgs-msg:ByteMultiArray :initial-element (cl:make-instance 'std_msgs-msg:ByteMultiArray))))
)

(cl:defclass TestBadDataTypes (<TestBadDataTypes>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TestBadDataTypes>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TestBadDataTypes)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name higgs_arduino_java-msg:<TestBadDataTypes> is deprecated: use higgs_arduino_java-msg:TestBadDataTypes instead.")))

(cl:ensure-generic-function 'Byte_f-val :lambda-list '(m))
(cl:defmethod Byte_f-val ((m <TestBadDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:Byte_f-val is deprecated.  Use higgs_arduino_java-msg:Byte_f instead.")
  (Byte_f m))

(cl:ensure-generic-function 'ByteMultiArray_f-val :lambda-list '(m))
(cl:defmethod ByteMultiArray_f-val ((m <TestBadDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:ByteMultiArray_f-val is deprecated.  Use higgs_arduino_java-msg:ByteMultiArray_f instead.")
  (ByteMultiArray_f m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TestBadDataTypes>) ostream)
  "Serializes a message object of type '<TestBadDataTypes>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Byte_f))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'ByteMultiArray_f))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TestBadDataTypes>) istream)
  "Deserializes a message object of type '<TestBadDataTypes>"
  (cl:setf (cl:slot-value msg 'Byte_f) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'Byte_f)))
    (cl:dotimes (i 2)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Byte))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  (cl:setf (cl:slot-value msg 'ByteMultiArray_f) (cl:make-array 1))
  (cl:let ((vals (cl:slot-value msg 'ByteMultiArray_f)))
    (cl:dotimes (i 1)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:ByteMultiArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TestBadDataTypes>)))
  "Returns string type for a message object of type '<TestBadDataTypes>"
  "higgs_arduino_java/TestBadDataTypes")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestBadDataTypes)))
  "Returns string type for a message object of type 'TestBadDataTypes"
  "higgs_arduino_java/TestBadDataTypes")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TestBadDataTypes>)))
  "Returns md5sum for a message object of type '<TestBadDataTypes>"
  "f0fea41d38f14ed745582d619f53bcd0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TestBadDataTypes)))
  "Returns md5sum for a message object of type 'TestBadDataTypes"
  "f0fea41d38f14ed745582d619f53bcd0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TestBadDataTypes>)))
  "Returns full string definition for message of type '<TestBadDataTypes>"
  (cl:format cl:nil "# Unfortunately, can't test these fully because roscpp message generation~%# is broken. ~%~%std_msgs/Byte[2] Byte_f~%std_msgs/ByteMultiArray[1] ByteMultiArray_f~%~%================================================================================~%MSG: std_msgs/Byte~%byte data~%~%================================================================================~%MSG: std_msgs/ByteMultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%byte[]            data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding bytes at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TestBadDataTypes)))
  "Returns full string definition for message of type 'TestBadDataTypes"
  (cl:format cl:nil "# Unfortunately, can't test these fully because roscpp message generation~%# is broken. ~%~%std_msgs/Byte[2] Byte_f~%std_msgs/ByteMultiArray[1] ByteMultiArray_f~%~%================================================================================~%MSG: std_msgs/Byte~%byte data~%~%================================================================================~%MSG: std_msgs/ByteMultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%byte[]            data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding bytes at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TestBadDataTypes>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Byte_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'ByteMultiArray_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TestBadDataTypes>))
  "Converts a ROS message object to a list"
  (cl:list 'TestBadDataTypes
    (cl:cons ':Byte_f (Byte_f msg))
    (cl:cons ':ByteMultiArray_f (ByteMultiArray_f msg))
))
