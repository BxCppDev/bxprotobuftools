# - Top level CMakeLists.txt for Bayeux/Protobuftools C++ library

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
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
set(BxProtobuftools_VERSION_MINOR 1)
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
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BXPROTOBUFTOOLS_TAG "BxProtobuftools-${BxProtobuftools_VERSION}")
file(RELATIVE_PATH BXPROTOBUFTOOLS_BINDIR_TO_RESOURCEDIR "${CMAKE_INSTALL_FULL_BINDIR}" "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BXPROTOBUFTOOLS_TAG}")
file(RELATIVE_PATH BXPROTOBUFTOOLS_CMAKEDIR_TO_INCLUDEDIR "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}"  "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
# message( STATUS "BXPROTOBUFTOOLS_TAG='${BXPROTOBUFTOOLS_TAG}'")
# message( STATUS "CMAKE_INSTALL_INCLUDEDIR='${CMAKE_INSTALL_INCLUDEDIR}'")
# message( STATUS "CMAKE_INSTALL_BINDIR='${CMAKE_INSTALL_BINDIR}'")
# message( STATUS "CMAKE_INSTALL_LIBDIR='${CMAKE_INSTALL_LIBDIR}'")
# message( STATUS "CMAKE_INSTALL_CMAKEDIR='${CMAKE_INSTALL_CMAKEDIR}'")
# message( STATUS "CMAKE_INSTALL_DATAROOTDIR='${CMAKE_INSTALL_DATAROOTDIR}'")

set(BXPROTOBUFTOOLS_WITH_BOOST ON)
# option(BXPROTOBUFTOOLS_WITH_BOOST "Build Bayeux/protobuftools with Boost support" ON)
# mark_as_advanced(BXPROTOBUFTOOLS_WITH_BOOST)

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
  configure_file(source/protobuftools/_base_numeric_converter.h.in
    ${PROJECT_BINARY_DIR}/source/protobuftools/${outfile_} @ONLY)
endfunction()
make_base_numeric_converter(bool     BOOL   bool   BOOL   Bool   bool_converter.h)
make_base_numeric_converter(int8_t   INT8   int32  INT32  Int32  int8_converter.h)
make_base_numeric_converter(uint8_t  UINT8  uint32 UINT32 UInt32 uint8_converter.h)
make_base_numeric_converter(int16_t  INT16  int32  INT32  Int32  int16_converter.h)
make_base_numeric_converter(uint16_t UINT16 uint32 UINT32 UInt32 uint16_converter.h)
make_base_numeric_converter(int32_t  INT32  int32  INT32  Int32  int32_converter.h)
make_base_numeric_converter(uint32_t UINT32 uint32 UINT32 UInt32 uint32_converter.h)
make_base_numeric_converter(int64_t  INT64  int64  INT64  Int64  int64_converter.h)
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
  source/protobuftools/boost_datetime_converters.h
  source/protobuftools/boost_converters.h
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

find_package(Protobuf 3.0 REQUIRED)
if (PROTOBUF_FOUND)
  message( STATUS "Found the Protobuf library:")
  message( STATUS "  PROTOBUF_VERSION_STRING='${PROTOBUF_VERSION_STRING}'")
  message( STATUS "  PROTOBUF_INCLUDE_DIRS='${PROTOBUF_INCLUDE_DIRS}'")
  message( STATUS "  PROTOBUF_LIBRARIES='${PROTOBUF_LIBRARIES}'")
  message( STATUS "  PROTOBUF_PROTOC_LIBRARIES='${PROTOBUF_PROTOC_LIBRARIES}'")
  message( STATUS "  PROTOBUF_LITE_LIBRARIES='${PROTOBUF_LITE_LIBRARIES}'")
  message( STATUS "  PROTOBUF_LIBRARY='${PROTOBUF_LIBRARY}'")
  message( STATUS "  PROTOBUF_PROTOC_LIBRARY='${PROTOBUF_PROTOC_LIBRARY}'")
  message( STATUS "  PROTOBUF_INCLUDE_DIR='${PROTOBUF_INCLUDE_DIR}'")
  message( STATUS "  PROTOBUF_PROTOC_EXECUTABLE='${PROTOBUF_PROTOC_EXECUTABLE}'")
endif()

set(BxProtobuftools_OTHER_LIBS ${PROTOBUF_LIBRARIES})

#if(BXPROTOBUFTOOLS_WITH_BOOST)
  find_package(Boost 1.60.0
    REQUIRED
    date_time
    )
  message( STATUS "Boost found at '${Boost_INCLUDE_DIRS}'")
  message( STATUS "Boost version = '${Boost_VERSION}'")
  include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
  list(APPEND
    BxProtobuftools_HEADERS
    # source/protobuftools/boost_type_converters.h
    )
  message( STATUS "Boost_LIBRARIES='${Boost_LIBRARIES}'")
  list(APPEND BxProtobuftools_OTHER_LIBS
    ${Boost_DATE_TIME_LIBRARY}
    )
  message( STATUS "Boost_DIR='${Boost_DIR}'")
  message( STATUS "BxProtobuftools_OTHER_LIBS='${BxProtobuftools_OTHER_LIBS}'")
#endif()


# - Utilities
configure_file(source/utilities/bxprotobuftools-query.in ${PROJECT_BINARY_DIR}/source/utilities/bxprotobuftools-query  @ONLY)

set(BxProtobuftools_PRIVATE_HEADERS
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS -std=c++11)
endif()
# add_definitions(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_BINARY_DIR}/source)
include_directories(${PROTOBUF_INCLUDE_DIRS})

add_library(Bayeux_protobuftools SHARED
  ${BxProtobuftools_HEADERS}
  ${BxProtobuftools_PRIVATE_HEADERS}
  ${BxProtobuftools_SOURCES}
  )

target_link_libraries(Bayeux_protobuftools ${BxProtobuftools_OTHER_LIBS})

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
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXPROTOBUFTOOLS_TAG}
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BXPROTOBUFTOOLS_TAG}
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
  #source/protobuftools/testing/test_protobuftools_0.cxx
  )

if(PROTOBUFTOOLS_ENABLE_TESTING)

  message( STATUS "Generating C++ testing source stub from protobuf files...")
  execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/source
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/protobuftools/testing/foo.proto
    RESULT_VARIABLE _gen_pb_error_code
    OUTPUT_VARIABLE _gen_pb_out
    ERROR_VARIABLE  _gen_pb_err
    )
  message( STATUS "Protobuf generation error code ='${_gen_pb_code}'")
  message( STATUS "Protobuf generation error msg  ='${_gen_pb_err}'")
  message( STATUS "Protobuf generation error out  ='${_gen_pb_out}'")
  message( STATUS "Done.")

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
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}/BxProtobuftoolsTargets.cmake
  )
install(EXPORT BxProtobuftoolsTargets
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}
  )

# - Versioning (build and install trees)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxProtobuftoolsConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}/BxProtobuftoolsConfigVersion.cmake
  @ONLY
  )

# - Config (build and install trees *at present*)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxProtobuftoolsConfig.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}/BxProtobuftoolsConfig.cmake
  @ONLY
  )

install(FILES
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}/BxProtobuftoolsConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}/BxProtobuftoolsConfig.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BXPROTOBUFTOOLS_TAG}
  )

# - end of CMakeLists.txt
