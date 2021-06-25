//
// Created by chungphb on 2/6/21.
//

#include <chirpstack_client/chirpstack_client.h>

using namespace api;
using namespace grpc;

namespace chirpstack_cpp_client {

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

get_application_response chirpstack_client::get_application(const get_application_request& request) {
    get_application_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _application_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_application_response{status.error_code()};
    } else {
        return get_application_response{std::move(response)};
    }
}

update_application_response chirpstack_client::update_application(const update_application_request& request) {
    update_application_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _application_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_application_response{status.error_code()};
    } else {
        return update_application_response{std::move(response)};
    }
}

delete_application_response chirpstack_client::delete_application(const delete_application_request& request) {
    delete_application_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _application_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_application_response{status.error_code()};
    } else {
        return delete_application_response{std::move(response)};
    }
}

list_application_response chirpstack_client::list_application(const list_application_request& request) {
    list_application_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _application_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_application_response{status.error_code()};
    } else {
        return list_application_response{std::move(response)};
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

get_device_response chirpstack_client::get_device(const get_device_request& request) {
    get_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_device_response{status.error_code()};
    } else {
        return get_device_response{std::move(response)};
    }
}

update_device_response chirpstack_client::update_device(const update_device_request& request) {
    update_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_device_response{status.error_code()};
    } else {
        return update_device_response{std::move(response)};
    }
}

delete_device_response chirpstack_client::delete_device(const delete_device_request& request) {
    delete_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_device_response{status.error_code()};
    } else {
        return delete_device_response{std::move(response)};
    }
}

list_device_response chirpstack_client::list_device(const list_device_request& request) {
    list_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_device_response{status.error_code()};
    } else {
        return list_device_response{std::move(response)};
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

get_device_keys_response chirpstack_client::get_device_keys(const get_device_keys_request& request) {
    get_device_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->GetKeys(&context, request, &response);
    if (!status.ok()) {
        return get_device_keys_response{status.error_code()};
    } else {
        return get_device_keys_response{std::move(response)};
    }
}

update_device_keys_response chirpstack_client::update_device_keys(const update_device_keys_request& request) {
    update_device_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->UpdateKeys(&context, request, &response);
    if (!status.ok()) {
        return update_device_keys_response{status.error_code()};
    } else {
        return update_device_keys_response{std::move(response)};
    }
}

delete_device_keys_response chirpstack_client::delete_device_keys(const delete_device_keys_request& request) {
    delete_device_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->DeleteKeys(&context, request, &response);
    if (!status.ok()) {
        return delete_device_keys_response{status.error_code()};
    } else {
        return delete_device_keys_response{std::move(response)};
    }
}

activate_device_response chirpstack_client::activate_device(const activate_device_request& request) {
    activate_device_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Activate(&context, request, &response);
    if (!status.ok()) {
        return activate_device_response{status.error_code()};
    } else {
        return activate_device_response{std::move(response)};
    }
}

deactivate_device_response chirpstack_client::deactivate_device(const deactivate_device_request& request) {
    delete_device_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->Deactivate(&context, request, &response);
    if (!status.ok()) {
        return delete_device_keys_response{status.error_code()};
    } else {
        return delete_device_keys_response{std::move(response)};
    }
}

get_device_activation_response chirpstack_client::get_device_activation(const get_device_activation_request& request) {
    get_device_activation_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->GetActivation(&context, request, &response);
    if (!status.ok()) {
        return get_device_activation_response{status.error_code()};
    } else {
        return get_device_activation_response{std::move(response)};
    }
}

get_random_dev_addr_response chirpstack_client::get_random_dev_addr(const get_random_dev_addr_request& request) {
    get_random_dev_addr_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_service_stub->GetRandomDevAddr(&context, request, &response);
    if (!status.ok()) {
        return get_random_dev_addr_response{status.error_code()};
    } else {
        return get_random_dev_addr_response{std::move(response)};
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

get_device_profile_response chirpstack_client::get_device_profile(const get_device_profile_request& request) {
    get_device_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_profile_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_device_profile_response{status.error_code()};
    } else {
        return get_device_profile_response{std::move(response)};
    }
}

update_device_profile_response chirpstack_client::update_device_profile(const update_device_profile_request& request) {
    update_device_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_profile_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_device_profile_response{status.error_code()};
    } else {
        return update_device_profile_response{std::move(response)};
    }
}

delete_device_profile_response chirpstack_client::delete_device_profile(const delete_device_profile_request& request) {
    delete_device_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_profile_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_device_profile_response{status.error_code()};
    } else {
        return delete_device_profile_response{std::move(response)};
    }
}

list_device_profile_response chirpstack_client::list_device_profile(const list_device_profile_request& request) {
    list_device_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_profile_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_device_profile_response{status.error_code()};
    } else {
        return list_device_profile_response{std::move(response)};
    }
}

// Device Queue Service

enqueue_device_queue_item_response chirpstack_client::enqueue_device_queue_item(const enqueue_device_queue_item_request& request) {
    enqueue_device_queue_item_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_queue_service_stub->Enqueue(&context, request, &response);
    if (!status.ok()) {
        return enqueue_device_queue_item_response{status.error_code()};
    } else {
        return enqueue_device_queue_item_response{std::move(response)};
    }
}

flush_device_queue_response chirpstack_client::flush_device_queue(const flush_device_queue_request& request) {
    flush_device_queue_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_queue_service_stub->Flush(&context, request, &response);
    if (!status.ok()) {
        return flush_device_queue_response{status.error_code()};
    } else {
        return flush_device_queue_response{std::move(response)};
    }
}

list_device_queue_items_response chirpstack_client::list_device_queue_items(const list_device_queue_items_request& request) {
    list_device_queue_items_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _device_queue_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_device_queue_items_response{status.error_code()};
    } else {
        return list_device_queue_items_response{std::move(response)};
    }
}

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

get_gateway_response chirpstack_client::get_gateway(const get_gateway_request& request) {
    get_gateway_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_gateway_response{status.error_code()};
    } else {
        return get_gateway_response{std::move(response)};
    }
}

update_gateway_response chirpstack_client::update_gateway(const update_gateway_request& request) {
    create_gateway_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_gateway_response{status.error_code()};
    } else {
        return update_gateway_response{std::move(response)};
    }
}

delete_gateway_response chirpstack_client::delete_gateway(const delete_gateway_request& request) {
    delete_gateway_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_gateway_response{status.error_code()};
    } else {
        return delete_gateway_response{std::move(response)};
    }
}

list_gateway_response chirpstack_client::list_gateway(const list_gateway_request& request) {
    list_gateway_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_gateway_response{status.error_code()};
    } else {
        return list_gateway_response{std::move(response)};
    }
}

get_gateway_stats_response chirpstack_client::get_gateway_stats(const get_gateway_stats_request& request) {
    get_gateway_stats_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->GetStats(&context, request, &response);
    if (!status.ok()) {
        return get_gateway_stats_response{status.error_code()};
    } else {
        return get_gateway_stats_response{std::move(response)};
    }
}

get_last_ping_response chirpstack_client::get_last_ping(const get_last_ping_request& request) {
    get_last_ping_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->GetLastPing(&context, request, &response);
    if (!status.ok()) {
        return get_last_ping_response{status.error_code()};
    } else {
        return get_last_ping_response{std::move(response)};
    }
}

generate_gateway_client_certificate_response chirpstack_client::generate_gateway_client_certificate(const generate_gateway_client_certificate_request& request) {
    generate_gateway_client_certificate_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_service_stub->GenerateGatewayClientCertificate(&context, request, &response);
    if (!status.ok()) {
        return generate_gateway_client_certificate_response{status.error_code()};
    } else {
        return generate_gateway_client_certificate_response{std::move(response)};
    }
}

// Gateway Profile Service

create_gateway_profile_response chirpstack_client::create_gateway_profile(const create_gateway_profile_request& request) {
    create_gateway_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_profile_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_gateway_profile_response{status.error_code()};
    } else {
        return create_gateway_profile_response{std::move(response)};
    }
}

get_gateway_profile_response chirpstack_client::get_gateway_profile(const get_gateway_profile_request& request) {
    get_gateway_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_profile_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_gateway_profile_response{status.error_code()};
    } else {
        return get_gateway_profile_response{std::move(response)};
    }
}

update_gateway_profile_response chirpstack_client::update_gateway_profile(const update_gateway_profile_request& request) {
    update_gateway_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_profile_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_gateway_profile_response{status.error_code()};
    } else {
        return update_gateway_profile_response{std::move(response)};
    }
}

delete_gateway_profile_response chirpstack_client::delete_gateway_profile(const delete_gateway_profile_request& request) {
    delete_gateway_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_profile_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_gateway_profile_response{status.error_code()};
    } else {
        return delete_gateway_profile_response{std::move(response)};
    }
}

list_gateway_profiles_response chirpstack_client::list_gateway_profiles(const list_gateway_profiles_request& request) {
    list_gateway_profiles_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _gateway_profile_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_gateway_profiles_response{status.error_code()};
    } else {
        return list_gateway_profiles_response{std::move(response)};
    }
}

// Internal Service

login_response chirpstack_client::login(const login_request& request) {
    login_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->Login(&context, request, &response);
    if (!status.ok()) {
        return login_response{status.error_code()};
    } else {
        return login_response{std::move(response)};
    }
}

profile_response chirpstack_client::profile(const profile_request& request) {
    profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->Profile(&context, request, &response);
    if (!status.ok()) {
        return profile_response{status.error_code()};
    } else {
        return profile_response{std::move(response)};
    }
}

global_search_response chirpstack_client::global_search(const global_search_request& request) {
    global_search_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->GlobalSearch(&context, request, &response);
    if (!status.ok()) {
        return global_search_response{status.error_code()};
    } else {
        return global_search_response{std::move(response)};
    }
}

create_api_key_response chirpstack_client::create_api_key(const create_api_key_request& request) {
    create_api_key_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->CreateAPIKey(&context, request, &response);
    if (!status.ok()) {
        return create_api_key_response{status.error_code()};
    } else {
        return create_api_key_response{std::move(response)};
    }
}

delete_api_key_response chirpstack_client::delete_api_key(const delete_api_key_request& request) {
    delete_api_key_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->DeleteAPIKey(&context, request, &response);
    if (!status.ok()) {
        return delete_api_key_response{status.error_code()};
    } else {
        return delete_api_key_response{std::move(response)};
    }
}

list_api_keys_response chirpstack_client::list_api_keys(const list_api_keys_request& request) {
    list_api_keys_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->ListAPIKeys(&context, request, &response);
    if (!status.ok()) {
        return list_api_keys_response{status.error_code()};
    } else {
        return list_api_keys_response{std::move(response)};
    }
}

settings_response chirpstack_client::settings(const settings_request& request) {
    settings_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->Settings(&context, request, &response);
    if (!status.ok()) {
        return settings_response{status.error_code()};
    } else {
        return settings_response{std::move(response)};
    }
}

open_id_connect_login_response chirpstack_client::open_id_connect_login(const open_id_connect_login_request& request) {
    open_id_connect_login_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->OpenIDConnectLogin(&context, request, &response);
    if (!status.ok()) {
        return open_id_connect_login_response{status.error_code()};
    } else {
        return open_id_connect_login_response{std::move(response)};
    }
}

get_devices_summary_response chirpstack_client::get_devices_summary(const get_devices_summary_request& request) {
    get_devices_summary_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->GetDevicesSummary(&context, request, &response);
    if (!status.ok()) {
        return get_devices_summary_response{status.error_code()};
    } else {
        return get_devices_summary_response{std::move(response)};
    }
}

get_gateways_summary_response chirpstack_client::get_gateways_summary(const get_gateways_summary_request& request) {
    get_gateways_summary_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _internal_service_stub->GetGatewaysSummary(&context, request, &response);
    if (!status.ok()) {
        return get_gateways_summary_response{status.error_code()};
    } else {
        return get_gateways_summary_response{std::move(response)};
    }
}

// Multicast Group Service

create_multicast_group_response chirpstack_client::create_multicast_group(const create_multicast_group_request& request) {
    create_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_multicast_group_response{status.error_code()};
    } else {
        return create_multicast_group_response{std::move(response)};
    }
}

get_multicast_group_response chirpstack_client::get_multicast_group(const get_multicast_group_request& request) {
    get_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_multicast_group_response{status.error_code()};
    } else {
        return get_multicast_group_response{std::move(response)};
    }
}

update_multicast_group_response chirpstack_client::update_multicast_group(const update_multicast_group_request& request) {
    update_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_multicast_group_response{status.error_code()};
    } else {
        return update_multicast_group_response{std::move(response)};
    }
}

delete_multicast_group_response chirpstack_client::delete_multicast_group(const delete_multicast_group_request& request) {
    delete_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_multicast_group_response{status.error_code()};
    } else {
        return delete_multicast_group_response{std::move(response)};
    }
}

list_multicast_group_response chirpstack_client::list_multicast_group(const list_multicast_group_request& request) {
    list_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_multicast_group_response{status.error_code()};
    } else {
        return list_multicast_group_response{std::move(response)};
    }
}

add_device_to_multicast_group_response chirpstack_client::add_device_to_multicast_group(const add_device_to_multicast_group_request& request) {
    add_device_to_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->AddDevice(&context, request, &response);
    if (!status.ok()) {
        return add_device_to_multicast_group_response{status.error_code()};
    } else {
        return add_device_to_multicast_group_response{std::move(response)};
    }
}

remove_device_from_multicast_group_response chirpstack_client::remove_device_from_multicast_group(const remove_device_from_multicast_group_request& request) {
    remove_device_from_multicast_group_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->RemoveDevice(&context, request, &response);
    if (!status.ok()) {
        return remove_device_from_multicast_group_response{status.error_code()};
    } else {
        return remove_device_from_multicast_group_response{std::move(response)};
    }
}

enqueue_multicast_queue_item_response chirpstack_client::enqueue_multicast_queue_item(const enqueue_multicast_queue_item_request& request) {
    enqueue_multicast_queue_item_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->Enqueue(&context, request, &response);
    if (!status.ok()) {
        return enqueue_multicast_queue_item_response{status.error_code()};
    } else {
        return enqueue_multicast_queue_item_response{std::move(response)};
    }
}

flush_multicast_group_queue_items_response chirpstack_client::flush_multicast_group_queue_items(const flush_multicast_group_queue_items_request& request) {
    flush_multicast_group_queue_items_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->FlushQueue(&context, request, &response);
    if (!status.ok()) {
        return flush_multicast_group_queue_items_response{status.error_code()};
    } else {
        return flush_multicast_group_queue_items_response{std::move(response)};
    }
}

list_multicast_group_queue_items_response chirpstack_client::list_multicast_group_queue_items(const list_multicast_group_queue_items_request& request) {
    list_multicast_group_queue_items_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _multicast_group_service_stub->ListQueue(&context, request, &response);
    if (!status.ok()) {
        return list_multicast_group_queue_items_response{status.error_code()};
    } else {
        return list_multicast_group_queue_items_response{std::move(response)};
    }
}

// Network Server Service

create_network_server_response chirpstack_client::create_network_server(const create_network_server_request& request) {
    create_network_server_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_network_server_response{status.error_code()};
    } else {
        return create_network_server_response{std::move(response)};
    }
}

get_network_server_response chirpstack_client::get_network_server(const get_network_server_request& request) {
    get_network_server_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_network_server_response{status.error_code()};
    } else {
        return get_network_server_response{std::move(response)};
    }
}

update_network_server_response chirpstack_client::update_network_server(const update_network_server_request& request) {
    update_network_server_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_network_server_response{status.error_code()};
    } else {
        return update_network_server_response{std::move(response)};
    }
}

delete_network_server_response chirpstack_client::delete_network_server(const delete_network_server_request& request) {
    delete_network_server_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_network_server_response{status.error_code()};
    } else {
        return delete_network_server_response{std::move(response)};
    }
}

list_network_server_response chirpstack_client::list_network_server(const list_network_server_request& request) {
    list_network_server_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_network_server_response{status.error_code()};
    } else {
        return list_network_server_response{std::move(response)};
    }
}

get_adr_algorithms_response chirpstack_client::get_adr_algorithms(const get_adr_algorithms_request& request) {
    get_adr_algorithms_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _network_server_service_stub->GetADRAlgorithms(&context, request, &response);
    if (!status.ok()) {
        return get_adr_algorithms_response{status.error_code()};
    } else {
        return get_adr_algorithms_response{std::move(response)};
    }
}

// Organization Service

create_organization_response chirpstack_client::create_organization(const create_organization_request& request) {
    create_organization_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_organization_response{status.error_code()};
    } else {
        return create_organization_response{std::move(response)};
    }
}

get_organization_response chirpstack_client::get_organization(const get_organization_request& request) {
    get_organization_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_organization_response{status.error_code()};
    } else {
        return get_organization_response{std::move(response)};
    }
}

update_organization_response chirpstack_client::update_organization(const update_organization_request& request) {
    update_organization_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_organization_response{status.error_code()};
    } else {
        return update_organization_response{std::move(response)};
    }
}

delete_organization_response chirpstack_client::delete_organization(const delete_organization_request& request) {
    delete_organization_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_organization_response{status.error_code()};
    } else {
        return delete_organization_response{std::move(response)};
    }
}

list_organization_response chirpstack_client::list_organization(const list_organization_request& request) {
    list_organization_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_organization_response{status.error_code()};
    } else {
        return list_organization_response{std::move(response)};
    }
}

add_organization_user_response chirpstack_client::add_organization_user(const add_organization_user_request& request) {
    add_organization_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->AddUser(&context, request, &response);
    if (!status.ok()) {
        printf("%s\n", status.error_message().c_str());
        return add_organization_user_response{status.error_code()};
    } else {
        return add_organization_user_response{std::move(response)};
    }
}

get_organization_user_response chirpstack_client::get_organization_user(const get_organization_user_request& request) {
    get_organization_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->GetUser(&context, request, &response);
    if (!status.ok()) {
        return get_organization_user_response{status.error_code()};
    } else {
        return get_organization_user_response{std::move(response)};
    }
}

update_organization_user_response chirpstack_client::update_organization_user(const update_organization_user_request& request) {
    update_organization_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->UpdateUser(&context, request, &response);
    if (!status.ok()) {
        return update_organization_user_response{status.error_code()};
    } else {
        return update_organization_user_response{std::move(response)};
    }
}

delete_organization_user_response chirpstack_client::delete_organization_user(const delete_organization_user_request& request) {
    delete_organization_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->DeleteUser(&context, request, &response);
    if (!status.ok()) {
        return delete_organization_user_response{status.error_code()};
    } else {
        return delete_organization_user_response{std::move(response)};
    }
}

list_organization_users_response chirpstack_client::list_organization_users(const list_organization_users_request& request) {
    list_organization_users_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _organization_service_stub->ListUsers(&context, request, &response);
    if (!status.ok()) {
        return list_organization_users_response{status.error_code()};
    } else {
        return list_organization_users_response{std::move(response)};
    }
}

// Service Profile Service

create_service_profile_response chirpstack_client::create_service_profile(const create_service_profile_request& request) {
    create_service_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _service_profile_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_service_profile_response{status.error_code()};
    } else {
        return create_service_profile_response{std::move(response)};
    }
}

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

update_service_profile_response chirpstack_client::update_service_profile(const update_service_profile_request& request) {
    update_service_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _service_profile_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_service_profile_response{status.error_code()};
    } else {
        return update_service_profile_response{std::move(response)};
    }
}

delete_service_profile_response chirpstack_client::delete_service_profile(const delete_service_profile_request& request) {
    delete_service_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _service_profile_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_service_profile_response{status.error_code()};
    } else {
        return delete_service_profile_response{std::move(response)};
    }
}

list_service_profile_response chirpstack_client::list_service_profile(const list_service_profile_request& request) {
    list_service_profile_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _service_profile_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_service_profile_response{status.error_code()};
    } else {
        return list_service_profile_response{std::move(response)};
    }
}

// User Service

create_user_response chirpstack_client::create_user(const create_user_request& request) {
    create_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->Create(&context, request, &response);
    if (!status.ok()) {
        return create_user_response{status.error_code()};
    } else {
        return create_user_response{std::move(response)};
    }
}

get_user_response chirpstack_client::get_user(const get_user_request& request) {
    get_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->Get(&context, request, &response);
    if (!status.ok()) {
        return get_user_response{status.error_code()};
    } else {
        return get_user_response{std::move(response)};
    }
}

update_user_response chirpstack_client::update_user(const update_user_request& request) {
    update_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->Update(&context, request, &response);
    if (!status.ok()) {
        return update_user_response{status.error_code()};
    } else {
        return update_user_response{std::move(response)};
    }
}

delete_user_response chirpstack_client::delete_user(const delete_user_request& request) {
    delete_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->Delete(&context, request, &response);
    if (!status.ok()) {
        return delete_user_response{status.error_code()};
    } else {
        return delete_user_response{std::move(response)};
    }
}

list_user_response chirpstack_client::list_user(const list_user_request& request) {
    list_user_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->List(&context, request, &response);
    if (!status.ok()) {
        return list_user_response{status.error_code()};
    } else {
        return list_user_response{std::move(response)};
    }
}

update_user_password_response chirpstack_client::update_user_password(const update_user_password_request& request) {
    update_user_password_response::value_type response;
    ClientContext context;
    context.AddMetadata("authorization", _config.jwt_token);
    auto status = _user_service_stub->UpdatePassword(&context, request, &response);
    if (!status.ok()) {
        return update_user_password_response{status.error_code()};
    } else {
        return update_user_password_response{std::move(response)};
    }
}

}