#.rst:
# FindProtobuf
# ------------
#
# Locate and configure the Google Protocol Buffers includes, libraries, executable
# and library components.
#
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module will set the following variables in your project::
#
# ``PROTOBUF_FOUND``
#   Found the Google Protocol Buffers library
#   (libprotobuf & header files)
# ``PROTOBUF_INCLUDE_DIRS``
#   Include directories for Google Protocol Buffers
# ``PROTOBUF_LIBRARIES``
#   The protobuf libraries
# ``PROTOBUF_PROTOC_LIBRARIES``
#   The protoc libraries
# ``PROTOBUF_LITE_LIBRARIES``
#   The protobuf-lite libraries
# ``PROTOBUF_JAVA_JAR``
#   The protobuf jar file
# ``PROTOBUF_JAVA_UTIL_JAR``
#   The protobuf util jar file
# ``PROTOBUF_LITE_JAR``
#   The protobuf lite jar file
# ``PROTOBUF_VERSION_STRING``
#   The protobuf version string
# ``PROTOBUF_PROTOC_EXECUTABLE``
#   The protoc compiler
#
# Hints
# ^^^^^
#
# Set ``PROTOBUF_ROOT`` to a directory that contains a Protobuf installation.
#
#
#
# Cache Variables
# ^^^^^^^^^^^^^^^
#
# The following cache variables are also available to set or use:
#
# ``PROTOBUF_LIBRARY``
#   The protobuf library
# ``PROTOBUF_PROTOC_LIBRARY``
#   The protoc library
# ``PROTOBUF_LITE_LIBRARY``
#   The protobuf lite library
# ``PROTOBUF_INCLUDE_DIR``
#   The include directory for protocol buffers
#
# Accepts the following variables as input:
#
#   PROTOBUF_ROOT - (as a CMake or environment variable)
#        The root directory of the protobuf install prefix
#   Protobuf_FIND_COMPONENTS - list of components
#
# Possible Components:
#
# ``JavaJar``
# ``JavaUtilJar``
#

message( STATUS "=====================================")
message( STATUS "=                                   =")
message( STATUS "=    Entering FindProtobuf.cmake    =")
message( STATUS "=                                   =")
message( STATUS "=====================================")
if (NOT PROTOBUF_ROOT)
  if (PROTOBUF_INCLUDE_DIR)
     get_filename_component(PROTOBUF_ROOT "${PROTOBUF_INCLUDE_DIR}" PATH)
  endif()
endif()
# if (PROTOBUF_INCLUDE_DIR)
#   if (NOT PROTOBUF_ROOT)
#     get_filename_component(PROTOBUF_ROOT "${PROTOBUF_INCLUDE_DIR}" PATH)
#   endif()
#   get_filename_component(PROTOBUF_ROOT_HINT "${PROTOBUF_INCLUDE_DIR}" PATH)
# endif()

#message(STATUS "=== DEBUG: PROTOBUF_ROOT='${PROTOBUF_ROOT}'")
# Find the include directory
find_path(PROTOBUF_INCLUDE_DIR google/protobuf/message.h
  PATH_SUFFIXES include
  HINTS ${PROTOBUF_ROOT} #${PROTOBUF_ROOT_HINT}
  ENV PROTOBUF_ROOT
  DOC "The Google Protocol Buffers include directory"
  NO_DEFAULT_PATH
  )
#message(STATUS "=== DEBUG: PROTOBUF_INCLUDE_DIR='${PROTOBUF_INCLUDE_DIR}'")
if (PROTOBUF_INCLUDE_DIR STREQUAL "PROTOBUF_INCLUDE_DIR-NOTFOUND")
  message(FATAL "Could not find PROTOBUF_INCLUDE_DIR!")
else()
  mark_as_advanced(PROTOBUF_INCLUDE_DIR)
  set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIR})

  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(_PROTOBUF_ARCH_DIR 64/)
  endif()

  # Internal function: search for normal library
  function(_protobuf_find_libraries name filename)
    #message( STATUS "FindProtobuf: _protobuf_find_libraries: name='${name}' filename='${filename}'")
    find_library(${name}_LIBRARY
      NAMES ${filename}
      PATH_SUFFIXES lib lib${_PROTOBUF_ARCH_DIR}
      HINTS ${PROTOBUF_ROOT} ${PROTOBUF_ROOT_HINT}
      ENV PROTOBUF_ROOT
      NO_DEFAULT_PATH
      )
    set(${name}_LIBRARIES     ${${name}_LIBRARY} PARENT_SCOPE)
    #message( STATUS "FindProtobuf: _protobuf_find_libraries: name='${name}_LIBRARIES'")
  endfunction()

  # The Protobuf library
  _protobuf_find_libraries(PROTOBUF protobuf)
  mark_as_advanced(PROTOBUF_LIBRARY)

  # The Protobuf lite library
  _protobuf_find_libraries(PROTOBUF_LITE protobuf-lite)
  mark_as_advanced(PROTOBUF_LITE_LIBRARY)

  # The Protobuf protoc Library
  _protobuf_find_libraries(PROTOBUF_PROTOC protoc)
  mark_as_advanced(PROTOBUF_PROTOC_LIBRARY)

  # Find the protoc Executable
  find_program(PROTOBUF_PROTOC_EXECUTABLE
    NAMES protoc
    PATH_SUFFIXES bin
    HINTS ${PROTOBUF_ROOT} ${PROTOBUF_ROOT_HINT}
    ENV PROTOBUF_ROOT
    DOC "The Google Protocol Buffers Compiler"
    NO_DEFAULT_PATH
    )
  mark_as_advanced(PROTOBUF_PROTOC_EXECUTABLE)

  set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIR})

  execute_process(
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --version
    COMMAND sed -e "s/libprotoc //g"
    COMMAND tr -d "[[:space:]]"
    OUTPUT_VARIABLE _protobuf_version_string
    )
  # message( STATUS "_protobuf_version_string='${_protobuf_version_string}'")
  set(PROTOBUF_VERSION_STRING ${_protobuf_version_string})
  mark_as_advanced(PROTOBUF_VERSION_STRING)
  #message( STATUS "FindProtobuf: PROTOBUF_VERSION_STRING='${PROTOBUF_VERSION_STRING}'")
endif()

# message( STATUS "FindProtobuf: Protobuf components='${Protobuf_FIND_COMPONENTS}'")

if( Protobuf_FIND_COMPONENTS )
  set(PROTOBUF_HAVE_JAVA_JAR 0)
  set(PROTOBUF_HAVE_JAVA_UTIL_JAR 0)
  set(PROTOBUF_HAVE_LITE_JAR 0)
  foreach( component ${Protobuf_FIND_COMPONENTS} )
    message( STATUS "FindProtobuf: Searching Protobuf component='${component}'...")
    if (component STREQUAL "JavaJar")
      # Find the Java JAR file
      find_file(PROTOBUF_JAVA_JAR
	protobuf-java-${PROTOBUF_VERSION_STRING}.jar
	PATHS
	${PROTOBUF_ROOT}/lib/java
	${PROTOBUF_ROOT}/lib${_PROTOBUF_ARCH_DIR}/java
	DOC "The Google Protocol Buffers JAR file"
	NO_DEFAULT_PATH
	)
      if (PROTOBUF_JAVA_JAR)
	set(PROTOBUF_HAVE_JAVA_JAR 1)
      endif()
      mark_as_advanced(PROTOBUF_JAVA_JAR)
    elseif (component STREQUAL "JavaUtilJar")
      # Find the Java util JAR file
      find_file(PROTOBUF_JAVA_UTIL_JAR
	protobuf-java-util-${PROTOBUF_VERSION_STRING}.jar
	PATHS
	${PROTOBUF_ROOT}/lib/java
	${PROTOBUF_ROOT}/lib${_PROTOBUF_ARCH_DIR}/java
	DOC "The Google Protocol Buffers JAR util file"
	NO_DEFAULT_PATH
	)
      if (PROTOBUF_JAVA_UTIL_JAR)
	set(PROTOBUF_HAVE_JAVA_UTIL_JAR 1)
      endif()
      mark_as_advanced(PROTOBUF_JAVA_UTIL_JAR)
    # elseif (component STREQUAL "JavaLiteJar")
    #   # Find the Java lite JAR file
    #   find_file(PROTOBUF_JAVA_LITE_JAR
    # 	protobuf-lite-3.0.0-beta-3.jar
    # 	PATHS
    # 	${PROTOBUF_ROOT}/lib/java
    # 	${PROTOBUF_ROOT}/lib${_PROTOBUF_ARCH_DIR}/java
    # 	DOC "The Google Protocol Buffers JAR lite file"
    # 	NO_DEFAULT_PATH
    # 	)
    #   if (PROTOBUF_JAVA_LITE_JAR)
    # 	set(PROTOBUF_HAVE_JAVA_LITE_JAR 1)
    #   endif()
    #   mark_as_advanced(PROTOBUF_JAVA_LITE_JAR)
    else ()
      message(FATAL_ERROR "FindProtobuf: Unknown Protobuf Component: ${component}")
    endif()

  endforeach( component )
endif( Protobuf_FIND_COMPONENTS )

set(PROTOBUF_FOUND 1)

message( STATUS "Summary:")
message( STATUS "  PROTOBUF_FOUND              = '${PROTOBUF_FOUND}'")
message( STATUS "  PROTOBUF_INCLUDE_DIR        = '${PROTOBUF_INCLUDE_DIR}'")
message( STATUS "  PROTOBUF_INCLUDE_DIRS       = '${PROTOBUF_INCLUDE_DIRS}'")
message( STATUS "  PROTOBUF_LIBRARY            = '${PROTOBUF_LIBRARY}'")
message( STATUS "  PROTOBUF_PROTOC_LIBRARY     = '${PROTOBUF_PROTOC_LIBRARY}'")
message( STATUS "  PROTOBUF_LITE_LIBRARY       = '${PROTOBUF_LITE_LIBRARY}'")
message( STATUS "  PROTOBUF_PROTOC_EXECUTABLE  = '${PROTOBUF_PROTOC_EXECUTABLE}'")
message( STATUS "  PROTOBUF_ROOT               = '${PROTOBUF_ROOT}'")
message( STATUS "  PROTOBUF_VERSION_STRING     = '${PROTOBUF_VERSION_STRING}'")
message( STATUS "  PROTOBUF_JAVA_JAR           = '${PROTOBUF_JAVA_JAR}'")
message( STATUS "  PROTOBUF_HAVE_JAVA_UTIL_JAR = '${PROTOBUF_HAVE_JAVA_UTIL_JAR}'")

# Include these modules to handle the QUIETLY and REQUIRED arguments.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Protobuf
  FOUND_VAR PROTOBUF_FOUND
  REQUIRED_VARS
  PROTOBUF_INCLUDE_DIRS
  PROTOBUF_LIBRARIES
  PROTOBUF_PROTOC_LIBRARIES
  PROTOBUF_LITE_LIBRARIES
  PROTOBUF_PROTOC_EXECUTABLE
  VERSION_VAR PROTOBUF_VERSION_STRING)
set(PROTOBUF_FOUND 1)
mark_as_advanced(PROTOBUF_ROOT)
message( STATUS "=====================================")
message( STATUS "=                                   =")
message( STATUS "=    Exiting FindProtobuf.cmake     =")
message( STATUS "=                                   =")
message( STATUS "=====================================")

# - end
