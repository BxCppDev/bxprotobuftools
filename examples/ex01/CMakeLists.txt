# - Top level CMakeLists.txt for bxprotobuftools_ex01 example program

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(bxprotobuftools_ex01 LANGUAGES CXX)

message( STATUS "[info] ${PROJECT_NAME}: Entering...")

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "${PROJECT_NAME} requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

include(GNUInstallDirs)
# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "[fatal] Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_PREFIX           = '${CMAKE_INSTALL_PREFIX}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_BINDIR           = '${CMAKE_INSTALL_BINDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_LIBDIR           = '${CMAKE_INSTALL_LIBDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_INCLUDEDIR       = '${CMAKE_INSTALL_INCLUDEDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_DATAROOTDIR      = '${CMAKE_INSTALL_DATAROOTDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_FULL_LIBDIR      = '${CMAKE_INSTALL_FULL_LIBDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_FULL_BINDIR      = '${CMAKE_INSTALL_FULL_BINDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_FULL_INCLUDEDIR  = '${CMAKE_INSTALL_FULL_INCLUDEDIR}'")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_INSTALL_FULL_DATAROOTDIR = '${CMAKE_INSTALL_FULL_DATAROOTDIR}'")

# -- RPATH settings --
# From: https://cmake.org/Wiki/CMake_RPATH_handling
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

# - Find BxJsontools
message(STATUS "[info] ${PROJECT_NAME}: Searching for BxProtobuftools version 0.1...")
find_package(BxProtobuftools REQUIRED)
message(STATUS "[info] ${PROJECT_NAME}: BxProtobuftools_VERSION      = '${BxProtobuftools_VERSION}'")
message(STATUS "[info] ${PROJECT_NAME}: BxProtobuftools_DEFINITIONS  = '${BxProtobuftools_DEFINITIONS}'")
message(STATUS "[info] ${PROJECT_NAME}: BxProtobuftools_INCLUDE_DIRS = '${BxProtobuftools_INCLUDE_DIRS}'")
message(STATUS "[info] ${PROJECT_NAME}: BxProtobuftools_LIBRARIES    = '${BxProtobuftools_LIBRARIES}'")

# - Find Boost:
message(STATUS "[info] Searching for Boost version ${BxProtobuftools_BOOST_VERSION} with 'MODULE' mode...")
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${BxProtobuftools_BOOST_VERSION} EXACT
  REQUIRED
  ${BxProtobuftools_BOOST_COMPONENTS}
  )
message(STATUS "[info] Boost_VERSION      = '${Boost_VERSION}'")
message(STATUS "[info] Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'")
message(STATUS "[info] Boost_LIBRARIES    = '${Boost_LIBRARIES}'")

add_definitions(${BxProtobuftools_DEFINITIONS})
include_directories(${PROJECT_SOURCE_DIR}
  ${BxProtobuftools_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

message(STATUS "[info] ${PROJECT_NAME}: Generating C++ stub files...")
message(STATUS "[info] ${PROJECT_NAME}: CMAKE_CURRENT_SOURCE_DIR='${CMAKE_CURRENT_SOURCE_DIR}'")
set(_protoc_IOPT)
foreach(_path ${BxProtobuftools_INCLUDE_DIRS})
  list(APPEND _protoc_IOPT "--proto_path=${_path}")
endforeach()

set(protofiles
  BarMsg.proto
  FooMsg.proto
  )

execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs)
foreach(_protofile ${protofiles})
  message( STATUS "[info] ${PROJECT_NAME}: Protobuf stub generation for message '${_protofile}'")
  get_filename_component(_pb_dir      ${_protofile} DIRECTORY)
  get_filename_component(_pb_basename ${_protofile} NAME_WE)
  execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ${_protoc_IOPT}
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs
    ${CMAKE_CURRENT_SOURCE_DIR}/${_pb_basename}.proto
    RESULT_VARIABLE _gen_pb_error_code
    OUTPUT_VARIABLE _gen_pb_out
    ERROR_VARIABLE  _gen_pb_err
    )
  message( STATUS "[info] ${PROJECT_NAME}: Protobuf generation error code ='${_gen_pb_code}'")
  message( STATUS "[info] ${PROJECT_NAME}: Protobuf generation error msg  ='${_gen_pb_err}'")
  message( STATUS "[info] ${PROJECT_NAME}: Protobuf generation error out  ='${_gen_pb_out}'")
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs)

# - Executable:
message(STATUS "[info] ${PROJECT_NAME}: Adding executable 'ex01'...")
add_executable(ex01
  ex01.cxx
  bar.h
  bar.cc
  foo.h
  foo.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs/BarMsg.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs/FooMsg.pb.cc
  )

target_link_libraries(ex01
  Bayeux_protobuftools
  ${Boost_LIBRARIES}
  )
install(TARGETS ex01
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  )

message( STATUS "[info] ${PROJECT_NAME}: Exiting.")

# end of CMakeLists.txt
