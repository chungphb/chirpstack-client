cmake_minimum_required(VERSION 3.19)
project(basic_grpc)

# Support C++ 14
set(CMAKE_CXX_STANDARD 14)

## Enable testing targets
option(ChirpStackClient_TESTING "Enable testing targets" ON)

# Find Threads package
find_package(Threads)

# Find Protobuf package
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

# Find protoc compiler
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC packet
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)

# Find grpc_cpp_plugin
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Generate Google API code
get_filename_component(google_proto_dir "/usr/local/include/" ABSOLUTE)
set(google_protos
        "google/protobuf/descriptor.proto"
        "google/api/http.proto"
        "google/api/annotations.proto")
set(google_proto_srcs "")
set(google_proto_hdrs "")
set(google_grpc_srcs "")
set(google_grpc_hdrs "")
foreach(google_proto ${google_protos})
    get_filename_component(current_proto "${google_proto_dir}/${google_proto}" ABSOLUTE)
    get_filename_component(current_proto_path "${current_proto}" PATH)
    string(REPLACE ".proto" "" current_file "${google_proto}")
    set(current_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.pb.cc")
    set(current_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.pb.h")
    set(current_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.grpc.pb.cc")
    set(current_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.grpc.pb.h")
    add_custom_command(
            OUTPUT "${current_proto_srcs}" "${current_proto_hdrs}" "${current_grpc_srcs}" "${current_grpc_hdrs}"
            COMMAND ${_PROTOBUF_PROTOC}
            ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
            --proto_path "${google_proto_dir}"
            -I "${current_proto_path}"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${current_proto}"
            DEPENDS "${current_proto}")
    list(APPEND google_proto_srcs ${current_proto_srcs})
    list(APPEND google_proto_hdrs ${current_proto_hdrs})
    list(APPEND google_grpc_srcs ${current_grpc_srcs})
    list(APPEND google_grpc_hdrs ${current_grpc_hdrs})
endforeach()

# Generate Chirpstack API
get_filename_component(chirpstack_proto_dir "modules/chirpstack-api/protobuf/" ABSOLUTE)
file(GLOB_RECURSE chirpstack_protos RELATIVE ${chirpstack_proto_dir} ${chirpstack_proto_dir}/*.proto)
set(chirpstack_proto_srcs "")
set(chirpstack_proto_hdrs "")
set(chirpstack_grpc_srcs "")
set(chirpstack_grpc_hdrs "")
foreach(chirpstack_proto ${chirpstack_protos})
    get_filename_component(current_proto "${chirpstack_proto_dir}/${chirpstack_proto}" ABSOLUTE)
    get_filename_component(current_proto_path "${current_proto}" PATH)
    string(REPLACE ".proto" "" current_file "${chirpstack_proto}")
    set(current_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.pb.cc")
    set(current_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.pb.h")
    set(current_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.grpc.pb.cc")
    set(current_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${current_file}.grpc.pb.h")
    add_custom_command(
            OUTPUT "${current_proto_srcs}" "${current_proto_hdrs}" "${current_grpc_srcs}" "${current_grpc_hdrs}"
            COMMAND ${_PROTOBUF_PROTOC}
            ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
            --proto_path "${chirpstack_proto_dir}"
            -I "${current_proto_path}" -I "${google_proto_dir}"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${current_proto}"
            DEPENDS "${current_proto}")
    list(APPEND chirpstack_proto_srcs ${current_proto_srcs})
    list(APPEND chirpstack_proto_hdrs ${current_proto_hdrs})
    list(APPEND chirpstack_grpc_srcs ${current_grpc_srcs})
    list(APPEND chirpstack_grpc_hdrs ${current_grpc_hdrs})
endforeach()

# Include binary directory
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Create chirpstack_grpc_proto target
add_library(chirpstack_grpc_proto
        ${chirpstack_proto_srcs}
        ${chirpstack_proto_hdrs}
        ${chirpstack_grpc_srcs}
        ${chirpstack_grpc_hdrs}
        ${google_proto_srcs}
        ${google_proto_hdrs}
        ${google_grpc_srcs}
        ${google_rpc_hdrs})
target_link_libraries(chirpstack_grpc_proto
        ${_PROTOBUF_LIBPROTOBUF}
        ${_REFLECTION}
        ${_GRPC_GRPCPP})

# Include chirpstack_client directory
include_directories("include")

# Create chirpstack_client target
set(chirpstack_client_srcs
        "src/chirpstack_client.cc")
set(chirpstack_client_hdrs
        "include/chirpstack_client/chirpstack_client.h"
        "include/chirpstack_client/messages.h")
add_library(chirpstack_client
        ${chirpstack_client_srcs}
        ${chirpstack_client_hdrs})
target_link_libraries(chirpstack_client
        chirpstack_grpc_proto
        ${_PROTOBUF_LIBPROTOBUF}
        ${_REFLECTION}
        ${_GRPC_GRPCPP})
target_include_directories(chirpstack_client
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (ChirpStackClient_TESTING)
    add_subdirectory(tests)
endif()