// Generated by gencpp from file ardrone_autonomy/navdata_vision_detect.msg
// DO NOT EDIT!


#ifndef ARDRONE_AUTONOMY_MESSAGE_NAVDATA_VISION_DETECT_H
#define ARDRONE_AUTONOMY_MESSAGE_NAVDATA_VISION_DETECT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <ardrone_autonomy/matrix33.h>
#include <ardrone_autonomy/vector31.h>

namespace ardrone_autonomy
{
template <class ContainerAllocator>
struct navdata_vision_detect_
{
  typedef navdata_vision_detect_<ContainerAllocator> Type;

  navdata_vision_detect_()
    : header()
    , drone_time(0.0)
    , tag(0)
    , size(0)
    , nb_detected(0)
    , type()
    , xc()
    , yc()
    , width()
    , height()
    , dist()
    , orientation_angle()
    , rotation()
    , translation()
    , camera_source()  {
    }
  navdata_vision_detect_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , drone_time(0.0)
    , tag(0)
    , size(0)
    , nb_detected(0)
    , type(_alloc)
    , xc(_alloc)
    , yc(_alloc)
    , width(_alloc)
    , height(_alloc)
    , dist(_alloc)
    , orientation_angle(_alloc)
    , rotation(_alloc)
    , translation(_alloc)
    , camera_source(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _drone_time_type;
  _drone_time_type drone_time;

   typedef uint16_t _tag_type;
  _tag_type tag;

   typedef uint16_t _size_type;
  _size_type size;

   typedef uint32_t _nb_detected_type;
  _nb_detected_type nb_detected;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _type_type;
  _type_type type;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _xc_type;
  _xc_type xc;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _yc_type;
  _yc_type yc;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _width_type;
  _width_type width;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _height_type;
  _height_type height;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _dist_type;
  _dist_type dist;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _orientation_angle_type;
  _orientation_angle_type orientation_angle;

   typedef std::vector< ::ardrone_autonomy::matrix33_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::ardrone_autonomy::matrix33_<ContainerAllocator> >::other >  _rotation_type;
  _rotation_type rotation;

   typedef std::vector< ::ardrone_autonomy::vector31_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::ardrone_autonomy::vector31_<ContainerAllocator> >::other >  _translation_type;
  _translation_type translation;

   typedef std::vector<uint32_t, typename ContainerAllocator::template rebind<uint32_t>::other >  _camera_source_type;
  _camera_source_type camera_source;




  typedef boost::shared_ptr< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> const> ConstPtr;

}; // struct navdata_vision_detect_

typedef ::ardrone_autonomy::navdata_vision_detect_<std::allocator<void> > navdata_vision_detect;

typedef boost::shared_ptr< ::ardrone_autonomy::navdata_vision_detect > navdata_vision_detectPtr;
typedef boost::shared_ptr< ::ardrone_autonomy::navdata_vision_detect const> navdata_vision_detectConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ardrone_autonomy

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'ardrone_autonomy': ['/home/jorge/tfm_ws/src/tum_simulator_ws/src/ardrone_autonomy-indigo-devel/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ab5f6b8c66aead58358d45a7c2dce7f6";
  }

  static const char* value(const ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xab5f6b8c66aead58ULL;
  static const uint64_t static_value2 = 0x358d45a7c2dce7f6ULL;
};

template<class ContainerAllocator>
struct DataType< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ardrone_autonomy/navdata_vision_detect";
  }

  static const char* value(const ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float64 drone_time\n\
uint16 tag\n\
uint16 size\n\
uint32 nb_detected\n\
uint32[] type\n\
uint32[] xc\n\
uint32[] yc\n\
uint32[] width\n\
uint32[] height\n\
uint32[] dist\n\
float32[] orientation_angle\n\
matrix33[] rotation\n\
vector31[] translation\n\
uint32[] camera_source\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: ardrone_autonomy/matrix33\n\
float32 m11\n\
float32 m12\n\
float32 m13\n\
float32 m21\n\
float32 m22\n\
float32 m23\n\
float32 m31\n\
float32 m32\n\
float32 m33\n\
================================================================================\n\
MSG: ardrone_autonomy/vector31\n\
float32 x\n\
float32 y\n\
float32 z\n\
";
  }

  static const char* value(const ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.drone_time);
      stream.next(m.tag);
      stream.next(m.size);
      stream.next(m.nb_detected);
      stream.next(m.type);
      stream.next(m.xc);
      stream.next(m.yc);
      stream.next(m.width);
      stream.next(m.height);
      stream.next(m.dist);
      stream.next(m.orientation_angle);
      stream.next(m.rotation);
      stream.next(m.translation);
      stream.next(m.camera_source);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct navdata_vision_detect_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ardrone_autonomy::navdata_vision_detect_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "drone_time: ";
    Printer<double>::stream(s, indent + "  ", v.drone_time);
    s << indent << "tag: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.tag);
    s << indent << "size: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.size);
    s << indent << "nb_detected: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.nb_detected);
    s << indent << "type[]" << std::endl;
    for (size_t i = 0; i < v.type.size(); ++i)
    {
      s << indent << "  type[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.type[i]);
    }
    s << indent << "xc[]" << std::endl;
    for (size_t i = 0; i < v.xc.size(); ++i)
    {
      s << indent << "  xc[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.xc[i]);
    }
    s << indent << "yc[]" << std::endl;
    for (size_t i = 0; i < v.yc.size(); ++i)
    {
      s << indent << "  yc[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.yc[i]);
    }
    s << indent << "width[]" << std::endl;
    for (size_t i = 0; i < v.width.size(); ++i)
    {
      s << indent << "  width[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.width[i]);
    }
    s << indent << "height[]" << std::endl;
    for (size_t i = 0; i < v.height.size(); ++i)
    {
      s << indent << "  height[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.height[i]);
    }
    s << indent << "dist[]" << std::endl;
    for (size_t i = 0; i < v.dist.size(); ++i)
    {
      s << indent << "  dist[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.dist[i]);
    }
    s << indent << "orientation_angle[]" << std::endl;
    for (size_t i = 0; i < v.orientation_angle.size(); ++i)
    {
      s << indent << "  orientation_angle[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.orientation_angle[i]);
    }
    s << indent << "rotation[]" << std::endl;
    for (size_t i = 0; i < v.rotation.size(); ++i)
    {
      s << indent << "  rotation[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::ardrone_autonomy::matrix33_<ContainerAllocator> >::stream(s, indent + "    ", v.rotation[i]);
    }
    s << indent << "translation[]" << std::endl;
    for (size_t i = 0; i < v.translation.size(); ++i)
    {
      s << indent << "  translation[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::ardrone_autonomy::vector31_<ContainerAllocator> >::stream(s, indent + "    ", v.translation[i]);
    }
    s << indent << "camera_source[]" << std::endl;
    for (size_t i = 0; i < v.camera_source.size(); ++i)
    {
      s << indent << "  camera_source[" << i << "]: ";
      Printer<uint32_t>::stream(s, indent + "  ", v.camera_source[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ARDRONE_AUTONOMY_MESSAGE_NAVDATA_VISION_DETECT_H
