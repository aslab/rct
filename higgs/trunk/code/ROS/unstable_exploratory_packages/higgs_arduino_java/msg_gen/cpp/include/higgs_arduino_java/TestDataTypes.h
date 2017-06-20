/* Auto-generated by genmsg_cpp for file /usr/local/ros_aslab/higgs_arduino_java/msg/TestDataTypes.msg */
#ifndef HIGGS_ARDUINO_JAVA_MESSAGE_TESTDATATYPES_H
#define HIGGS_ARDUINO_JAVA_MESSAGE_TESTDATATYPES_H
#include <string>
#include <vector>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"

#include "std_msgs/Byte.h"
#include "std_msgs/Byte.h"
#include "std_msgs/ByteMultiArray.h"
#include "std_msgs/ByteMultiArray.h"

namespace higgs_arduino_java
{
template <class ContainerAllocator>
struct TestDataTypes_ : public ros::Message
{
  typedef TestDataTypes_<ContainerAllocator> Type;

  TestDataTypes_()
  : byte_(0)
  , char_(0)
  , uint8_(0)
  , int8_(0)
  , uint16_(0)
  , int16_(0)
  , uint32_(0)
  , int32_(0)
  , uint64_(0)
  , int64_(0)
  , float32_(0.0)
  , float64_(0.0)
  , string_()
  , time_()
  , duration_()
  , byte_v()
  , byte_f()
  , float64_v()
  , float64_f()
  , string_v()
  , string_f()
  , time_v()
  , time_f()
  , Byte_()
  , Byte_v()
  , ByteMultiArray_()
  , ByteMultiArray_v()
  {
    byte_f.assign(0);
    float64_f.assign(0.0);
  }

  TestDataTypes_(const ContainerAllocator& _alloc)
  : byte_(0)
  , char_(0)
  , uint8_(0)
  , int8_(0)
  , uint16_(0)
  , int16_(0)
  , uint32_(0)
  , int32_(0)
  , uint64_(0)
  , int64_(0)
  , float32_(0.0)
  , float64_(0.0)
  , string_(_alloc)
  , time_()
  , duration_()
  , byte_v(_alloc)
  , byte_f()
  , float64_v(_alloc)
  , float64_f()
  , string_v(_alloc)
  , string_f()
  , time_v(_alloc)
  , time_f()
  , Byte_(_alloc)
  , Byte_v(_alloc)
  , ByteMultiArray_(_alloc)
  , ByteMultiArray_v(_alloc)
  {
    byte_f.assign(0);
    float64_f.assign(0.0);
    string_f.assign(std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > (_alloc));
  }

  typedef int8_t _byte__type;
  int8_t byte_;

  typedef uint8_t _char__type;
  uint8_t char_;

  typedef uint8_t _uint8__type;
  uint8_t uint8_;

  typedef int8_t _int8__type;
  int8_t int8_;

  typedef uint16_t _uint16__type;
  uint16_t uint16_;

  typedef int16_t _int16__type;
  int16_t int16_;

  typedef uint32_t _uint32__type;
  uint32_t uint32_;

  typedef int32_t _int32__type;
  int32_t int32_;

  typedef uint64_t _uint64__type;
  uint64_t uint64_;

  typedef int64_t _int64__type;
  int64_t int64_;

  typedef float _float32__type;
  float float32_;

  typedef double _float64__type;
  double float64_;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _string__type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  string_;

  typedef ros::Time _time__type;
  ros::Time time_;

  typedef ros::Duration _duration__type;
  ros::Duration duration_;

  typedef std::vector<int8_t, typename ContainerAllocator::template rebind<int8_t>::other >  _byte_v_type;
  std::vector<int8_t, typename ContainerAllocator::template rebind<int8_t>::other >  byte_v;

  typedef boost::array<int8_t, 2>  _byte_f_type;
  boost::array<int8_t, 2>  byte_f;

  typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _float64_v_type;
  std::vector<double, typename ContainerAllocator::template rebind<double>::other >  float64_v;

  typedef boost::array<double, 2>  _float64_f_type;
  boost::array<double, 2>  float64_f;

  typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _string_v_type;
  std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  string_v;

  typedef boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 2>  _string_f_type;
  boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 2>  string_f;

  typedef std::vector<ros::Time, typename ContainerAllocator::template rebind<ros::Time>::other >  _time_v_type;
  std::vector<ros::Time, typename ContainerAllocator::template rebind<ros::Time>::other >  time_v;

  typedef boost::array<ros::Time, 2>  _time_f_type;
  boost::array<ros::Time, 2>  time_f;

  typedef  ::std_msgs::Byte_<ContainerAllocator>  _Byte__type;
   ::std_msgs::Byte_<ContainerAllocator>  Byte_;

  typedef std::vector< ::std_msgs::Byte_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::Byte_<ContainerAllocator> >::other >  _Byte_v_type;
  std::vector< ::std_msgs::Byte_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::Byte_<ContainerAllocator> >::other >  Byte_v;

  typedef  ::std_msgs::ByteMultiArray_<ContainerAllocator>  _ByteMultiArray__type;
   ::std_msgs::ByteMultiArray_<ContainerAllocator>  ByteMultiArray_;

  typedef std::vector< ::std_msgs::ByteMultiArray_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::other >  _ByteMultiArray_v_type;
  std::vector< ::std_msgs::ByteMultiArray_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::other >  ByteMultiArray_v;


  ROS_DEPRECATED uint32_t get_byte_v_size() const { return (uint32_t)byte_v.size(); }
  ROS_DEPRECATED void set_byte_v_size(uint32_t size) { byte_v.resize((size_t)size); }
  ROS_DEPRECATED void get_byte_v_vec(std::vector<int8_t, typename ContainerAllocator::template rebind<int8_t>::other > & vec) const { vec = this->byte_v; }
  ROS_DEPRECATED void set_byte_v_vec(const std::vector<int8_t, typename ContainerAllocator::template rebind<int8_t>::other > & vec) { this->byte_v = vec; }
  ROS_DEPRECATED uint32_t get_byte_f_size() const { return (uint32_t)byte_f.size(); }
  ROS_DEPRECATED uint32_t get_float64_v_size() const { return (uint32_t)float64_v.size(); }
  ROS_DEPRECATED void set_float64_v_size(uint32_t size) { float64_v.resize((size_t)size); }
  ROS_DEPRECATED void get_float64_v_vec(std::vector<double, typename ContainerAllocator::template rebind<double>::other > & vec) const { vec = this->float64_v; }
  ROS_DEPRECATED void set_float64_v_vec(const std::vector<double, typename ContainerAllocator::template rebind<double>::other > & vec) { this->float64_v = vec; }
  ROS_DEPRECATED uint32_t get_float64_f_size() const { return (uint32_t)float64_f.size(); }
  ROS_DEPRECATED uint32_t get_string_v_size() const { return (uint32_t)string_v.size(); }
  ROS_DEPRECATED void set_string_v_size(uint32_t size) { string_v.resize((size_t)size); }
  ROS_DEPRECATED void get_string_v_vec(std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other > & vec) const { vec = this->string_v; }
  ROS_DEPRECATED void set_string_v_vec(const std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other > & vec) { this->string_v = vec; }
  ROS_DEPRECATED uint32_t get_string_f_size() const { return (uint32_t)string_f.size(); }
  ROS_DEPRECATED uint32_t get_time_v_size() const { return (uint32_t)time_v.size(); }
  ROS_DEPRECATED void set_time_v_size(uint32_t size) { time_v.resize((size_t)size); }
  ROS_DEPRECATED void get_time_v_vec(std::vector<ros::Time, typename ContainerAllocator::template rebind<ros::Time>::other > & vec) const { vec = this->time_v; }
  ROS_DEPRECATED void set_time_v_vec(const std::vector<ros::Time, typename ContainerAllocator::template rebind<ros::Time>::other > & vec) { this->time_v = vec; }
  ROS_DEPRECATED uint32_t get_time_f_size() const { return (uint32_t)time_f.size(); }
  ROS_DEPRECATED uint32_t get_Byte_v_size() const { return (uint32_t)Byte_v.size(); }
  ROS_DEPRECATED void set_Byte_v_size(uint32_t size) { Byte_v.resize((size_t)size); }
  ROS_DEPRECATED void get_Byte_v_vec(std::vector< ::std_msgs::Byte_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::Byte_<ContainerAllocator> >::other > & vec) const { vec = this->Byte_v; }
  ROS_DEPRECATED void set_Byte_v_vec(const std::vector< ::std_msgs::Byte_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::Byte_<ContainerAllocator> >::other > & vec) { this->Byte_v = vec; }
  ROS_DEPRECATED uint32_t get_ByteMultiArray_v_size() const { return (uint32_t)ByteMultiArray_v.size(); }
  ROS_DEPRECATED void set_ByteMultiArray_v_size(uint32_t size) { ByteMultiArray_v.resize((size_t)size); }
  ROS_DEPRECATED void get_ByteMultiArray_v_vec(std::vector< ::std_msgs::ByteMultiArray_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::other > & vec) const { vec = this->ByteMultiArray_v; }
  ROS_DEPRECATED void set_ByteMultiArray_v_vec(const std::vector< ::std_msgs::ByteMultiArray_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::other > & vec) { this->ByteMultiArray_v = vec; }
private:
  static const char* __s_getDataType_() { return "higgs_arduino_java/TestDataTypes"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "25bc379e8ef2913896f76e9ef8bedbdc"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "# Test all primitive types\n\
byte     byte_\n\
char     char_\n\
uint8    uint8_\n\
int8     int8_\n\
uint16   uint16_\n\
int16    int16_\n\
uint32   uint32_\n\
int32    int32_\n\
uint64   uint64_\n\
int64    int64_\n\
float32  float32_\n\
float64  float64_\n\
string   string_\n\
time     time_\n\
duration duration_\n\
\n\
# Test a smattering of array types\n\
byte[]     byte_v\n\
byte[2]    byte_f\n\
float64[]  float64_v\n\
float64[2] float64_f\n\
string[]   string_v\n\
string[2]  string_f\n\
time[]     time_v\n\
time[2]    time_f\n\
\n\
# Test submsgs, including both fixed and var length\n\
std_msgs/Byte    Byte_\n\
std_msgs/Byte[]  Byte_v\n\
\n\
std_msgs/ByteMultiArray    ByteMultiArray_\n\
std_msgs/ByteMultiArray[]  ByteMultiArray_v\n\
\n\
# Unfortunately, can't test these because roscpp message generation\n\
# is broken.  Hopefully rosjava works correctly ...\n\
# TODO: put these back in.\n\
\n\
# std_msgs/Byte[2] Byte_f\n\
# std_msgs/ByteMultiArray[2] ByteMultiArray_f\n\
\n\
================================================================================\n\
MSG: std_msgs/Byte\n\
byte data\n\
\n\
================================================================================\n\
MSG: std_msgs/ByteMultiArray\n\
# Please look at the MultiArrayLayout message definition for\n\
# documentation on all multiarrays.\n\
\n\
MultiArrayLayout  layout        # specification of data layout\n\
byte[]            data          # array of data\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/MultiArrayLayout\n\
# The multiarray declares a generic multi-dimensional array of a\n\
# particular data type.  Dimensions are ordered from outer most\n\
# to inner most.\n\
\n\
MultiArrayDimension[] dim # Array of dimension properties\n\
uint32 data_offset        # padding bytes at front of data\n\
\n\
# Accessors should ALWAYS be written in terms of dimension stride\n\
# and specified outer-most dimension first.\n\
# \n\
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]\n\
#\n\
# A standard, 3-channel 640x480 image with interleaved color channels\n\
# would be specified as:\n\
#\n\
# dim[0].label  = \"height\"\n\
# dim[0].size   = 480\n\
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)\n\
# dim[1].label  = \"width\"\n\
# dim[1].size   = 640\n\
# dim[1].stride = 3*640 = 1920\n\
# dim[2].label  = \"channel\"\n\
# dim[2].size   = 3\n\
# dim[2].stride = 3\n\
#\n\
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.\n\
================================================================================\n\
MSG: std_msgs/MultiArrayDimension\n\
string label   # label of given dimension\n\
uint32 size    # size of given dimension (in type units)\n\
uint32 stride  # stride of given dimension\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, byte_);
    ros::serialization::serialize(stream, char_);
    ros::serialization::serialize(stream, uint8_);
    ros::serialization::serialize(stream, int8_);
    ros::serialization::serialize(stream, uint16_);
    ros::serialization::serialize(stream, int16_);
    ros::serialization::serialize(stream, uint32_);
    ros::serialization::serialize(stream, int32_);
    ros::serialization::serialize(stream, uint64_);
    ros::serialization::serialize(stream, int64_);
    ros::serialization::serialize(stream, float32_);
    ros::serialization::serialize(stream, float64_);
    ros::serialization::serialize(stream, string_);
    ros::serialization::serialize(stream, time_);
    ros::serialization::serialize(stream, duration_);
    ros::serialization::serialize(stream, byte_v);
    ros::serialization::serialize(stream, byte_f);
    ros::serialization::serialize(stream, float64_v);
    ros::serialization::serialize(stream, float64_f);
    ros::serialization::serialize(stream, string_v);
    ros::serialization::serialize(stream, string_f);
    ros::serialization::serialize(stream, time_v);
    ros::serialization::serialize(stream, time_f);
    ros::serialization::serialize(stream, Byte_);
    ros::serialization::serialize(stream, Byte_v);
    ros::serialization::serialize(stream, ByteMultiArray_);
    ros::serialization::serialize(stream, ByteMultiArray_v);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, byte_);
    ros::serialization::deserialize(stream, char_);
    ros::serialization::deserialize(stream, uint8_);
    ros::serialization::deserialize(stream, int8_);
    ros::serialization::deserialize(stream, uint16_);
    ros::serialization::deserialize(stream, int16_);
    ros::serialization::deserialize(stream, uint32_);
    ros::serialization::deserialize(stream, int32_);
    ros::serialization::deserialize(stream, uint64_);
    ros::serialization::deserialize(stream, int64_);
    ros::serialization::deserialize(stream, float32_);
    ros::serialization::deserialize(stream, float64_);
    ros::serialization::deserialize(stream, string_);
    ros::serialization::deserialize(stream, time_);
    ros::serialization::deserialize(stream, duration_);
    ros::serialization::deserialize(stream, byte_v);
    ros::serialization::deserialize(stream, byte_f);
    ros::serialization::deserialize(stream, float64_v);
    ros::serialization::deserialize(stream, float64_f);
    ros::serialization::deserialize(stream, string_v);
    ros::serialization::deserialize(stream, string_f);
    ros::serialization::deserialize(stream, time_v);
    ros::serialization::deserialize(stream, time_f);
    ros::serialization::deserialize(stream, Byte_);
    ros::serialization::deserialize(stream, Byte_v);
    ros::serialization::deserialize(stream, ByteMultiArray_);
    ros::serialization::deserialize(stream, ByteMultiArray_v);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(byte_);
    size += ros::serialization::serializationLength(char_);
    size += ros::serialization::serializationLength(uint8_);
    size += ros::serialization::serializationLength(int8_);
    size += ros::serialization::serializationLength(uint16_);
    size += ros::serialization::serializationLength(int16_);
    size += ros::serialization::serializationLength(uint32_);
    size += ros::serialization::serializationLength(int32_);
    size += ros::serialization::serializationLength(uint64_);
    size += ros::serialization::serializationLength(int64_);
    size += ros::serialization::serializationLength(float32_);
    size += ros::serialization::serializationLength(float64_);
    size += ros::serialization::serializationLength(string_);
    size += ros::serialization::serializationLength(time_);
    size += ros::serialization::serializationLength(duration_);
    size += ros::serialization::serializationLength(byte_v);
    size += ros::serialization::serializationLength(byte_f);
    size += ros::serialization::serializationLength(float64_v);
    size += ros::serialization::serializationLength(float64_f);
    size += ros::serialization::serializationLength(string_v);
    size += ros::serialization::serializationLength(string_f);
    size += ros::serialization::serializationLength(time_v);
    size += ros::serialization::serializationLength(time_f);
    size += ros::serialization::serializationLength(Byte_);
    size += ros::serialization::serializationLength(Byte_v);
    size += ros::serialization::serializationLength(ByteMultiArray_);
    size += ros::serialization::serializationLength(ByteMultiArray_v);
    return size;
  }

  typedef boost::shared_ptr< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator>  const> ConstPtr;
}; // struct TestDataTypes
typedef  ::higgs_arduino_java::TestDataTypes_<std::allocator<void> > TestDataTypes;

typedef boost::shared_ptr< ::higgs_arduino_java::TestDataTypes> TestDataTypesPtr;
typedef boost::shared_ptr< ::higgs_arduino_java::TestDataTypes const> TestDataTypesConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace higgs_arduino_java

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> > {
  static const char* value() 
  {
    return "25bc379e8ef2913896f76e9ef8bedbdc";
  }

  static const char* value(const  ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x25bc379e8ef29138ULL;
  static const uint64_t static_value2 = 0x96f76e9ef8bedbdcULL;
};

template<class ContainerAllocator>
struct DataType< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> > {
  static const char* value() 
  {
    return "higgs_arduino_java/TestDataTypes";
  }

  static const char* value(const  ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# Test all primitive types\n\
byte     byte_\n\
char     char_\n\
uint8    uint8_\n\
int8     int8_\n\
uint16   uint16_\n\
int16    int16_\n\
uint32   uint32_\n\
int32    int32_\n\
uint64   uint64_\n\
int64    int64_\n\
float32  float32_\n\
float64  float64_\n\
string   string_\n\
time     time_\n\
duration duration_\n\
\n\
# Test a smattering of array types\n\
byte[]     byte_v\n\
byte[2]    byte_f\n\
float64[]  float64_v\n\
float64[2] float64_f\n\
string[]   string_v\n\
string[2]  string_f\n\
time[]     time_v\n\
time[2]    time_f\n\
\n\
# Test submsgs, including both fixed and var length\n\
std_msgs/Byte    Byte_\n\
std_msgs/Byte[]  Byte_v\n\
\n\
std_msgs/ByteMultiArray    ByteMultiArray_\n\
std_msgs/ByteMultiArray[]  ByteMultiArray_v\n\
\n\
# Unfortunately, can't test these because roscpp message generation\n\
# is broken.  Hopefully rosjava works correctly ...\n\
# TODO: put these back in.\n\
\n\
# std_msgs/Byte[2] Byte_f\n\
# std_msgs/ByteMultiArray[2] ByteMultiArray_f\n\
\n\
================================================================================\n\
MSG: std_msgs/Byte\n\
byte data\n\
\n\
================================================================================\n\
MSG: std_msgs/ByteMultiArray\n\
# Please look at the MultiArrayLayout message definition for\n\
# documentation on all multiarrays.\n\
\n\
MultiArrayLayout  layout        # specification of data layout\n\
byte[]            data          # array of data\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/MultiArrayLayout\n\
# The multiarray declares a generic multi-dimensional array of a\n\
# particular data type.  Dimensions are ordered from outer most\n\
# to inner most.\n\
\n\
MultiArrayDimension[] dim # Array of dimension properties\n\
uint32 data_offset        # padding bytes at front of data\n\
\n\
# Accessors should ALWAYS be written in terms of dimension stride\n\
# and specified outer-most dimension first.\n\
# \n\
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]\n\
#\n\
# A standard, 3-channel 640x480 image with interleaved color channels\n\
# would be specified as:\n\
#\n\
# dim[0].label  = \"height\"\n\
# dim[0].size   = 480\n\
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)\n\
# dim[1].label  = \"width\"\n\
# dim[1].size   = 640\n\
# dim[1].stride = 3*640 = 1920\n\
# dim[2].label  = \"channel\"\n\
# dim[2].size   = 3\n\
# dim[2].stride = 3\n\
#\n\
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.\n\
================================================================================\n\
MSG: std_msgs/MultiArrayDimension\n\
string label   # label of given dimension\n\
uint32 size    # size of given dimension (in type units)\n\
uint32 stride  # stride of given dimension\n\
";
  }

  static const char* value(const  ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.byte_);
    stream.next(m.char_);
    stream.next(m.uint8_);
    stream.next(m.int8_);
    stream.next(m.uint16_);
    stream.next(m.int16_);
    stream.next(m.uint32_);
    stream.next(m.int32_);
    stream.next(m.uint64_);
    stream.next(m.int64_);
    stream.next(m.float32_);
    stream.next(m.float64_);
    stream.next(m.string_);
    stream.next(m.time_);
    stream.next(m.duration_);
    stream.next(m.byte_v);
    stream.next(m.byte_f);
    stream.next(m.float64_v);
    stream.next(m.float64_f);
    stream.next(m.string_v);
    stream.next(m.string_f);
    stream.next(m.time_v);
    stream.next(m.time_f);
    stream.next(m.Byte_);
    stream.next(m.Byte_v);
    stream.next(m.ByteMultiArray_);
    stream.next(m.ByteMultiArray_v);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct TestDataTypes_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::higgs_arduino_java::TestDataTypes_<ContainerAllocator> & v) 
  {
    s << indent << "byte_: ";
    Printer<int8_t>::stream(s, indent + "  ", v.byte_);
    s << indent << "char_: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.char_);
    s << indent << "uint8_: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.uint8_);
    s << indent << "int8_: ";
    Printer<int8_t>::stream(s, indent + "  ", v.int8_);
    s << indent << "uint16_: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.uint16_);
    s << indent << "int16_: ";
    Printer<int16_t>::stream(s, indent + "  ", v.int16_);
    s << indent << "uint32_: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.uint32_);
    s << indent << "int32_: ";
    Printer<int32_t>::stream(s, indent + "  ", v.int32_);
    s << indent << "uint64_: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.uint64_);
    s << indent << "int64_: ";
    Printer<int64_t>::stream(s, indent + "  ", v.int64_);
    s << indent << "float32_: ";
    Printer<float>::stream(s, indent + "  ", v.float32_);
    s << indent << "float64_: ";
    Printer<double>::stream(s, indent + "  ", v.float64_);
    s << indent << "string_: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.string_);
    s << indent << "time_: ";
    Printer<ros::Time>::stream(s, indent + "  ", v.time_);
    s << indent << "duration_: ";
    Printer<ros::Duration>::stream(s, indent + "  ", v.duration_);
    s << indent << "byte_v[]" << std::endl;
    for (size_t i = 0; i < v.byte_v.size(); ++i)
    {
      s << indent << "  byte_v[" << i << "]: ";
      Printer<int8_t>::stream(s, indent + "  ", v.byte_v[i]);
    }
    s << indent << "byte_f[]" << std::endl;
    for (size_t i = 0; i < v.byte_f.size(); ++i)
    {
      s << indent << "  byte_f[" << i << "]: ";
      Printer<int8_t>::stream(s, indent + "  ", v.byte_f[i]);
    }
    s << indent << "float64_v[]" << std::endl;
    for (size_t i = 0; i < v.float64_v.size(); ++i)
    {
      s << indent << "  float64_v[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.float64_v[i]);
    }
    s << indent << "float64_f[]" << std::endl;
    for (size_t i = 0; i < v.float64_f.size(); ++i)
    {
      s << indent << "  float64_f[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.float64_f[i]);
    }
    s << indent << "string_v[]" << std::endl;
    for (size_t i = 0; i < v.string_v.size(); ++i)
    {
      s << indent << "  string_v[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.string_v[i]);
    }
    s << indent << "string_f[]" << std::endl;
    for (size_t i = 0; i < v.string_f.size(); ++i)
    {
      s << indent << "  string_f[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.string_f[i]);
    }
    s << indent << "time_v[]" << std::endl;
    for (size_t i = 0; i < v.time_v.size(); ++i)
    {
      s << indent << "  time_v[" << i << "]: ";
      Printer<ros::Time>::stream(s, indent + "  ", v.time_v[i]);
    }
    s << indent << "time_f[]" << std::endl;
    for (size_t i = 0; i < v.time_f.size(); ++i)
    {
      s << indent << "  time_f[" << i << "]: ";
      Printer<ros::Time>::stream(s, indent + "  ", v.time_f[i]);
    }
    s << indent << "Byte_: ";
s << std::endl;
    Printer< ::std_msgs::Byte_<ContainerAllocator> >::stream(s, indent + "  ", v.Byte_);
    s << indent << "Byte_v[]" << std::endl;
    for (size_t i = 0; i < v.Byte_v.size(); ++i)
    {
      s << indent << "  Byte_v[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::std_msgs::Byte_<ContainerAllocator> >::stream(s, indent + "    ", v.Byte_v[i]);
    }
    s << indent << "ByteMultiArray_: ";
s << std::endl;
    Printer< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::stream(s, indent + "  ", v.ByteMultiArray_);
    s << indent << "ByteMultiArray_v[]" << std::endl;
    for (size_t i = 0; i < v.ByteMultiArray_v.size(); ++i)
    {
      s << indent << "  ByteMultiArray_v[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::std_msgs::ByteMultiArray_<ContainerAllocator> >::stream(s, indent + "    ", v.ByteMultiArray_v[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // HIGGS_ARDUINO_JAVA_MESSAGE_TESTDATATYPES_H

