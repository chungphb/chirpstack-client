get_filename_component(google_proto_dir "/usr/local/include/google/api" ABSOLUTE)
get_filename_component(chirpstack_proto_dir "../modules/chirpstack-api/protobuf/" ABSOLUTE)
file(GLOB_RECURSE chirpstack_protos RELATIVE ${chirpstack_proto_dir} ${chirpstack_proto_dir}/*.proto)

set(chirpstack_proto_sources "")
set(chirpstack_proto_headers "")
set(chirpstack_grpc_sources "")
set(chirpstack_grpc_headers "")

foreach(chirpstack_proto ${chirpstack_protos})
    get_filename_component(current_proto "${chirpstack_proto_dir}/${chirpstack_proto}" ABSOLUTE)
    get_filename_component(current_proto_path "${current_proto}" PATH)

    string(REPLACE ".proto" "" current_target "${chirpstack_proto}")

    set(current_proto_sources "${CMAKE_CURRENT_BINARY_DIR}/${current_target}.pb.cc")
    set(current_proto_headers "${CMAKE_CURRENT_BINARY_DIR}/${current_target}.pb.h")
    set(current_grpc_sources "${CMAKE_CURRENT_BINARY_DIR}/${current_target}.grpc.pb.cc")
    set(current_grpc_headers "${CMAKE_CURRENT_BINARY_DIR}/${current_target}.grpc.pb.h")
    add_custom_command(
            OUTPUT "${current_proto_sources}" "${current_proto_headers}" "${current_grpc_sources}" "${current_grpc_headers}"
            COMMAND ${_PROTOBUF_PROTOC}
            ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
            --proto_path "${chirpstack_proto_dir}"
            -I "${current_proto_path}" -I "/usr/local/include"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${current_proto}" "${google_proto_dir}/annotations.proto" "${google_proto_dir}/http.proto"
            DEPENDS "${current_proto}")

    list(APPEND chirpstack_proto_sources ${current_proto_sources})
    list(APPEND chirpstack_proto_headers ${current_proto_headers})
    list(APPEND chirpstack_grpc_sources ${current_grpc_sources})
    list(APPEND chirpstack_grpc_headers ${current_grpc_headers})
endforeach()

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(chirpstack_grpc_proto
        ${chirpstack_proto_sources}
        ${chirpstack_proto_headers}
        ${chirpstack_grpc_sources}
        ${chirpstack_grpc_headers})
target_link_libraries(chirpstack_grpc_proto
        ${_PROTOBUF_LIBPROTOBUF}
        ${_REFLECTION}
        ${_GRPC_GRPCPP})

add_executable(chirpstack-client chirpstack-client.cc)
target_link_libraries(chirpstack-client
        chirpstack_grpc_proto
        ${_PROTOBUF_LIBPROTOBUF}
        ${_REFLECTION}
        ${_GRPC_GRPCPP})