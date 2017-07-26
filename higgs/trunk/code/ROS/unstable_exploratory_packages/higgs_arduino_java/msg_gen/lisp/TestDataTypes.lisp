; Auto-generated. Do not edit!


(cl:in-package higgs_arduino_java-msg)


;//! \htmlinclude TestDataTypes.msg.html

(cl:defclass <TestDataTypes> (roslisp-msg-protocol:ros-message)
  ((byte_
    :reader byte_
    :initarg :byte_
    :type cl:integer
    :initform 0)
   (char_
    :reader char_
    :initarg :char_
    :type cl:integer
    :initform 0)
   (uint8_
    :reader uint8_
    :initarg :uint8_
    :type cl:fixnum
    :initform 0)
   (int8_
    :reader int8_
    :initarg :int8_
    :type cl:fixnum
    :initform 0)
   (uint16_
    :reader uint16_
    :initarg :uint16_
    :type cl:fixnum
    :initform 0)
   (int16_
    :reader int16_
    :initarg :int16_
    :type cl:fixnum
    :initform 0)
   (uint32_
    :reader uint32_
    :initarg :uint32_
    :type cl:integer
    :initform 0)
   (int32_
    :reader int32_
    :initarg :int32_
    :type cl:integer
    :initform 0)
   (uint64_
    :reader uint64_
    :initarg :uint64_
    :type cl:integer
    :initform 0)
   (int64_
    :reader int64_
    :initarg :int64_
    :type cl:integer
    :initform 0)
   (float32_
    :reader float32_
    :initarg :float32_
    :type cl:float
    :initform 0.0)
   (float64_
    :reader float64_
    :initarg :float64_
    :type cl:float
    :initform 0.0)
   (string_
    :reader string_
    :initarg :string_
    :type cl:string
    :initform "")
   (time_
    :reader time_
    :initarg :time_
    :type cl:real
    :initform 0)
   (duration_
    :reader duration_
    :initarg :duration_
    :type cl:real
    :initform 0)
   (byte_v
    :reader byte_v
    :initarg :byte_v
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (byte_f
    :reader byte_f
    :initarg :byte_f
    :type (cl:vector cl:integer)
   :initform (cl:make-array 2 :element-type 'cl:integer :initial-element 0))
   (float64_v
    :reader float64_v
    :initarg :float64_v
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (float64_f
    :reader float64_f
    :initarg :float64_f
    :type (cl:vector cl:float)
   :initform (cl:make-array 2 :element-type 'cl:float :initial-element 0.0))
   (string_v
    :reader string_v
    :initarg :string_v
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (string_f
    :reader string_f
    :initarg :string_f
    :type (cl:vector cl:string)
   :initform (cl:make-array 2 :element-type 'cl:string :initial-element ""))
   (time_v
    :reader time_v
    :initarg :time_v
    :type (cl:vector cl:real)
   :initform (cl:make-array 0 :element-type 'cl:real :initial-element 0))
   (time_f
    :reader time_f
    :initarg :time_f
    :type (cl:vector cl:real)
   :initform (cl:make-array 2 :element-type 'cl:real :initial-element 0))
   (Byte_
    :reader Byte_
    :initarg :Byte_
    :type std_msgs-msg:Byte
    :initform (cl:make-instance 'std_msgs-msg:Byte))
   (Byte_v
    :reader Byte_v
    :initarg :Byte_v
    :type (cl:vector std_msgs-msg:Byte)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:Byte :initial-element (cl:make-instance 'std_msgs-msg:Byte)))
   (ByteMultiArray_
    :reader ByteMultiArray_
    :initarg :ByteMultiArray_
    :type std_msgs-msg:ByteMultiArray
    :initform (cl:make-instance 'std_msgs-msg:ByteMultiArray))
   (ByteMultiArray_v
    :reader ByteMultiArray_v
    :initarg :ByteMultiArray_v
    :type (cl:vector std_msgs-msg:ByteMultiArray)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:ByteMultiArray :initial-element (cl:make-instance 'std_msgs-msg:ByteMultiArray))))
)

(cl:defclass TestDataTypes (<TestDataTypes>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TestDataTypes>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TestDataTypes)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name higgs_arduino_java-msg:<TestDataTypes> is deprecated: use higgs_arduino_java-msg:TestDataTypes instead.")))

(cl:ensure-generic-function 'byte_-val :lambda-list '(m))
(cl:defmethod byte_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:byte_-val is deprecated.  Use higgs_arduino_java-msg:byte_ instead.")
  (byte_ m))

(cl:ensure-generic-function 'char_-val :lambda-list '(m))
(cl:defmethod char_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:char_-val is deprecated.  Use higgs_arduino_java-msg:char_ instead.")
  (char_ m))

(cl:ensure-generic-function 'uint8_-val :lambda-list '(m))
(cl:defmethod uint8_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:uint8_-val is deprecated.  Use higgs_arduino_java-msg:uint8_ instead.")
  (uint8_ m))

(cl:ensure-generic-function 'int8_-val :lambda-list '(m))
(cl:defmethod int8_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:int8_-val is deprecated.  Use higgs_arduino_java-msg:int8_ instead.")
  (int8_ m))

(cl:ensure-generic-function 'uint16_-val :lambda-list '(m))
(cl:defmethod uint16_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:uint16_-val is deprecated.  Use higgs_arduino_java-msg:uint16_ instead.")
  (uint16_ m))

(cl:ensure-generic-function 'int16_-val :lambda-list '(m))
(cl:defmethod int16_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:int16_-val is deprecated.  Use higgs_arduino_java-msg:int16_ instead.")
  (int16_ m))

(cl:ensure-generic-function 'uint32_-val :lambda-list '(m))
(cl:defmethod uint32_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:uint32_-val is deprecated.  Use higgs_arduino_java-msg:uint32_ instead.")
  (uint32_ m))

(cl:ensure-generic-function 'int32_-val :lambda-list '(m))
(cl:defmethod int32_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:int32_-val is deprecated.  Use higgs_arduino_java-msg:int32_ instead.")
  (int32_ m))

(cl:ensure-generic-function 'uint64_-val :lambda-list '(m))
(cl:defmethod uint64_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:uint64_-val is deprecated.  Use higgs_arduino_java-msg:uint64_ instead.")
  (uint64_ m))

(cl:ensure-generic-function 'int64_-val :lambda-list '(m))
(cl:defmethod int64_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:int64_-val is deprecated.  Use higgs_arduino_java-msg:int64_ instead.")
  (int64_ m))

(cl:ensure-generic-function 'float32_-val :lambda-list '(m))
(cl:defmethod float32_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:float32_-val is deprecated.  Use higgs_arduino_java-msg:float32_ instead.")
  (float32_ m))

(cl:ensure-generic-function 'float64_-val :lambda-list '(m))
(cl:defmethod float64_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:float64_-val is deprecated.  Use higgs_arduino_java-msg:float64_ instead.")
  (float64_ m))

(cl:ensure-generic-function 'string_-val :lambda-list '(m))
(cl:defmethod string_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:string_-val is deprecated.  Use higgs_arduino_java-msg:string_ instead.")
  (string_ m))

(cl:ensure-generic-function 'time_-val :lambda-list '(m))
(cl:defmethod time_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:time_-val is deprecated.  Use higgs_arduino_java-msg:time_ instead.")
  (time_ m))

(cl:ensure-generic-function 'duration_-val :lambda-list '(m))
(cl:defmethod duration_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:duration_-val is deprecated.  Use higgs_arduino_java-msg:duration_ instead.")
  (duration_ m))

(cl:ensure-generic-function 'byte_v-val :lambda-list '(m))
(cl:defmethod byte_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:byte_v-val is deprecated.  Use higgs_arduino_java-msg:byte_v instead.")
  (byte_v m))

(cl:ensure-generic-function 'byte_f-val :lambda-list '(m))
(cl:defmethod byte_f-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:byte_f-val is deprecated.  Use higgs_arduino_java-msg:byte_f instead.")
  (byte_f m))

(cl:ensure-generic-function 'float64_v-val :lambda-list '(m))
(cl:defmethod float64_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:float64_v-val is deprecated.  Use higgs_arduino_java-msg:float64_v instead.")
  (float64_v m))

(cl:ensure-generic-function 'float64_f-val :lambda-list '(m))
(cl:defmethod float64_f-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:float64_f-val is deprecated.  Use higgs_arduino_java-msg:float64_f instead.")
  (float64_f m))

(cl:ensure-generic-function 'string_v-val :lambda-list '(m))
(cl:defmethod string_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:string_v-val is deprecated.  Use higgs_arduino_java-msg:string_v instead.")
  (string_v m))

(cl:ensure-generic-function 'string_f-val :lambda-list '(m))
(cl:defmethod string_f-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:string_f-val is deprecated.  Use higgs_arduino_java-msg:string_f instead.")
  (string_f m))

(cl:ensure-generic-function 'time_v-val :lambda-list '(m))
(cl:defmethod time_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:time_v-val is deprecated.  Use higgs_arduino_java-msg:time_v instead.")
  (time_v m))

(cl:ensure-generic-function 'time_f-val :lambda-list '(m))
(cl:defmethod time_f-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:time_f-val is deprecated.  Use higgs_arduino_java-msg:time_f instead.")
  (time_f m))

(cl:ensure-generic-function 'Byte_-val :lambda-list '(m))
(cl:defmethod Byte_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:Byte_-val is deprecated.  Use higgs_arduino_java-msg:Byte_ instead.")
  (Byte_ m))

(cl:ensure-generic-function 'Byte_v-val :lambda-list '(m))
(cl:defmethod Byte_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:Byte_v-val is deprecated.  Use higgs_arduino_java-msg:Byte_v instead.")
  (Byte_v m))

(cl:ensure-generic-function 'ByteMultiArray_-val :lambda-list '(m))
(cl:defmethod ByteMultiArray_-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:ByteMultiArray_-val is deprecated.  Use higgs_arduino_java-msg:ByteMultiArray_ instead.")
  (ByteMultiArray_ m))

(cl:ensure-generic-function 'ByteMultiArray_v-val :lambda-list '(m))
(cl:defmethod ByteMultiArray_v-val ((m <TestDataTypes>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader higgs_arduino_java-msg:ByteMultiArray_v-val is deprecated.  Use higgs_arduino_java-msg:ByteMultiArray_v instead.")
  (ByteMultiArray_v m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TestDataTypes>) ostream)
  "Serializes a message object of type '<TestDataTypes>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'byte_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'char_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint8_)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'int8_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint16_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint16_)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'int16_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint32_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint32_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'uint32_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'uint32_)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'int32_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'uint64_)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'uint64_)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'int64_)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'float32_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'float64_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'string_))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'string_))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'time_)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'time_) (cl:floor (cl:slot-value msg 'time_)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'duration_)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'duration_) (cl:floor (cl:slot-value msg 'duration_)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'byte_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'byte_v))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'byte_f))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'float64_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'float64_v))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'float64_f))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'string_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'string_v))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'string_f))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'time_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__sec (cl:floor ele))
        (__nsec (cl:round (cl:* 1e9 (cl:- ele (cl:floor ele))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream)))
   (cl:slot-value msg 'time_v))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__sec (cl:floor ele))
        (__nsec (cl:round (cl:* 1e9 (cl:- ele (cl:floor ele))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream)))
   (cl:slot-value msg 'time_f))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Byte_) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Byte_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Byte_v))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ByteMultiArray_) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ByteMultiArray_v))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'ByteMultiArray_v))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TestDataTypes>) istream)
  "Deserializes a message object of type '<TestDataTypes>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'byte_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'char_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint8_)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'int8_) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint16_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint16_)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'int16_) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint32_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint32_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'uint32_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'uint32_)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'int32_) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'uint64_)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'int64_) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'float32_) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'float64_) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'string_) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'string_) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'time_) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'duration_) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'byte_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'byte_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  (cl:setf (cl:slot-value msg 'byte_f) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'byte_f)))
    (cl:dotimes (i 2)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'float64_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'float64_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:setf (cl:slot-value msg 'float64_f) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'float64_f)))
    (cl:dotimes (i 2)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'string_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'string_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  (cl:setf (cl:slot-value msg 'string_f) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'string_f)))
    (cl:dotimes (i 2)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'time_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'time_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9)))))))
  (cl:setf (cl:slot-value msg 'time_f) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'time_f)))
    (cl:dotimes (i 2)
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Byte_) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Byte_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Byte_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Byte))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ByteMultiArray_) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ByteMultiArray_v) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ByteMultiArray_v)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:ByteMultiArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TestDataTypes>)))
  "Returns string type for a message object of type '<TestDataTypes>"
  "higgs_arduino_java/TestDataTypes")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestDataTypes)))
  "Returns string type for a message object of type 'TestDataTypes"
  "higgs_arduino_java/TestDataTypes")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TestDataTypes>)))
  "Returns md5sum for a message object of type '<TestDataTypes>"
  "25bc379e8ef2913896f76e9ef8bedbdc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TestDataTypes)))
  "Returns md5sum for a message object of type 'TestDataTypes"
  "25bc379e8ef2913896f76e9ef8bedbdc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TestDataTypes>)))
  "Returns full string definition for message of type '<TestDataTypes>"
  (cl:format cl:nil "# Test all primitive types~%byte     byte_~%char     char_~%uint8    uint8_~%int8     int8_~%uint16   uint16_~%int16    int16_~%uint32   uint32_~%int32    int32_~%uint64   uint64_~%int64    int64_~%float32  float32_~%float64  float64_~%string   string_~%time     time_~%duration duration_~%~%# Test a smattering of array types~%byte[]     byte_v~%byte[2]    byte_f~%float64[]  float64_v~%float64[2] float64_f~%string[]   string_v~%string[2]  string_f~%time[]     time_v~%time[2]    time_f~%~%# Test submsgs, including both fixed and var length~%std_msgs/Byte    Byte_~%std_msgs/Byte[]  Byte_v~%~%std_msgs/ByteMultiArray    ByteMultiArray_~%std_msgs/ByteMultiArray[]  ByteMultiArray_v~%~%# Unfortunately, can't test these because roscpp message generation~%# is broken.  Hopefully rosjava works correctly ...~%# TODO: put these back in.~%~%# std_msgs/Byte[2] Byte_f~%# std_msgs/ByteMultiArray[2] ByteMultiArray_f~%~%================================================================================~%MSG: std_msgs/Byte~%byte data~%~%================================================================================~%MSG: std_msgs/ByteMultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%byte[]            data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding bytes at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TestDataTypes)))
  "Returns full string definition for message of type 'TestDataTypes"
  (cl:format cl:nil "# Test all primitive types~%byte     byte_~%char     char_~%uint8    uint8_~%int8     int8_~%uint16   uint16_~%int16    int16_~%uint32   uint32_~%int32    int32_~%uint64   uint64_~%int64    int64_~%float32  float32_~%float64  float64_~%string   string_~%time     time_~%duration duration_~%~%# Test a smattering of array types~%byte[]     byte_v~%byte[2]    byte_f~%float64[]  float64_v~%float64[2] float64_f~%string[]   string_v~%string[2]  string_f~%time[]     time_v~%time[2]    time_f~%~%# Test submsgs, including both fixed and var length~%std_msgs/Byte    Byte_~%std_msgs/Byte[]  Byte_v~%~%std_msgs/ByteMultiArray    ByteMultiArray_~%std_msgs/ByteMultiArray[]  ByteMultiArray_v~%~%# Unfortunately, can't test these because roscpp message generation~%# is broken.  Hopefully rosjava works correctly ...~%# TODO: put these back in.~%~%# std_msgs/Byte[2] Byte_f~%# std_msgs/ByteMultiArray[2] ByteMultiArray_f~%~%================================================================================~%MSG: std_msgs/Byte~%byte data~%~%================================================================================~%MSG: std_msgs/ByteMultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%byte[]            data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding bytes at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TestDataTypes>))
  (cl:+ 0
     1
     1
     1
     1
     2
     2
     4
     4
     8
     8
     4
     8
     4 (cl:length (cl:slot-value msg 'string_))
     8
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'byte_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'byte_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'float64_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'float64_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'string_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'string_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'time_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'time_f) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Byte_))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Byte_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ByteMultiArray_))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ByteMultiArray_v) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TestDataTypes>))
  "Converts a ROS message object to a list"
  (cl:list 'TestDataTypes
    (cl:cons ':byte_ (byte_ msg))
    (cl:cons ':char_ (char_ msg))
    (cl:cons ':uint8_ (uint8_ msg))
    (cl:cons ':int8_ (int8_ msg))
    (cl:cons ':uint16_ (uint16_ msg))
    (cl:cons ':int16_ (int16_ msg))
    (cl:cons ':uint32_ (uint32_ msg))
    (cl:cons ':int32_ (int32_ msg))
    (cl:cons ':uint64_ (uint64_ msg))
    (cl:cons ':int64_ (int64_ msg))
    (cl:cons ':float32_ (float32_ msg))
    (cl:cons ':float64_ (float64_ msg))
    (cl:cons ':string_ (string_ msg))
    (cl:cons ':time_ (time_ msg))
    (cl:cons ':duration_ (duration_ msg))
    (cl:cons ':byte_v (byte_v msg))
    (cl:cons ':byte_f (byte_f msg))
    (cl:cons ':float64_v (float64_v msg))
    (cl:cons ':float64_f (float64_f msg))
    (cl:cons ':string_v (string_v msg))
    (cl:cons ':string_f (string_f msg))
    (cl:cons ':time_v (time_v msg))
    (cl:cons ':time_f (time_f msg))
    (cl:cons ':Byte_ (Byte_ msg))
    (cl:cons ':Byte_v (Byte_v msg))
    (cl:cons ':ByteMultiArray_ (ByteMultiArray_ msg))
    (cl:cons ':ByteMultiArray_v (ByteMultiArray_v msg))
))
