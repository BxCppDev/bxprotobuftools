cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxprotobuftools_ex01 LANGUAGES CXX)

message( STATUS "=======================================")
message( STATUS "=                                     =")
message( STATUS "=     BxProtobuftools Example ex01    =")
message( STATUS "=                                     =")
message( STATUS "=======================================")

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

find_package(BxProtobuftools REQUIRED)
# include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${BxProtobuftools_INCLUDE_DIRS})
message(STATUS "BxProtobuftools_INCLUDE_DIRS='${BxProtobuftools_INCLUDE_DIRS}'")

message(STATUS "Generating C++ stub files...")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR='${CMAKE_CURRENT_SOURCE_DIR}'")
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
  message( STATUS "Protobuf stub generation for message '${_protofile}'")
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
  message( STATUS "Protobuf generation error code ='${_gen_pb_code}'")
  message( STATUS "Protobuf generation error msg  ='${_gen_pb_err}'")
  message( STATUS "Protobuf generation error out  ='${_gen_pb_out}'")
endforeach()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs)

add_executable(ex01
  ex01.cxx
  bar.h
  bar.cc
  foo.h
  foo.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs/BarMsg.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs/FooMsg.pb.cc
  )

target_link_libraries(ex01 Bayeux_protobuftools)
