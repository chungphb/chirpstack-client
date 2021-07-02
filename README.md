# ChirpStack Client

## Building

### How to build

As for many C++ projects, **ChirpStack Client** can be built using the CMake build system. The minimum required version of CMake is 3.15. To build **ChirpStack Client**, use the following commands:

```bash
$ mkdir bin
$ cd bin
$ cmake ..
$ cmake --build . -- -j 8
```

The shared libraries will be located at `bin/libchirpstack_client.so` and `bin/libchirpstack_grpc_proto.so`.

### Note

- **gRPC** should be installed in advance. See also: [grpc-cpp](https://github.com/chungphb/grpc-cpp).
- You might also need to copy the `grpc/third_party/googleapis/google/` and `grpc/third_party/protobuf/src/google/` directories to the `/usr/local/include/` directory beforehand.

## Testing

### How to build

To build **ChirpStack Client** with tests, use the following commands:

```bash
$ mkdir bin
$ cd bin
$ cmake -DChirpStackClient_TESTING=ON ..
$ cmake --build . -- -j 8
```

The test binary files will be located at `bin/tests/`.

### How to configure

Before testing, you have to modify the TOML configuration file located at `bin/tests/test_config.toml`. Since most of the fields already have a default value, you only need to fill in 3 fields:

- `test.jwt_token`
    - Using in the `application`, `device`, `device_profile`, `gateway`, `internal` and `multicast_group` tests.
    - Can be acquired in the `Token` field after creating a new API key using **ChirpStack Application Server** web-interface.
- `test.service_profile_id`
    - Using in the `application`, `device`, `device_profile`, `gateway`, `internal` and `multicast_group` tests.
    - Can be acquired in the URL after creating a new service-profile using **ChirpStack Application Server** web-interface.
- `test.global_jwt_token`
    - Using in the `gateway_profile`, `network_server`, `organization`, `service_profile` and `user` tests.
    - Can be acquired in the `Token` field after creating a new API key using **ChirpStack Application Server** web-interface.

### Detail

| Test                   | Tested functions                                             | Configuration parameters                                     |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `application_test`     | - `create_application`<br />- `get_application`<br />- `update_application`<br />- `delete_application`<br />- `list_application` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.application.name` |
| `device_test`          | - `create_device`<br />- `get_device`<br />- `update_device`<br />- `delete_device`<br />- `list_device`<br />- `create_device_keys`<br />- `get_device_keys`<br />- `update_device_keys`<br />- `delete_device_keys`<br />- `activate_device`<br />- `deactivate_device`<br />- `get_device_activation`<br />- `get_random_dev_addr`<br />- `enqueue_device_queue_item`<br />- `flush_device_queue`<br />- `list_device_queue_items` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.application.name`<br />- `test.device_profile.name`<br />- `test.device.eui`<br />- `test.device.nwk_key`<br />- `test.device.app_key`<br />- `test.device.address`<br />- `test.device.app_s_key`<br />- `test.device.nwk_s_enc_key`<br />- `test.device.s_nwk_int_key`<br />- `test.device.f_nwk_int_key`<br />- `test.device.f_port`<br />- `test.device.payload` |
| `device_profile_test`  | - `create_device_profile`<br />- `get_device_profile`<br />- `update_device_profile`<br />- `delete_device_profile`<br />- `list_device_profile` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.device_profile.name` |
| `gateway_test`         | - `create_gateway`<br />- `get_gateway`<br />- `update_gateway`<br />- `delete_gateway`<br />- `list_gateway`<br />- `get_gateway_stats`<br />- `get_last_ping`<br />- `generate_gateway_client_certificate` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.gateway.id` |
| `gateway_profile_test` | - `create_gateway_profile`<br />- `get_gateway_profile`<br />- `update_gateway_profile`<br />- `delete_gateway_profile`<br />- `list_gateway_profile` | - `general.application_server`<br />- `test.global_jwt_token`<br />- `test.service_profile_id`<br />- `test.gateway_profile.name`<br />- `test.gateway_profile.bandwidth`<br />- `test.gateway_profile.frequency`<br />- `test.gateway_profile.spreading_factors` |
| `internal_test`        | - `login`<br />- `profile`<br />- `global_search`<br />- `create_api_key`<br />- `delete_api_key`<br />- `list_api_keys`<br />- `settings`<br />- `open_id_connect_login`<br />- `get_devices_summary`<br />- `get_gateways_summary` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.internal.admin_username`<br />- `test.internal.admin_password`<br />- `test.internal.api_key_name` |
| `multicast_group_test` | - `create_multicast_group`<br />- `get_multicast_group`<br />- `update_multicast_group`<br />- `delete_multicast_group`<br />- `list_multicast_group`<br />- `add_device_to_multicast_group`<br />- `remove_device_from_multicast_group`<br />- `enqueue_multicast_queue_item`<br />- `flush_multicast_group_queue_items`<br />- `list_multicast_group_queue_items` | - `general.application_server`<br />- `test.jwt_token`<br />- `test.service_profile_id`<br />- `test.application.name`<br />- `test.device_profile.name`<br />- `test.device.eui`<br />- `test.device.address`<br />- `test.device.app_s_key`<br />- `test.device.nwk_s_enc_key`<br />- `test.device.s_nwk_int_key`<br />- `test.device.f_nwk_int_key`<br />- `test.device.f_port`<br />- `test.device.payload`<br />- `test.multicast_group.name`<br />- `test.multicast_group.address`<br />- `test.multicast_group.app_s_key`<br />- `test.multicast_group.nwk_s_key` |
| `network_server_test`  | - `create_network_server`<br />- `get_network_server`<br />- `update_network_server`<br />- `delete_network_server`<br />- `list_network_server`<br />- `get_adr_algorithms` | - `general.application_server`<br />- `test.global_jwt_token`<br />- `test.network_server.name`<br />- `test.network_server.server` |
| `organization_test`    | - `create_organization`<br />- `get_organization`<br />- `update_organization`<br />- `delete_organization`<br />- `list_organization`<br />- `add_organization_user`<br />- `get_organization_user`<br />- `update_organization_user`<br />- `delete_organization_user`<br />- `list_organization_users` | - `general.application_server`<br />- `test.global_jwt_token`<br />- `test.organization.name`<br />- `test.organization.display_name`<br />- `test.user.username`<br />- `test.user.password` |
| `service_profile_test` | - `create_server_profile`<br />- `get_server_profile`<br />- `update_server_profile`<br />- `delete_server_profile`<br />- `list_server_profile` | - `general.application_server`<br />- `test.global_jwt_token`<br />- `test.network_server.name`<br />- `test.network_server.server`<br />- `test.organization.name`<br />- `test.organization.display_name`<br />- `test.service_profile.name` |
| `user_test`            | - `create_user`<br />- `get_user`<br />- `update_user`<br />- `delete_user`<br />- `list_user`<br />- `update_user_password` | - `general.application_server`<br />- `test.global_jwt_token`<br />- `test.user.username`<br />- `test.user.password` |

### Note

- The `network-server` and `service-profile` tests require manually running a new instance of **ChirpStack Network Server** to reduce the effects on other existing instances. To do that, they will generate 2 bash files `start-sample-network-server.sh` and  `stop-sample-network-server.sh` to the `bin/tests/` directory. You should follow the instruction of the tests to be able to run them correctly.

## License

This project is licensed under the terms of the MIT license.
