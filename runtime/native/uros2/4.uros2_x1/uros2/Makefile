#include ../../../../../config_arm_sim.mak
MAKEFILE := $(shell git rev-parse --show-toplevel)/config_arm.mak
include $(MAKEFILE)


CFLAGS=-fPIC -fPIE -pie -g -O2  -nostdinc -DCVM_MAX_SIZE=$(CONFIG_CVM_MAX_SIZE)\
	-I cheri-libc/include \
	$(TARGET_FLAGS_LINUX) $(SYSROOT_FLAGS_PURE) -B$(CROSS_COMPILE) $(ARCH_PURE) -Iarch/$(TARGET_ARCH)/include\
	-Iunikraft/vfscore/include -Iunikraft/devfs/include -I unikraft/ukswrand/include \
	-I musl-host/src/internal -I musl-host/src/include -I musl-host/include  -I musl-host/arch/morello -I musl-host/src/math \
	-I uros2/rcl/rcl/include -I uros2/rcutils/include -I uros2/rmw/rmw/include -I uros2/rosidl/rosidl_runtime_c/include -I uros2/rosidl/rosidl_typesupport_interface/include \
	-I uros2/rclc/rclc/include -I uros2/rcl/rcl_action/include/ -I uros2/micro_ros_intravisor/libmicroros/include  -I uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/\
	-I uros2/_generated/rosidl_typesupport_c \
	-I uros2/_generated -DROS_PACKAGE_NAME=\"demo\"

#CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I$(srcdir)/arch/$(ARCH) -I$(srcdir)/arch/generic -Iobj/src/internal -I$(srcdir)/src/include -I$(srcdir)/src/internal -Iobj/include -I$(srcdir)/include
#	-Wno-unused-command-line-argument -Werror=implicit-function-declaration -Werror=format -Werror=incompatible-pointer-types -Werror=cheri-capability-misuse -Werror=cheri-bitwise-operations -Werror=cheri-prototypes -Werror=pass-failed -Werror=undefined-internal -Wno-error=cheri-capability-misuse \

ifneq ($(MODE),sim)
endif

DEPS = 
OBJDIR = obj
SRC = main.c tramps.c hostcalls.c nolibc_printf2.c nolibc_float.c nolibc_printf.c nolibc_file.c  nolibc_strings.c nolibc_math.c nolibc_time.c nolibc_unsorted.c nolibc_regex.c dlmalloc_nonreuse.c cpio.c nolibc_network.c
SRC += $(wildcard musl-host/src/ctype/*.c)
SRC += $(wildcard musl-host/src/locale/*.c)
SRC += $(wildcard musl-host/src/termios/*.c)
SRC += $(wildcard musl-host/src/complex/*.c)
SRC += $(wildcard musl-host/src/fenv/*.c)
SRC += $(wildcard musl-host/src/math/*.c)
SRC += $(wildcard musl-host/src/string/*.c)
SRC += $(wildcard musl-host/src/stdlib/*.c)
SRC += $(wildcard musl-host/src/internal/*.c)
SRC += $(wildcard musl-host/src/stdio/*.c)
SRC += $(wildcard musl-host/src/multibyte/*.c)
SRC += $(wildcard musl-host/src/errno/*.c)
SRC += $(wildcard musl-host/src/time/*.c)
SRC += unikraft/vfscore/main.c unikraft/vfscore/fd.c unikraft/vfscore/rootfs.c unikraft/vfscore/task.c unikraft/vfscore/vnode.c  unikraft/vfscore/dentry.c unikraft/vfscore/file.c unikraft/vfscore/subr_uio.c unikraft/vfscore/fops.c unikraft/vfscore/lookup.c unikraft/vfscore/mount.c unikraft/vfscore/syscalls.c
SRC += unikraft/ramfs/ramfs_vnops.c unikraft/ramfs/ramfs_vfsops.c 
SRC += unikraft/devfs/devfs_vnops.c unikraft/devfs/device.c unikraft/devfs/null.c
SRC += unikraft/ukswrand/dev.c unikraft/ukswrand/swrand.c unikraft/ukswrand/mwc.c
# demo ping_pong
#SRC += uros2/micro-ROS-demos/rclc/ping_pong/main.c
SRC += uros2/micro-ROS-demos/rclc/timer/main.c
#SRC += uros2/micro-ROS-demos/rclc/string_publisher/main.c
#SRC += uros2/micro-ROS-demos/rclc/graph_introspection/graph_visualizer/main.c
#rcl
SRC += uros2/rcl/rcl/src/rcl/client.c
SRC += uros2/rcl/rcl/src/rcl/common.c
SRC += uros2/rcl/rcl/src/rcl/context.c
SRC += uros2/rcl/rcl/src/rcl/domain_id.c
SRC += uros2/rcl/rcl/src/rcl/event.c
SRC += uros2/rcl/rcl/src/rcl/expand_topic_name.c
SRC += uros2/rcl/rcl/src/rcl/graph.c
SRC += uros2/rcl/rcl/src/rcl/guard_condition.c
SRC += uros2/rcl/rcl/src/rcl/init.c
SRC += uros2/rcl/rcl/src/rcl/init_options.c
SRC += uros2/rcl/rcl/src/rcl/lexer.c
SRC += uros2/rcl/rcl/src/rcl/lexer_lookahead.c
SRC += uros2/rcl/rcl/src/rcl/localhost.c
SRC += uros2/rcl/rcl/src/rcl/network_flow_endpoints.c
SRC += uros2/rcl/rcl/src/rcl/node.c
SRC += uros2/rcl/rcl/src/rcl/node_options.c
SRC += uros2/rcl/rcl/src/rcl/publisher.c
SRC += uros2/rcl/rcl/src/rcl/remap.c
SRC += uros2/rcl/rcl/src/rcl/node_resolve_name.c
SRC += uros2/rcl/rcl/src/rcl/rmw_implementation_identifier_check.c
SRC += uros2/rcl/rcl/src/rcl/security.c
SRC += uros2/rcl/rcl/src/rcl/service.c
SRC += uros2/rcl/rcl/src/rcl/subscription.c
SRC += uros2/rcl/rcl/src/rcl/time.c
SRC += uros2/rcl/rcl/src/rcl/timer.c
SRC += uros2/rcl/rcl/src/rcl/validate_enclave_name.c
SRC += uros2/rcl/rcl/src/rcl/validate_topic_name.c
SRC += uros2/rcl/rcl/src/rcl/wait.c
## might be disabled
SRC += uros2/rcl/rcl/src/rcl/logging_rosout.c
SRC += uros2/rcl/rcl/src/rcl/logging.c
SRC += uros2/rcl/rcl/src/rcl/log_level.c
#rclc
SRC += uros2/rclc/rclc/src/rclc/init.c
SRC += uros2/rclc/rclc/src/rclc/publisher.c
SRC += uros2/rclc/rclc/src/rclc/subscription.c
SRC += uros2/rclc/rclc/src/rclc/client.c
SRC += uros2/rclc/rclc/src/rclc/service.c
SRC += uros2/rclc/rclc/src/rclc/timer.c
SRC += uros2/rclc/rclc/src/rclc/action_client.c
SRC += uros2/rclc/rclc/src/rclc/action_server.c
SRC += uros2/rclc/rclc/src/rclc/action_goal_handle.c
SRC += uros2/rclc/rclc/src/rclc/node.c
SRC += uros2/rclc/rclc/src/rclc/executor_handle.c
SRC += uros2/rclc/rclc/src/rclc/executor.c
SRC += uros2/rclc/rclc/src/rclc/sleep.c

#platform
SRC += uros2/micro_ros_intravisor/libmicroros/src/noop.c
#rcutils
SRC += uros2/rcutils/src/allocator.c
SRC += uros2/rcutils/src/array_list.c
SRC += uros2/rcutils/src/char_array.c
SRC += uros2/rcutils/src/cmdline_parser.c
SRC += uros2/rcutils/src/env.c
SRC += uros2/rcutils/src/error_handling.c
SRC += uros2/rcutils/src/filesystem.c
SRC += uros2/rcutils/src/find.c
SRC += uros2/rcutils/src/format_string.c
SRC += uros2/rcutils/src/hash_map.c
SRC += uros2/rcutils/src/logging.c
SRC += uros2/rcutils/src/process.c
SRC += uros2/rcutils/src/qsort.c
SRC += uros2/rcutils/src/repl_str.c
SRC += uros2/rcutils/src/shared_library.c
SRC += uros2/rcutils/src/snprintf.c
SRC += uros2/rcutils/src/split.c
SRC += uros2/rcutils/src/strcasecmp.c
SRC += uros2/rcutils/src/strdup.c
SRC += uros2/rcutils/src/strerror.c
SRC += uros2/rcutils/src/string_array.c
SRC += uros2/rcutils/src/string_map.c
SRC += uros2/rcutils/src/testing/fault_injection.c
SRC += uros2/rcutils/src/time.c
SRC += uros2/rcutils/src/time_unix.c
SRC += uros2/rcutils/src/uint8_array.c
SRC += uros2/rcutils/src/atomic_64bits.c
#rmw
SRC +=uros2/rmw/rmw/src/allocators.c
SRC +=uros2/rmw/rmw/src/convert_rcutils_ret_to_rmw_ret.c
SRC +=uros2/rmw/rmw/src/event.c
SRC +=uros2/rmw/rmw/src/init.c
SRC +=uros2/rmw/rmw/src/init_options.c
SRC +=uros2/rmw/rmw/src/message_sequence.c
SRC +=uros2/rmw/rmw/src/names_and_types.c
SRC +=uros2/rmw/rmw/src/network_flow_endpoint_array.c
SRC +=uros2/rmw/rmw/src/network_flow_endpoint.c
SRC +=uros2/rmw/rmw/src/publisher_options.c
SRC +=uros2/rmw/rmw/src/qos_string_conversions.c
SRC +=uros2/rmw/rmw/src/sanity_checks.c
SRC +=uros2/rmw/rmw/src/security_options.c
SRC +=uros2/rmw/rmw/src/subscription_content_filter_options.c
SRC +=uros2/rmw/rmw/src/subscription_options.c
SRC +=uros2/rmw/rmw/src/time.c
SRC +=uros2/rmw/rmw/src/topic_endpoint_info_array.c
SRC +=uros2/rmw/rmw/src/topic_endpoint_info.c
SRC +=uros2/rmw/rmw/src/types.c
SRC +=uros2/rmw/rmw/src/validate_full_topic_name.c
SRC +=uros2/rmw/rmw/src/validate_namespace.c
SRC +=uros2/rmw/rmw/src/validate_node_name.c
# rmw_microxrcedds_c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/identifiers.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/memory.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_client.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_compare_gids_equal.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_count.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_event.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_features.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_get_gid_for_publisher.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_get_implementation_identifier.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_get_serialization_format.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_get_topic_endpoint_info.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_get_endpoint_network_flow.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_qos_profile_check_compatible.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_guard_condition.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_init.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_logging.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microxrcedds_topic.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_node.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_node_info_and_types.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_node_names.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_publish.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_publisher.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_request.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_response.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_serialize.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_service.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_service_names_and_types.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_service_server_is_available.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_subscription.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_take.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_topic_names_and_types.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_trigger_guard_condition.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_wait.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_wait_set.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/types.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/utils.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/callbacks.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_event_callbacks.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_uxrce_transports.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/continous_serialization.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/init_options.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/time_sync.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/ping.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/timing.c
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/discovery.c
#SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/custom_transport.c <- should be enabled in a config
#SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c  $<$<BOOL:${RMW_UXRCE_GRAPH}>:src/rmw_graph.c>
SRC += uros2/rmw_microxrcedds/rmw_microxrcedds_c/src/rmw_microros/error_handling.c 
#rcl_action
SRC += uros2/rcl/rcl_action/src/rcl_action/action_client.c
SRC += uros2/rcl/rcl_action/src/rcl_action/action_server.c
SRC += uros2/rcl/rcl_action/src/rcl_action/goal_handle.c
SRC += uros2/rcl/rcl_action/src/rcl_action/goal_state_machine.c
SRC += uros2/rcl/rcl_action/src/rcl_action/graph.c
SRC += uros2/rcl/rcl_action/src/rcl_action/names.c
SRC += uros2/rcl/rcl_action/src/rcl_action/types.c
#uros2/rosidl/rosidl_runtime_c
SRC += uros2/rosidl/rosidl_runtime_c/src/message_type_support.c
SRC += uros2/rosidl/rosidl_runtime_c/src/primitives_sequence_functions.c
SRC += uros2/rosidl/rosidl_runtime_c/src/sequence_bound.c
SRC += uros2/rosidl/rosidl_runtime_c/src/service_type_support.c
SRC += uros2/rosidl/rosidl_runtime_c/src/string_functions.c
SRC += uros2/rosidl/rosidl_runtime_c/src/u16string_functions.c
#uros2/uros2/Micro-XRCE-DDS-Client
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/input_best_effort_stream.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/input_reliable_stream.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/output_best_effort_stream.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/output_reliable_stream.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/stream_storage.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/stream_id.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/stream/seq_num.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/session.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/session_info.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/submessage.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/object_id.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/serialization/xrce_types.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/serialization/xrce_header.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/serialization/xrce_subheader.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/util/time.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/util/ping.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/common_create_entities.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/create_entities_ref.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/create_entities_xml.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/create_entities_bin.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/read_access.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/core/session/write_access.c
#SRC += uros2/Micro-XRCE-DDS-Client    $<$<BOOL:${UCLIENT_PROFILE_MULTITHREAD}>:src/c/profile/multithread/multithread.c>
#SRC += uros2/Micro-XRCE-DDS-Client    $<$<BOOL:${UCLIENT_PROFILE_SHARED_MEMORY}>:src/c/profile/shared_memory/shared_memory.c>
#SRC += uros2/Micro-XRCE-DDS-Client    $<$<BOOL:${UCLIENT_PROFILE_MATCHING}>:src/c/profile/matching/matching.c>
#SRC += uros2/Micro-XRCE-DDS-Client    $<$<BOOL:${UCLIENT_PROFILE_STREAM_FRAMING}>:src/c/profile/transport/stream_framing/stream_framing_protocol.c>
#SRC += uros2/Micro-XRCE-DDS-Client    $<$<OR:$<BOOL:${UCLIENT_VERBOSE_MESSAGE}>,$<BOOL:${UCLIENT_VERBOSE_SERIALIZATION}>>:src/c/core/log/log.c>
##
#SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/udp/udp_transport.c
##SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/udp/udp_transport_posix.c
#SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/udp/udp_transport_posix_nopoll.c

SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/tcp/tcp_transport.c
SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/tcp/tcp_transport_posix.c
#SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/tcp/tcp_transport_posix_nopoll.c

SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/ip/ip_posix.c
#SRC += uros2/Micro-XRCE-DDS-Client/src/c/profile/transport/custom/custom_transport.c
#micro-CDR
SRC += uros2/Micro-CDR/src/c/common.c
SRC += uros2/Micro-CDR/src/c/types/basic.c
SRC += uros2/Micro-CDR/src/c/types/string.c
SRC += uros2/Micro-CDR/src/c/types/array.c
SRC += uros2/Micro-CDR/src/c/types/sequence.c
### messages? 
SRC += uros2/_generated/std_msgs/msg/detail/int64_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/multi_array_layout__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/float64_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/float32_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int32_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int32_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int8_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/byte__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int8__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/string__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/float64__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/bool__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/empty__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/float32__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int32__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/int16_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/multi_array_dimension__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/byte_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/int8_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int8_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int16__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int8_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/color_rgba__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/float64__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/string__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/float32__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/int16__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int16__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int64_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/byte__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int64_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int32__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int32_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/float64_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/float32_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int32__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/int64_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int64__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int16_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/multi_array_layout__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/int16_multi_array__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int16_multi_array__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/int64__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/empty__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/bool__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/u_int8__functions.c
SRC += uros2/_generated/std_msgs/msg/detail/multi_array_dimension__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/header__type_support.c
SRC += uros2/_generated/std_msgs/msg/detail/header__functions.c
SRC += uros2/_generated/builtin_interfaces/msg/detail/time__type_support.c
SRC += uros2/_generated/builtin_interfaces/msg/detail/time__functions.c
###
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/byte__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int16_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int16_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/color_rgba__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/multi_array_layout__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/bool__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int16__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int8__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int32_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/multi_array_dimension__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/header__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int32_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int32__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/float32_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int8__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int8_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int64__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/char__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/string__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/byte_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/empty__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int8_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int16__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/float64__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int32__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/int64_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int64__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/u_int64_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/float64_multi_array__type_support.cpp
#SRC += uros2/_generated/rosidl_typesupport_c/std_msgs/msg/float32__type_support.cpp


OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

default: libsco_uros2.so


$(OBJDIR)/%.o: %.c $(DEPS) 
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	@mkdir -p '$(@D)'
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -emit-llvm -S -c -o $(basename $@).ll $< $(CFLAGS)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) -c -o $(basename $@).o $(basename $@).ll $(CFLAGS)

LD_FLAGS = 
ifdef CONFIG_SIM
LD_FLAGS += -lgcc
else
LD_FLAGS += -Wl,-error-limit=0 libcompiler_rt.a
endif


$(OBJDIR)/tramps.o: arch/$(TARGET_ARCH)/tramps.S
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -c -o $(OBJDIR)/tramps.o arch/$(TARGET_ARCH)/tramps.S

libsco_uros2.so: $(OBJ)
	$(CC_CHERI_PURE) $(CC_CHERI_PURE_FLAGS) $(CFLAGS) -o $@ -nostdlib -Wl,-eouter_c -fPIE -fPIC $(OBJ) $(LD_FLAGS)

clean:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR)

mrproper:
	rm -rf ./*.o ./*.so ./*.ll ./1.txt $(OBJDIR) $(PASS_DIR1) $(PASS_DIR2)