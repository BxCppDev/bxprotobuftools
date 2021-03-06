
message( STATUS "[info] Generating protobuf stubs...")
set(BxProtobuftools_PROTOSTUB_HEADERS)
set(BxProtobuftools_PROTOSTUB_SOURCES)

set(protofiles
  )

list(APPEND protofiles
  protobuftools/SimpleOptional.proto
  protobuftools/TimePeriod.proto
  )

foreach(protofile ${protofiles})
  message( STATUS "[info] Protobuf stub generation for = '${protofile}'")
  get_filename_component(pb_dir ${protofile} DIRECTORY)
  get_filename_component(pb_basename ${protofile} NAME_WE)
  execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs)
  execute_process(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/cpp_stubs
    ${CMAKE_CURRENT_SOURCE_DIR}/${protofile}
    RESULT_VARIABLE _gen_pb_error_code
    OUTPUT_VARIABLE _gen_pb_out
    ERROR_VARIABLE  _gen_pb_err
    )
  message( STATUS "[info] Protobuf generation error code ='${_gen_pb_code}'")
  message( STATUS "[info] Protobuf generation error msg  ='${_gen_pb_err}'")
  message( STATUS "[info] Protobuf generation error out  ='${_gen_pb_out}'")
  message( STATUS "[info] Adding stub header ='${pb_dir}/${pb_basename}.pb.h'")
  message( STATUS "[info] Adding stub source ='${pb_dir}/${pb_basename}.pb.cc'")
  list(APPEND
    BxProtobuftools_PROTOSTUB_HEADERS
    ${pb_dir}/${pb_basename}.pb.h
    )
  list(APPEND
    BxProtobuftools_PROTOSTUB_SOURCES
    ${pb_dir}/${pb_basename}.pb.cc
    )
  message( STATUS "[info] Done.")
endforeach()