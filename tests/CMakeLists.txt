foreach(target_var application device device_profile gateway gateway_profile network_server organization service_profile user simulator)
    add_executable("${target_var}_test" "${target_var}_test.cc" test_config.h)
    target_link_libraries("${target_var}_test"
            chirpstack_client
            ${_PROTOBUF_LIBPROTOBUF}
            ${_REFLECTION}
            ${_GRPC_GRPCPP})
endforeach()