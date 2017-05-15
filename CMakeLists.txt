# - Top level CMakeLists.txt for Bayeux/Protobuftools C++ library

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(bxprotobuftools LANGUAGES CXX)

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

# - Load Custom Modules
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

# - Versioning
set(BxProtobuftools_VERSION_MAJOR 0)
set(BxProtobuftools_VERSION_MINOR 2)
set(BxProtobuftools_VERSION_PATCH 0)
set(BxProtobuftools_VERSION
  "${BxProtobuftools_VERSION_MAJOR}.${BxProtobuftools_VERSION_MINOR}.${BxProtobuftools_VERSION_PATCH}")

#-----------------------------------------------------------------------
# - Standard UNIX Tool install paths, including relative paths for use
# by applications requiring resources
include(GNUInstallDirs)

# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR      ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BxProtobuftools_TAG "BxProtobuftools-${BxProtobuftools_VERSION}")
file(RELATIVE_PATH BXPROTOBUFTOOLS_BINDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_BINDIR}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BxProtobuftools_TAG}"
  )
file(RELATIVE_PATH BXPROTOBUFTOOLS_CMAKEDIR_TO_INCLUDEDIR
  "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BxProtobuftools_TAG}"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
  )
file(RELATIVE_PATH BXPROTOBUFTOOLS_CMAKEDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BxProtobuftools_TAG}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BxProtobuftools_TAG}"
  )
message(STATUS "[info] BXPROTOBUFTOOLS_BINDIR_TO_RESOURCEDIR   = '${BXPROTOBUFTOOLS_BINDIR_TO_RESOURCEDIR}'")
message(STATUS "[info] BXPROTOBUFTOOLS_CMAKEDIR_TO_INCLUDEDIR  = '${BXPROTOBUFTOOLS_CMAKEDIR_TO_INCLUDEDIR}'")
message(STATUS "[info] BXPROTOBUFTOOLS_CMAKEDIR_TO_RESOURCEDIR = '${BXPROTOBUFTOOLS_CMAKEDIR_TO_RESOURCEDIR}'")

# - Publish headers
configure_file(source/protobuftools/version.h.in ${PROJECT_BINARY_DIR}/source/protobuftools/version.h @ONLY)
configure_file(source/protobuftools/config.h.in  ${PROJECT_BINARY_DIR}/source/protobuftools/config.h  @ONLY)

# - Automated generation of specialized template converters for a few basic C++ types:
#
#   make_base_numeric_converter(type1 GUARDTAG type1 TYPE1 Type fake_converter.h)
function(make_base_numeric_converter cpptype_ GUARDTAG_ pbtype_ PBTYPE_ Pbtype_ outfile_)
  set(_cpptype  ${cpptype_})
  set(_GUARDTAG ${GUARDTAG_})
  set(_pbtype   ${pbtype_})
  set(_PBTYPE   ${PBTYPE_})
  set(_Pbtype   ${Pbtype_})
  message( STATUS "[info] Generating converter header for C++ type ${cpptype_}...")
  configure_file(source/protobuftools/_base_numeric_converter.h.in
    ${PROJECT_BINARY_DIR}/source/protobuftools/${outfile_} @ONLY)
endfunction()
make_base_numeric_converter(bool     BOOL   bool   BOOL   Bool   bool_converter.h)
make_base_numeric_converter(int8_t   INT8   sint32 SINT32 Int32  int8_converter.h)
make_base_numeric_converter(uint8_t  UINT8  uint32 UINT32 UInt32 uint8_converter.h)
make_base_numeric_converter(int16_t  INT16  sint32 SINT32 Int32  int16_converter.h)
make_base_numeric_converter(uint16_t UINT16 uint32 UINT32 UInt32 uint16_converter.h)
make_base_numeric_converter(int32_t  INT32  sint32 SINT32 Int32  int32_converter.h)
make_base_numeric_converter(uint32_t UINT32 uint32 UINT32 UInt32 uint32_converter.h)
make_base_numeric_converter(int64_t  INT64  sint64 SINT64 Int64  int64_converter.h)
make_base_numeric_converter(uint64_t UINT64 uint64 UINT64 UInt64 uint64_converter.h)
make_base_numeric_converter(float    FLOAT  float  FLOAT  Float  float_converter.h)
make_base_numeric_converter(double   DOUBLE double DOUBLE Double double_converter.h)

set(BxProtobuftools_HEADERS
  ${PROJECT_BINARY_DIR}/source/protobuftools/version.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/config.h
  source/protobuftools/logger.h
  source/protobuftools/logger_macros.h
  source/protobuftools/exception.h
  source/protobuftools/core.h
  source/protobuftools/node.h
  source/protobuftools/node-inl.h
  source/protobuftools/i_protobufable.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/bool_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/int8_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/uint8_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/int16_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/uint16_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/int32_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/uint32_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/int64_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/uint64_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/float_converter.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/double_converter.h
  source/protobuftools/base_type_converters.h
  source/protobuftools/enum_converter.h
  source/protobuftools/std_string_converter.h
  source/protobuftools/std_vector_converter.h
  source/protobuftools/std_list_converter.h
  source/protobuftools/std_set_converter.h
  source/protobuftools/std_array_converter.h
  source/protobuftools/std_type_converters.h
  source/protobuftools/protobufable_converter.h
  source/protobuftools/io.h
  source/protobuftools/io-inl.h
  source/protobuftools/iofile.h
  source/protobuftools/iofile-inl.h
  source/protobuftools/protobuf_utils.h
  source/protobuftools/protobuf_factory.h
  source/protobuftools/protobuftools.h
  )

set(BxProtobuftools_SOURCES
  source/protobuftools/logger.cc
  source/protobuftools/i_protobufable.cc
  source/protobuftools/exception.cc
  source/protobuftools/node.cc
  source/protobuftools/protobuf_utils.cc
  source/protobuftools/protobuf_factory.cc
  )

set(BXPROTOBUFTOOLS_PROTOBUF_MIN_VERSION 3.0)
message( STATUS "[info] Searching for Protobuf library version >= ${BXPROTOBUFTOOLS_PROTOBUF_MIN_VERSION}...")
set(Protobuf_FIND_COMPONENTS "JavaJar" "JavaUtilJar")
message( STATUS "[info]   with components = ${Protobuf_FIND_COMPONENTS}")
find_package(Protobuf ${BXPROTOBUFTOOLS_PROTOBUF_MIN_VERSION} REQUIRED COMPONENTS "${Protobuf_FIND_COMPONENTS}")
if (PROTOBUF_FOUND)
  message( STATUS "[info] Found the Protobuf library:")
  message( STATUS "[info]   PROTOBUF_FOUND             ='${PROTOBUF_FOUND}'")
  message( STATUS "[info]   PROTOBUF_ROOT              ='${PROTOBUF_ROOT}'")
  message( STATUS "[info]   PROTOBUF_VERSION_STRING    ='${PROTOBUF_VERSION_STRING}'")
  message( STATUS "[info]   PROTOBUF_INCLUDE_DIRS      ='${PROTOBUF_INCLUDE_DIRS}'")
  message( STATUS "[info]   PROTOBUF_LIBRARIES         ='${PROTOBUF_LIBRARIES}'")
  message( STATUS "[info]   PROTOBUF_PROTOC_LIBRARIES  ='${PROTOBUF_PROTOC_LIBRARIES}'")
  message( STATUS "[info]   PROTOBUF_LITE_LIBRARIES    ='${PROTOBUF_LITE_LIBRARIES}'")
  message( STATUS "[info]   PROTOBUF_LIBRARY           ='${PROTOBUF_LIBRARY}'")
  message( STATUS "[info]   PROTOBUF_PROTOC_LIBRARY    ='${PROTOBUF_PROTOC_LIBRARY}'")
  message( STATUS "[info]   PROTOBUF_INCLUDE_DIR       ='${PROTOBUF_INCLUDE_DIR}'")
  message( STATUS "[info]   PROTOBUF_PROTOC_EXECUTABLE ='${PROTOBUF_PROTOC_EXECUTABLE}'")
  message( STATUS "[info]   PROTOBUF_JAVA_JAR          ='${PROTOBUF_JAVA_JAR}'")
  message( STATUS "[info]   PROTOBUF_JAVA_UTIL_JAR     ='${PROTOBUF_JAVA_UTIL_JAR}'")
endif()

set(BxProtobuftools_OTHER_LIBS ${PROTOBUF_LIBRARIES})

set(BXPROTOBUFTOOLS_BOOST_MIN_VERSION 1.58.0)
set(BXPROTOBUFTOOLS_BOOST_COMPONENTS date_time)
message( STATUS "[info] Finding Boost version > ${BXPROTOBUFTOOLS_BOOST_MIN_VERSION} and components '${BXPROTOBUFTOOLS_BOOST_COMPONENTS}'")
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${BXPROTOBUFTOOLS_BOOST_MIN_VERSION}
  REQUIRED
  ${BXPROTOBUFTOOLS_BOOST_COMPONENTS}
  )
message( STATUS "[info] Boost_VERSION      = '${Boost_VERSION}'")
message( STATUS "[info] Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'")
message( STATUS "[info] Boost_LIBRARIES    = '${Boost_LIBRARIES}'")
message( STATUS "[info] Found Boost through 'MODULE' mode.")
message( STATUS "[info] Found Boost_LIB_VERSION  = '${Boost_LIB_VERSION}'")
message( STATUS "[info] Found Boost_MAJOR_VERSION    = '${Boost_MAJOR_VERSION}'")
message( STATUS "[info] Found Boost_MINOR_VERSION    = '${Boost_MINOR_VERSION}'")
message( STATUS "[info] Found Boost_SUBMINOR_VERSION = '${Boost_SUBMINOR_VERSION}'")
set(BxProtobuftools_BOOST_VERSION
  "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
get_filename_component(Boost_DIR ${Boost_INCLUDE_DIRS} DIRECTORY)
message( STATUS "[info] BxProtobuftools_BOOST_VERSION    = '${BxProtobuftools_BOOST_VERSION}'")
set(BxProtobuftools_BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${BxProtobuftools_BOOST_INCLUDE_DIRS})
message( STATUS "Boost_LIBRARIES='${Boost_LIBRARIES}'")
list(APPEND
  BxProtobuftools_HEADERS
  source/protobuftools/boost_datetime_converters.h
  source/protobuftools/boost_optional_converter.h
  source/protobuftools/boost_converters.h
  )
# set(BxProtobuftools_BOOST_LIBRARIES
#   # ${Boost_LIBRARIES}
#   # Boost::date_time
#   )
# message( STATUS "[info] BxProtobuftools_BOOST_LIBRARIES = '${BxProtobuftools_BOOST_LIBRARIES}'")
# list(APPEND BxProtobuftools_OTHER_LIBS ${BxProtobuftools_BOOST_LIBRARIES})
message( STATUS "[info] BxProtobuftools_OTHER_LIBS = '$BxProtobuftools_OTHER_LIBS}'")

# - Add specific protobuf support
add_subdirectory(source/proto)
get_directory_property(_BxProtobuftools_PROTOSTUB_HEADERS
  DIRECTORY source/proto
  DEFINITION BxProtobuftools_PROTOSTUB_HEADERS)
get_directory_property(_BxProtobuftools_PROTOSTUB_SOURCES
  DIRECTORY source/proto
  DEFINITION BxProtobuftools_PROTOSTUB_SOURCES)
message(STATUS "[debug] _BxProtobuftools_PROTOSTUB_HEADERS='${_BxProtobuftools_PROTOSTUB_HEADERS}'")
message(STATUS "[debug] _BxProtobuftools_PROTOSTUB_SOURCES='${_BxProtobuftools_PROTOSTUB_SOURCES}'")
message(STATUS "[debug] CMAKE_BINARY_DIR='${CMAKE_BINARY_DIR}'")
message(STATUS "[info] Listing protobuf stub files...")
set(BxProtobuftools_PROTOSTUB_HEADERS)
set(BxProtobuftools_PROTOSTUB_SOURCES)
foreach(_protofile ${_BxProtobuftools_PROTOSTUB_HEADERS})
  get_filename_component(_pb_dir ${_protofile} DIRECTORY)
  get_filename_component(_pb_basename ${_protofile} NAME_WE)
  set(_pb_stub_header ${CMAKE_BINARY_DIR}/source/proto/cpp_stubs/${_pb_dir}/${_pb_basename}.pb.h)
  set(_pb_stub_source ${CMAKE_BINARY_DIR}/source/proto/cpp_stubs/${_pb_dir}/${_pb_basename}.pb.cc)
  list(APPEND
    BxProtobuftools_PROTOSTUB_HEADERS
    ${_pb_stub_header}
    )
  list(APPEND
    BxProtobuftools_PROTOSTUB_SOURCES
    ${_pb_stub_source}
    )
endforeach()
list(APPEND
  BxProtobuftools_HEADERS
  source/protobuftools/protobuftools_stubs.h
  )

# - Utilities
configure_file(source/utilities/bxprotobuftools-query.in
  ${PROJECT_BINARY_DIR}/source/utilities/bxprotobuftools-query
  @ONLY)

set(BxProtobuftools_PRIVATE_HEADERS
  )

set(BXPROTOBUFTOOLS_DEFINITIONS
  -std=c++11
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS ${BXPROTOBUFTOOLS_DEFINITIONS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_BINARY_DIR}/source)
include_directories(${PROJECT_BINARY_DIR}/source/proto/cpp_stubs)
include_directories(${PROTOBUF_INCLUDE_DIRS})

foreach(_header ${BxProtobuftools_HEADERS})
  message(STATUS "[info] Header = '${_header}'")
endforeach()
foreach(_source ${BxProtobuftools_SOURCES})
  message(STATUS "[info] Source = '${_source}'")
endforeach()

add_library(Bayeux_protobuftools SHARED
  ${BxProtobuftools_HEADERS}
  ${BxProtobuftools_PRIVATE_HEADERS}
  ${BxProtobuftools_SOURCES}
  ${BxProtobuftools_PROTOSTUB_HEADERS}
  ${BxProtobuftools_PROTOSTUB_SOURCES}
  )

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

target_link_libraries(Bayeux_protobuftools ${BxProtobuftools_OTHER_LIBS})

# - Set RPATH as needed
set_target_properties(Bayeux_protobuftools PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

# - Use BinReloc
set_target_properties(Bayeux_protobuftools PROPERTIES COMPILE_DEFINITIONS ENABLE_BINRELOC)

install( FILES
  ${BxProtobuftools_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/protobuftools
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/source/protobuftools/version.h
  ${PROJECT_BINARY_DIR}/source/protobuftools/config.h
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/protobuftools
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/source/proto/protobuftools
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/proto
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  FILES_MATCHING PATTERN "*.proto"
  )

install( DIRECTORY
  ${CMAKE_BINARY_DIR}/source/proto/cpp_stubs/protobuftools
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bayeux/proto
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  FILES_MATCHING PATTERN "*.pb.h"
  )

install( FILES
  ${PROJECT_BINARY_DIR}/libBayeux_protobuftools${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_BINARY_DIR}/source/utilities/bxprotobuftools-query
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxProtobuftools_TAG}
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxProtobuftools_TAG}
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
)

option(PROTOBUFTOOLS_ENABLE_TESTING "Build unit testing system for Bayeux/protobuftools" ON)
if(PROTOBUFTOOLS_ENABLE_TESTING)
  enable_testing()
endif()

set(BxProtobuftools_TESTS
  source/protobuftools/testing/test_protobuf_factory.cxx
  )

if(PROTOBUFTOOLS_ENABLE_TESTING)

  message( STATUS "[info] Generating C++ testing source stub from protobuf files...")
  execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/source
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/source/proto
    --proto_path=${PROJECT_BINARY_DIR}/source/proto/cpp_stubs
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/protobuftools/testing/foo.proto
    RESULT_VARIABLE _gen_pb_error_code
    OUTPUT_VARIABLE _gen_pb_out
    ERROR_VARIABLE  _gen_pb_err
    )
  message( STATUS "[info] Protobuf generation error code ='${_gen_pb_code}'")
  message( STATUS "[info] Protobuf generation error msg  ='${_gen_pb_err}'")
  message( STATUS "[info] Protobuf generation error out  ='${_gen_pb_out}'")
  message( STATUS "[info] Done.")

  set(BxProtobuftools_TESTING_HEADERS
    source/protobuftools/testing/foo.h
    ${CMAKE_CURRENT_BINARY_DIR}/source/protobuftools/testing/foo.pb.h
    )

  set(BxProtobuftools_TESTING_PRIVATE_HEADERS
    )

  set(BxProtobuftools_TESTING_SOURCES
    source/protobuftools/testing/foo.cc
    ${CMAKE_CURRENT_BINARY_DIR}/source/protobuftools/testing/foo.pb.cc
    )

  include_directories("${CMAKE_CURRENT_BINARY_DIR}/source/")

  add_library(Bayeux_protobuftools_testing SHARED
    ${BxProtobuftools_TESTING_HEADERS}
    ${BxProtobuftools_TESTING_PRIVATE_HEADERS}
    ${BxProtobuftools_TESTING_SOURCES}
    )

  target_link_libraries(Bayeux_protobuftools_testing
    ${BxProtobuftools_OTHER_LIBS}
    ${PROTOBUF_LIBRARIES}
    )

  foreach(_testsource ${BxProtobuftools_TESTS})
    set(_bxprotobuftools_TEST_ENVIRONMENT
      # "BXPROTOBUFTOOLS_RESOURCE_FILES_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxprotobuftools-${_testname}")
    add_executable(${_testname} ${_testsource})
    target_link_libraries(${_testname}
      Bayeux_protobuftools_testing
      Bayeux_protobuftools
      ${BxProtobuftools_OTHER_LIBS})
    # - On Apple, ensure dynamic_lookup of undefined symbols
    if(APPLE)
      set_target_properties(${_testname} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_bxprotobuftools_TEST_ENVIRONMENT}
      )
    # - For now, dump them into the testing output directory
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxprotobuftools_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxprotobuftools_tests
      )
  endforeach()
endif()

#-----------------------------------------------------------------------
# Install targets and resources
#
install(TARGETS Bayeux_protobuftools
  EXPORT  BxProtobuftoolsTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

#-----------------------------------------------------------------------
# Configure/Install support files
# Done here so that external package variables are visible
#
# - Targets
export(TARGETS Bayeux_protobuftools
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}/BxProtobuftoolsTargets.cmake
  )
install(EXPORT BxProtobuftoolsTargets
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}
  )

# - Versioning (build and install trees)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxProtobuftoolsConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}/BxProtobuftoolsConfigVersion.cmake
  @ONLY
  )

# - Config (build and install trees *at present*)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxProtobuftoolsConfig.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}/BxProtobuftoolsConfig.cmake
  @ONLY
  )

install(FILES
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}/BxProtobuftoolsConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}/BxProtobuftoolsConfig.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxProtobuftools_TAG}
  )

install(FILES
  ${PROJECT_SOURCE_DIR}/cmake/FindProtobuf.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxProtobuftools_TAG}/cmake/Modules
  )

# - end of CMakeLists.txt
