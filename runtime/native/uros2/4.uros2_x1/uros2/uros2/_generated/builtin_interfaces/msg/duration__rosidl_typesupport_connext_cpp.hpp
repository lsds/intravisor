// generated from rosidl_typesupport_connext_cpp/resource/idl__rosidl_typesupport_connext_cpp.hpp.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice


#ifndef BUILTIN_INTERFACES__MSG__DURATION__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
#define BUILTIN_INTERFACES__MSG__DURATION__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "builtin_interfaces/msg/rosidl_typesupport_connext_cpp__visibility_control.h"
#include "builtin_interfaces/msg/detail/duration__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "builtin_interfaces/msg/dds_connext/Duration_Support.h"
#include "builtin_interfaces/msg/dds_connext/Duration_Plugin.h"
#include "ndds/ndds_cpp.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// forward declaration of internal CDR Stream
struct ConnextStaticCDRStream;

// forward declaration of DDS types
class DDSDomainParticipant;
class DDSDataWriter;
class DDSDataReader;


namespace builtin_interfaces
{

namespace msg
{
namespace typesupport_connext_cpp
{

DDS_TypeCode *
get_type_code__Duration();

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_builtin_interfaces
convert_ros_message_to_dds(
  const builtin_interfaces::msg::Duration & ros_message,
  builtin_interfaces::msg::dds_::Duration_ & dds_message);

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_builtin_interfaces
convert_dds_message_to_ros(
  const builtin_interfaces::msg::dds_::Duration_ & dds_message,
  builtin_interfaces::msg::Duration & ros_message);

bool
to_cdr_stream__Duration(
  const void * untyped_ros_message,
  ConnextStaticCDRStream * cdr_stream);

bool
to_message__Duration(
  const ConnextStaticCDRStream * cdr_stream,
  void * untyped_ros_message);

}  // namespace typesupport_connext_cpp

}  // namespace msg

}  // namespace builtin_interfaces


#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_builtin_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  builtin_interfaces, msg,
  Duration)();

#ifdef __cplusplus
}
#endif


#endif  // BUILTIN_INTERFACES__MSG__DURATION__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
