//
// Created by chungphb on 2/6/21.
//

#pragma once

#include <chirpstack_client/messages.h>
#include <as/external/api/application.grpc.pb.h>
#include <as/external/api/device.grpc.pb.h>
#include <as/external/api/deviceProfile.grpc.pb.h>
#include <as/external/api/deviceQueue.grpc.pb.h>
#include <as/external/api/frameLog.grpc.pb.h>
#include <as/external/api/gateway.grpc.pb.h>
#include <as/external/api/gatewayProfile.grpc.pb.h>
#include <as/external/api/internal.grpc.pb.h>
#include <as/external/api/multicastGroup.grpc.pb.h>
#include <as/external/api/networkServer.grpc.pb.h>
#include <as/external/api/organization.grpc.pb.h>
#include <as/external/api/profiles.grpc.pb.h>
#include <as/external/api/serviceProfile.grpc.pb.h>
#include <as/external/api/user.grpc.pb.h>
#include <grpc++/grpc++.h>
#include <memory>

namespace chirpstack_cpp_client {

struct chirpstack_client_config {
    std::string jwt_token;
};

struct chirpstack_client {
public:
    chirpstack_client(const std::string& server_address, chirpstack_client_config config);

    // Application Service
    create_application_response create_application(const create_application_request& request);
    get_application_response get_application(const get_application_request& request);
    update_application_response update_application(const update_application_request& request);
    delete_application_response delete_application(const delete_application_request& request);
    list_application_response list_application(const list_application_request& request);

    // Device Service
    create_device_response create_device(const create_device_request& request);
    get_device_response get_device(const get_device_request& request);
    update_device_response update_device(const update_device_request& request);
    delete_device_response delete_device(const delete_device_request& request);
    list_device_response list_device(const list_device_request& request);
    create_device_keys_response create_device_keys(const create_device_keys_request& request);
    get_device_keys_response get_device_keys(const get_device_keys_request& request);
    update_device_keys_response update_device_keys(const update_device_keys_request& request);
    delete_device_keys_response delete_device_keys(const delete_device_keys_request& request);
    activate_device_response activate_device(const activate_device_request& request);
    deactivate_device_response deactivate_device(const deactivate_device_request& request);
    get_device_activation_response get_device_activation(const get_device_activation_request& request);
    get_random_dev_addr_response get_random_dev_addr(const get_random_dev_addr_request& request);

    // Device Profile Service
    create_device_profile_response create_device_profile(const create_device_profile_request& request);
    get_device_profile_response get_device_profile(const get_device_profile_request& request);
    update_device_profile_response update_device_profile(const update_device_profile_request& request);
    delete_device_profile_response delete_device_profile(const delete_device_profile_request& request);
    list_device_profile_response list_device_profile(const list_device_profile_request& request);

    // Device Queue Service
    enqueue_device_queue_item_response enqueue_device_queue_item(const enqueue_device_queue_item_request& request);
    flush_device_queue_response flush_device_queue(const flush_device_queue_request& request);
    list_device_queue_items_response list_device_queue_items(const list_device_queue_items_request& request);

    // Gateway Service
    create_gateway_response create_gateway(const create_gateway_request& request);
    get_gateway_response get_gateway(const get_gateway_request& request);
    update_gateway_response update_gateway(const update_gateway_request& request);
    delete_gateway_response delete_gateway(const delete_gateway_request& request);
    list_gateway_response list_gateway(const list_gateway_request& request);
    get_gateway_stats_response get_gateway_stats(const get_gateway_stats_request& request);
    get_last_ping_response get_last_ping(const get_last_ping_request& request);
    generate_gateway_client_certificate_response generate_gateway_client_certificate(const generate_gateway_client_certificate_request& request);

    // Gateway Profile Service
    create_gateway_profile_response create_gateway_profile(const create_gateway_profile_request& request);
    get_gateway_profile_response get_gateway_profile(const get_gateway_profile_request& request);
    update_gateway_profile_response update_gateway_profile(const update_gateway_profile_request& request);
    delete_gateway_profile_response delete_gateway_profile(const delete_gateway_profile_request& request);
    list_gateway_profiles_response list_gateway_profiles(const list_gateway_profiles_request& request);

    // Internal Service
    login_response login(const login_request& request);
    profile_response profile(const profile_request& request);
    global_search_response global_search(const global_search_request& request);
    create_api_key_response create_api_key(const create_api_key_request& request);
    delete_api_key_response delete_api_key(const delete_api_key_request& request);
    list_api_keys_response list_api_keys(const list_api_keys_request& request);
    settings_response settings(const settings_request& request);
    open_id_connect_login_response open_id_connect_login(const open_id_connect_login_request& request);
    get_devices_summary_response get_devices_summary(const get_devices_summary_request& request);
    get_gateways_summary_response get_gateways_summary(const get_gateways_summary_request& request);

    // Multicast Group Service
    create_multicast_group_response create_multicast_group(const create_multicast_group_request& request);
    get_multicast_group_response get_multicast_group(const get_multicast_group_request& request);
    update_multicast_group_response update_multicast_group(const update_multicast_group_request& request);
    delete_multicast_group_response delete_multicast_group(const delete_multicast_group_request& request);
    list_multicast_group_response list_multicast_group(const list_multicast_group_request& request);
    add_device_to_multicast_group_response add_device_to_multicast_group(const add_device_to_multicast_group_request& request);
    remove_device_from_multicast_group_response remove_device_from_multicast_group(const remove_device_from_multicast_group_request& request);
    enqueue_multicast_queue_item_response enqueue_multicast_queue_item(const enqueue_multicast_queue_item_request& request);
    flush_multicast_group_queue_items_response flush_multicast_group_queue_items(const flush_multicast_group_queue_items_request& request);
    list_multicast_group_queue_items_response list_multicast_group_queue_items(const list_multicast_group_queue_items_request& request);

    // Network Server Service
    create_network_server_response create_network_server(const create_network_server_request& request);
    get_network_server_response get_network_server(const get_network_server_request& request);
    update_network_server_response update_network_server(const update_network_server_request& request);
    delete_network_server_response delete_network_server(const delete_network_server_request& request);
    list_network_server_response list_network_server(const list_network_server_request& request);
    get_adr_algorithms_response get_adr_algorithms(const get_adr_algorithms_request& request);

    // Organization Service
    create_organization_response create_organization(const create_organization_request& request);
    get_organization_response get_organization(const get_organization_request& request);
    update_organization_response update_organization(const update_organization_request& request);
    delete_organization_response delete_organization(const delete_organization_request& request);
    list_organization_response list_organization(const list_organization_request& request);
    add_organization_user_response add_organization_user(const add_organization_user_request& request);
    get_organization_user_response get_organization_user(const get_organization_user_request& request);
    update_organization_user_response update_organization_user(const update_organization_user_request& request);
    delete_organization_user_response delete_organization_user(const delete_organization_user_request& request);
    list_organization_users_response list_organization_users(const list_organization_users_request& request);

    // Service Profile Service
    create_service_profile_response create_service_profile(const create_service_profile_request& request);
    get_service_profile_response get_service_profile(const get_service_profile_request& request);
    update_service_profile_response update_service_profile(const update_service_profile_request& request);
    delete_service_profile_response delete_service_profile(const delete_service_profile_request& request);
    list_service_profile_response list_service_profile(const list_service_profile_request& request);

    // User Service
    create_user_response create_user(const create_user_request& request);
    get_user_response get_user(const get_user_request& request);
    update_user_response update_user(const update_user_request& request);
    delete_user_response delete_user(const delete_user_request& request);
    list_user_response list_user(const list_user_request& request);
    update_user_password_response update_user_password(const update_user_password_request& request);

private:
    chirpstack_client_config _config;
    std::shared_ptr<grpc::Channel> _channel;
    std::unique_ptr<api::ApplicationService::Stub> _application_service_stub;
    std::unique_ptr<api::DeviceService::Stub> _device_service_stub;
    std::unique_ptr<api::DeviceProfileService::Stub> _device_profile_service_stub;
    std::unique_ptr<api::DeviceQueueService::Stub> _device_queue_service_stub;
    std::unique_ptr<api::GatewayService::Stub> _gateway_service_stub;
    std::unique_ptr<api::GatewayProfileService::Stub> _gateway_profile_service_stub;
    std::unique_ptr<api::InternalService::Stub> _internal_service_stub;
    std::unique_ptr<api::MulticastGroupService::Stub> _multicast_group_service_stub;
    std::unique_ptr<api::NetworkServerService::Stub> _network_server_service_stub;
    std::unique_ptr<api::OrganizationService::Stub> _organization_service_stub;
    std::unique_ptr<api::ServiceProfileService::Stub> _service_profile_service_stub;
    std::unique_ptr<api::UserService::Stub> _user_service_stub;
};

}