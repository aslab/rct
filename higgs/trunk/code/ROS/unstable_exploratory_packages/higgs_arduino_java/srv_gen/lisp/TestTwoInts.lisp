; Auto-generated. Do not edit!


(cl:in-package higgs_arduino_java-srv)


;//! \htmlinclude TestTwoInts-request.msg.html

(cl:defclass <TestTwoInts-request> (roslisp-msg-protocol:ros-message)
  ((a
    :reader a
    :initarg :a
    :type cl:integer
    :initform 0)
   (b
    :reader b
    :initarg :b
    :type cl:integer
    :initform 0))
)

(cl:defclass TestTwoInts-request (<TestTwoInts-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TestTwoInts-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TestTwoInts-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name higgs_arduino_java-srv:<TestTwoInts-request> is deprecated: use higgs_arduino_java-srv:TestTwoInts-request instead.")))

(cl:ensure-generic-function 'a-val :lambda-list '(m))
(cl:defmethod a-val ((m <TestTwoInts-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-srv:a-val is deprecated.  Use higgs_arduino_java-srv:a instead.")
  (a m))

(cl:ensure-generic-function 'b-val :lambda-list '(m))
(cl:defmethod b-val ((m <TestTwoInts-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-srv:b-val is deprecated.  Use higgs_arduino_java-srv:b instead.")
  (b m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TestTwoInts-request>) ostream)
  "Serializes a message object of type '<TestTwoInts-request>"
  (cl:let* ((signed (cl:slot-value msg 'a)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'b)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TestTwoInts-request>) istream)
  "Deserializes a message object of type '<TestTwoInts-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'a) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'b) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TestTwoInts-request>)))
  "Returns string type for a service object of type '<TestTwoInts-request>"
  "higgs_arduino_java/TestTwoIntsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestTwoInts-request)))
  "Returns string type for a service object of type 'TestTwoInts-request"
  "higgs_arduino_java/TestTwoIntsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TestTwoInts-request>)))
  "Returns md5sum for a message object of type '<TestTwoInts-request>"
  "f0b6d69ea10b0cf210cb349d58d59e8f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TestTwoInts-request)))
  "Returns md5sum for a message object of type 'TestTwoInts-request"
  "f0b6d69ea10b0cf210cb349d58d59e8f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TestTwoInts-request>)))
  "Returns full string definition for message of type '<TestTwoInts-request>"
  (cl:format cl:nil "int32 a~%int32 b~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TestTwoInts-request)))
  "Returns full string definition for message of type 'TestTwoInts-request"
  (cl:format cl:nil "int32 a~%int32 b~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TestTwoInts-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TestTwoInts-request>))
  "Converts a ROS message object to a list"
  (cl:list 'TestTwoInts-request
    (cl:cons ':a (a msg))
    (cl:cons ':b (b msg))
))
;//! \htmlinclude TestTwoInts-response.msg.html

(cl:defclass <TestTwoInts-response> (roslisp-msg-protocol:ros-message)
  ((sum
    :reader sum
    :initarg :sum
    :type cl:integer
    :initform 0))
)

(cl:defclass TestTwoInts-response (<TestTwoInts-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TestTwoInts-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TestTwoInts-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name higgs_arduino_java-srv:<TestTwoInts-response> is deprecated: use higgs_arduino_java-srv:TestTwoInts-response instead.")))

(cl:ensure-generic-function 'sum-val :lambda-list '(m))
(cl:defmethod sum-val ((m <TestTwoInts-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-srv:sum-val is deprecated.  Use higgs_arduino_java-srv:sum instead.")
  (sum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TestTwoInts-response>) ostream)
  "Serializes a message object of type '<TestTwoInts-response>"
  (cl:let* ((signed (cl:slot-value msg 'sum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TestTwoInts-response>) istream)
  "Deserializes a message object of type '<TestTwoInts-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sum) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TestTwoInts-response>)))
  "Returns string type for a service object of type '<TestTwoInts-response>"
  "higgs_arduino_java/TestTwoIntsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestTwoInts-response)))
  "Returns string type for a service object of type 'TestTwoInts-response"
  "higgs_arduino_java/TestTwoIntsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TestTwoInts-response>)))
  "Returns md5sum for a message object of type '<TestTwoInts-response>"
  "f0b6d69ea10b0cf210cb349d58d59e8f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TestTwoInts-response)))
  "Returns md5sum for a message object of type 'TestTwoInts-response"
  "f0b6d69ea10b0cf210cb349d58d59e8f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TestTwoInts-response>)))
  "Returns full string definition for message of type '<TestTwoInts-response>"
  (cl:format cl:nil "int32 sum~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TestTwoInts-response)))
  "Returns full string definition for message of type 'TestTwoInts-response"
  (cl:format cl:nil "int32 sum~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TestTwoInts-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TestTwoInts-response>))
  "Converts a ROS message object to a list"
  (cl:list 'TestTwoInts-response
    (cl:cons ':sum (sum msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'TestTwoInts)))
  'TestTwoInts-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'TestTwoInts)))
  'TestTwoInts-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestTwoInts)))
  "Returns string type for a service object of type '<TestTwoInts>"
  "higgs_arduino_java/TestTwoInts")
