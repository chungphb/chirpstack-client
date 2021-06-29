file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_config.toml DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

include_directories(../modules/tinytoml/include)
foreach(target_var
        application device device_profile gateway gateway_profile internal
        multicast_group network_server organization service_profile user)
    add_executable("${target_var}_test" "${target_var}_test.cc" test_config.h test_config.cc)
    target_link_libraries("${target_var}_test"
            chirpstack_client
            ${_PROTOBUF_LIBPROTOBUF}
            ${_REFLECTION}
            ${_GRPC_GRPCPP})
endforeach()