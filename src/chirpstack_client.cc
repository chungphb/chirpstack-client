//
// Created by chungphb on 2/6/21.
//

#include <chirpstack_client/chirpstack_client.h>

namespace chirpstack_client {

chirpstack_client::chirpstack_client(const std::string& server_address, chirpstack_client_config config) {
    _channel = CreateChannel(server_address, grpc::InsecureChannelCredentials());
    _config = config;
    _application_service_stub = ApplicationService::NewStub(_channel);
    _device_service_stub = DeviceService::NewStub(_channel);
    _device_profile_service_stub = DeviceProfileService::NewStub(_channel);
    _device_queue_service_stub = DeviceQueueService::NewStub(_channel);
    _gateway_service_stub = GatewayService::NewStub(_channel);
    _gateway_profile_service_stub = GatewayProfileService::NewStub(_channel);
    _internal_service_stub = InternalService::NewStub(_channel);
    _multicast_group_service_stub = MulticastGroupService::NewStub(_channel);
    _network_server_service_stub = NetworkServerService::NewStub(_channel);
    _organization_service_stub = OrganizationService::NewStub(_channel);
    _service_profile_service_stub = ServiceProfileService::NewStub(_channel);
    _user_service_stub = UserService::NewStub(_channel);
}

// Application Service

create_application_response chirpstack_client::create_application(const create_application_request& request) {
    create_application_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _application_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_application_response{status.error_code()};
    } else {
        return create_application_response{std::move(response)};
    }
}

// Device Service

create_device_response chirpstack_client::create_device(const create_device_request& request) {
    create_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_device_response{status.error_code()};
    } else {
        return create_device_response{std::move(response)};
    }
}

create_device_keys_response chirpstack_client::create_device_keys(const create_device_keys_request& request) {
    create_device_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->CreateKeys(&context, request, &response);
    if (!status.ok()) {
        return create_device_keys_response{status.error_code()};
    } else {
        return create_device_keys_response{std::move(response)};
    }
}

// Device Profile Service

create_device_profile_response chirpstack_client::create_device_profile(const create_device_profile_request& request) {
    create_device_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_profile_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_device_profile_response{status.error_code()};
    } else {
        return create_device_profile_response{std::move(response)};
    }
}

// Device Queue Service

// Gateway Service

create_gateway_response chirpstack_client::create_gateway(const create_gateway_request& request) {
    create_gateway_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_gateway_response{status.error_code()};
    } else {
        return create_gateway_response{std::move(response)};
    }
}

// Gateway Profile Service

// Internal Service

// Multicast Group Service

// Network Server Service

// Organization Service

// Service Profile Service

get_service_profile_response chirpstack_client::get_service_profile(const get_service_profile_request& request) {
    get_service_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _service_profile_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_service_profile_response{status.error_code()};
    } else {
        return get_service_profile_response{std::move(response)};
    }
}

// User Service

}