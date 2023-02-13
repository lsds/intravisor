#include <rcl_logging_interface/rcl_logging_interface.h>
#include <rcutils/allocator.h>
#include <rcutils/logging.h>

#if 1

// Map rcutils severity to Android priority
int severity_to_priority(int severity)
{
	printf("%s : not implemented\n", __func__);
}

rcl_logging_ret_t rcl_logging_external_initialize(
  const char * config, rcutils_allocator_t allocator)
{
  (void)config;
  (void)allocator;
	printf("%s : not implemented\n", __func__);
  return RCL_LOGGING_RET_OK;
}

rcl_logging_ret_t rcl_logging_external_shutdown()
{
	printf("%s : not implemented\n", __func__);
  return RCL_LOGGING_RET_OK;
}

void rcl_logging_external_log(int severity, const char * name, const char * msg)
{
	printf("%s : not implemented\n", __func__);
}

rcl_logging_ret_t rcl_logging_external_set_logger_level(const char * name, int level)
{
  (void)name;
  (void)level;
	printf("%s : not implemented\n", __func__);
  return RCL_LOGGING_RET_OK;
}

#endif

#include "rosidl_typesupport_interface/macros.h"

#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/message_type_support_struct.h"

#include "rcl_interfaces/msg/detail/log__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "rosidl_runtime_c/string_functions.h"



ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces rcl_interfaces__msg__Log * rcl_interfaces__msg__Log__create() {
	printf("%s : not implemented\n", __func__);
}

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void
rcl_interfaces__msg__Log__destroy(rcl_interfaces__msg__Log * msg) {
	printf("%s : not implemented\n", __func__);
}


const rosidl_message_type_support_t * rosidl_typesupport_c__get_message_type_support_handle__rcl_interfaces__msg__Log() {
	printf("%s : not implemented\n", __func__);
}

#if 0
rosidl_typesupport_c__get_message_type_support_handle__std_msgs__msg__Header() {
	printf("%s : not implemented\n", __func__);
}

rosidl_typesupport_c__get_message_type_support_handle__std_msgs__msg__String() {
	printf("%s : not implemented\n", __func__);
}
#endif
const char * rosidl_typesupport_introspection_c__identifier="123";