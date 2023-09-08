cmake_minimum_required(VERSION 3.10)

project(LocPass)

# LLVM LOC pass
# MODULE libraries are plugins that are not 
# linked into other targets but may be loaded 
# dynamically at runtime using dlopen-like 
# functionality 
add_library(LocPass
	MODULE Loc.cpp
)

# Use C++11 to compile our pass (i.e., supply -std=c++11).
#target_compile_features(LocPass
#	PRIVATE
#		cxx_std_11
#)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
#target_compile_options(LocPass
#	PRIVATE
#		-fno-rtti
#)


include_directories("${CHERI_SDK}/include/")

set_target_properties(LocPass PROPERTIES
    POSITION_INDEPENDENT_CODE true
    OUTPUT_NAME LocPass)

if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -lc++")
else ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti")
endif ()


target_compile_features(LocPass
	PRIVATE
		cxx_std_11
)


find_program(LLVM_CONFIG NAMES llvm-config DOC "Path to llvm-config utility")
if (${LLVM_CONFIG} STREQUAL "LLVM_CONFIG-NOTFOUND")
    message(SEND_ERROR "llvm-config not found, please manually set path with -DLLVM_CONFIG")
endif()
message(STATUS "Using llvm-config: ${LLVM_CONFIG}")

if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
# Define LLVM version macros so that we can support multiple versions in the source.
execute_process(COMMAND ${LLVM_CONFIG} --version
  OUTPUT_VARIABLE LLVM_VER
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --cxxflags
  OUTPUT_VARIABLE LLVM_CXXFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --libs ${LLVM_LIBS}
  OUTPUT_VARIABLE LLVM_LIBS_FLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --ldflags
  OUTPUT_VARIABLE LLVM_LDFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --system-libs
  OUTPUT_VARIABLE LLVM_SYSTEMLIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "([0-9]*).([0-9]*).*" "-DLLVM_MAJOR=\\1 -DLLVM_MINOR=\\2"  LLVM_VERSION "${LLVM_VER}")
string(REGEX REPLACE "-l/usr/lib/libexecinfo.so" "-lexecinfo" LLVM_SYSTEMLIBS "${LLVM_SYSTEMLIBS}")
# Ensure that all system-libs are prefixed by -l correctly
separate_arguments(LLVM_SYSTEMLIBS)
set(LLVM_SYSTEMLIBS_NORMALIZED "")
set(LLVM_EXTRA_LINK_DIRECTORIES)
foreach (lib ${LLVM_SYSTEMLIBS})
  # if the argument does not start with -l and is an absolute path we have to fix it
  if (NOT lib MATCHES "^-l" AND lib MATCHES "^/")
    # extract libXXX.so name
    string(REGEX MATCH "lib[a-zA-Z0-9]+.so" libname ${lib})
    # extract name without lib or .so
    string(REGEX REPLACE "lib([a-zA-Z09]+).so" "\\1" name ${libname})
    # extract base path
    string(REGEX REPLACE "/${libname}" "" libpath ${lib})
    list(APPEND LLVM_EXTRA_LINK_DIRECTORIES ${libpath})
    list(APPEND LLVM_SYSTEMLIBS_NORMALIZED "-l${name}")
  else ()
    list(APPEND LLVM_SYSTEMLIBS_NORMALIZED "${lib}")
  endif ()
endforeach ()
endif ()

#include_directories(SYSTEM)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXXFLAGS} ${LLVM_VERSION}")
#target_link_directories(LocPass PUBLIC
#  ${LLVM_EXTRA_LINK_DIRECTORIES})

target_link_libraries(LocPass
  ${LLVM_LDFLAGS}
  ${LLVM_LIBS_FLAGS}
  ${LLVM_SYSTEMLIBS_NORMALIZED})
#set(CMAKE_SKIP_RPATH true)


