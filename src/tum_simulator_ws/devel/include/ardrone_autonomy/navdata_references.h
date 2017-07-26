// Generated by gencpp from file ardrone_autonomy/navdata_references.msg
// DO NOT EDIT!


#ifndef ARDRONE_AUTONOMY_MESSAGE_NAVDATA_REFERENCES_H
#define ARDRONE_AUTONOMY_MESSAGE_NAVDATA_REFERENCES_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace ardrone_autonomy
{
template <class ContainerAllocator>
struct navdata_references_
{
  typedef navdata_references_<ContainerAllocator> Type;

  navdata_references_()
    : header()
    , drone_time(0.0)
    , tag(0)
    , size(0)
    , ref_theta(0)
    , ref_phi(0)
    , ref_theta_I(0)
    , ref_phi_I(0)
    , ref_pitch(0)
    , ref_roll(0)
    , ref_yaw(0)
    , ref_psi(0)
    , vx_ref(0.0)
    , vy_ref(0.0)
    , theta_mod(0.0)
    , phi_mod(0.0)
    , k_v_x(0.0)
    , k_v_y(0.0)
    , k_mode(0)
    , ui_time(0.0)
    , ui_theta(0.0)
    , ui_phi(0.0)
    , ui_psi(0.0)
    , ui_psi_accuracy(0.0)
    , ui_seq(0)  {
    }
  navdata_references_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , drone_time(0.0)
    , tag(0)
    , size(0)
    , ref_theta(0)
    , ref_phi(0)
    , ref_theta_I(0)
    , ref_phi_I(0)
    , ref_pitch(0)
    , ref_roll(0)
    , ref_yaw(0)
    , ref_psi(0)
    , vx_ref(0.0)
    , vy_ref(0.0)
    , theta_mod(0.0)
    , phi_mod(0.0)
    , k_v_x(0.0)
    , k_v_y(0.0)
    , k_mode(0)
    , ui_time(0.0)
    , ui_theta(0.0)
    , ui_phi(0.0)
    , ui_psi(0.0)
    , ui_psi_accuracy(0.0)
    , ui_seq(0)  {
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

   typedef int32_t _ref_theta_type;
  _ref_theta_type ref_theta;

   typedef int32_t _ref_phi_type;
  _ref_phi_type ref_phi;

   typedef int32_t _ref_theta_I_type;
  _ref_theta_I_type ref_theta_I;

   typedef int32_t _ref_phi_I_type;
  _ref_phi_I_type ref_phi_I;

   typedef int32_t _ref_pitch_type;
  _ref_pitch_type ref_pitch;

   typedef int32_t _ref_roll_type;
  _ref_roll_type ref_roll;

   typedef int32_t _ref_yaw_type;
  _ref_yaw_type ref_yaw;

   typedef int32_t _ref_psi_type;
  _ref_psi_type ref_psi;

   typedef float _vx_ref_type;
  _vx_ref_type vx_ref;

   typedef float _vy_ref_type;
  _vy_ref_type vy_ref;

   typedef float _theta_mod_type;
  _theta_mod_type theta_mod;

   typedef float _phi_mod_type;
  _phi_mod_type phi_mod;

   typedef float _k_v_x_type;
  _k_v_x_type k_v_x;

   typedef float _k_v_y_type;
  _k_v_y_type k_v_y;

   typedef uint32_t _k_mode_type;
  _k_mode_type k_mode;

   typedef float _ui_time_type;
  _ui_time_type ui_time;

   typedef float _ui_theta_type;
  _ui_theta_type ui_theta;

   typedef float _ui_phi_type;
  _ui_phi_type ui_phi;

   typedef float _ui_psi_type;
  _ui_psi_type ui_psi;

   typedef float _ui_psi_accuracy_type;
  _ui_psi_accuracy_type ui_psi_accuracy;

   typedef int32_t _ui_seq_type;
  _ui_seq_type ui_seq;




  typedef boost::shared_ptr< ::ardrone_autonomy::navdata_references_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ardrone_autonomy::navdata_references_<ContainerAllocator> const> ConstPtr;

}; // struct navdata_references_

typedef ::ardrone_autonomy::navdata_references_<std::allocator<void> > navdata_references;

typedef boost::shared_ptr< ::ardrone_autonomy::navdata_references > navdata_referencesPtr;
typedef boost::shared_ptr< ::ardrone_autonomy::navdata_references const> navdata_referencesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ardrone_autonomy::navdata_references_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ardrone_autonomy

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'ardrone_autonomy': ['/home/jorge/tum_simulator_ws/src/ardrone_autonomy-indigo-devel/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ardrone_autonomy::navdata_references_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ardrone_autonomy::navdata_references_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ardrone_autonomy::navdata_references_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
{
  static const char* value()
  {
    return "263b844b053f4a098c75c1c26a452911";
  }

  static const char* value(const ::ardrone_autonomy::navdata_references_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x263b844b053f4a09ULL;
  static const uint64_t static_value2 = 0x8c75c1c26a452911ULL;
};

template<class ContainerAllocator>
struct DataType< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ardrone_autonomy/navdata_references";
  }

  static const char* value(const ::ardrone_autonomy::navdata_references_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float64 drone_time\n\
uint16 tag\n\
uint16 size\n\
int32 ref_theta\n\
int32 ref_phi\n\
int32 ref_theta_I\n\
int32 ref_phi_I\n\
int32 ref_pitch\n\
int32 ref_roll\n\
int32 ref_yaw\n\
int32 ref_psi\n\
float32 vx_ref\n\
float32 vy_ref\n\
float32 theta_mod\n\
float32 phi_mod\n\
float32 k_v_x\n\
float32 k_v_y\n\
uint32 k_mode\n\
float32 ui_time\n\
float32 ui_theta\n\
float32 ui_phi\n\
float32 ui_psi\n\
float32 ui_psi_accuracy\n\
int32 ui_seq\n\
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
";
  }

  static const char* value(const ::ardrone_autonomy::navdata_references_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.drone_time);
      stream.next(m.tag);
      stream.next(m.size);
      stream.next(m.ref_theta);
      stream.next(m.ref_phi);
      stream.next(m.ref_theta_I);
      stream.next(m.ref_phi_I);
      stream.next(m.ref_pitch);
      stream.next(m.ref_roll);
      stream.next(m.ref_yaw);
      stream.next(m.ref_psi);
      stream.next(m.vx_ref);
      stream.next(m.vy_ref);
      stream.next(m.theta_mod);
      stream.next(m.phi_mod);
      stream.next(m.k_v_x);
      stream.next(m.k_v_y);
      stream.next(m.k_mode);
      stream.next(m.ui_time);
      stream.next(m.ui_theta);
      stream.next(m.ui_phi);
      stream.next(m.ui_psi);
      stream.next(m.ui_psi_accuracy);
      stream.next(m.ui_seq);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct navdata_references_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ardrone_autonomy::navdata_references_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ardrone_autonomy::navdata_references_<ContainerAllocator>& v)
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
    s << indent << "ref_theta: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_theta);
    s << indent << "ref_phi: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_phi);
    s << indent << "ref_theta_I: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_theta_I);
    s << indent << "ref_phi_I: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_phi_I);
    s << indent << "ref_pitch: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_pitch);
    s << indent << "ref_roll: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_roll);
    s << indent << "ref_yaw: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_yaw);
    s << indent << "ref_psi: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ref_psi);
    s << indent << "vx_ref: ";
    Printer<float>::stream(s, indent + "  ", v.vx_ref);
    s << indent << "vy_ref: ";
    Printer<float>::stream(s, indent + "  ", v.vy_ref);
    s << indent << "theta_mod: ";
    Printer<float>::stream(s, indent + "  ", v.theta_mod);
    s << indent << "phi_mod: ";
    Printer<float>::stream(s, indent + "  ", v.phi_mod);
    s << indent << "k_v_x: ";
    Printer<float>::stream(s, indent + "  ", v.k_v_x);
    s << indent << "k_v_y: ";
    Printer<float>::stream(s, indent + "  ", v.k_v_y);
    s << indent << "k_mode: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.k_mode);
    s << indent << "ui_time: ";
    Printer<float>::stream(s, indent + "  ", v.ui_time);
    s << indent << "ui_theta: ";
    Printer<float>::stream(s, indent + "  ", v.ui_theta);
    s << indent << "ui_phi: ";
    Printer<float>::stream(s, indent + "  ", v.ui_phi);
    s << indent << "ui_psi: ";
    Printer<float>::stream(s, indent + "  ", v.ui_psi);
    s << indent << "ui_psi_accuracy: ";
    Printer<float>::stream(s, indent + "  ", v.ui_psi_accuracy);
    s << indent << "ui_seq: ";
    Printer<int32_t>::stream(s, indent + "  ", v.ui_seq);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ARDRONE_AUTONOMY_MESSAGE_NAVDATA_REFERENCES_H
