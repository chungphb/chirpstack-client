//
// Created by chungphb on 2/6/21.
//

#pragma once

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
#include <grpc++/grpc++.h>

namespace chirpstack_cpp_client {

using namespace grpc;
using namespace api;

template <typename T>
struct expected {
public:
    using value_type = T;

    explicit expected(const T& rhs) : _value{rhs}, _error_code{StatusCode::OK} {}

    explicit expected(T&& rhs) : _value{std::move(rhs)}, _error_code{StatusCode::OK} {}

    explicit expected(StatusCode rhs) : _error_code{rhs} {}

    expected(const expected& rhs) {
        _value = rhs._value;
        _error_code = rhs._error_code;
    }

    expected(expected&& rhs) noexcept {
        _value = std::move(rhs._value);
        _error_code = rhs._error_code;
    }

    bool is_valid() {
        return _error_code == StatusCode::OK;
    }

    T& get() {
        if (!is_valid()) {
            throw std::runtime_error("Invalid access");
        }
        return _value;
    }

    const T& get() const {
        if (!is_valid()) {
            throw std::runtime_error("Invalid access");
        }
        return _value;
    }

    StatusCode error_code() const {
        return _error_code;
    }

private:
    expected() = default;

private:
    T _value;
    StatusCode _error_code;
};

// Application Service
using create_application_request = CreateApplicationRequest;
using create_application_response = expected<CreateApplicationResponse>;
using get_application_request = GetApplicationRequest;
using get_application_response = expected<GetApplicationResponse>;
using update_application_request = UpdateApplicationRequest;
using update_application_response = expected<google::protobuf::Empty>;
using delete_application_request = DeleteApplicationRequest;
using delete_application_response = expected<google::protobuf::Empty>;
using list_application_request = ListApplicationRequest;
using list_application_response = expected<ListApplicationResponse>;

// Device Service
using create_device_request = CreateDeviceRequest;
using create_device_response = expected<google::protobuf::Empty>;
using get_device_request = GetDeviceRequest;
using get_device_response = expected<GetDeviceResponse>;
using update_device_request = UpdateDeviceRequest;
using update_device_response = expected<google::protobuf::Empty>;
using delete_device_request = DeleteDeviceRequest;
using delete_device_response = expected<google::protobuf::Empty>;
using list_device_request = ListDeviceRequest;
using list_device_response = expected<ListDeviceResponse>;
using create_device_keys_request = CreateDeviceKeysRequest;
using create_device_keys_response = expected<google::protobuf::Empty>;
using get_device_keys_request = GetDeviceKeysRequest;
using get_device_keys_response = expected<GetDeviceKeysResponse>;
using update_device_keys_request = UpdateDeviceKeysRequest;
using update_device_keys_response = expected<google::protobuf::Empty>;
using delete_device_keys_request = DeleteDeviceKeysRequest;
using delete_device_keys_response = expected<google::protobuf::Empty>;
using activate_device_request = ActivateDeviceRequest;
using activate_device_response = expected<google::protobuf::Empty>;
using deactivate_device_request = DeactivateDeviceRequest;
using deactivate_device_response = expected<google::protobuf::Empty>;
using get_device_activation_request = GetDeviceActivationRequest;
using get_device_activation_response = expected<GetDeviceActivationResponse>;
using get_random_dev_addr_request = GetRandomDevAddrRequest;
using get_random_dev_addr_response = expected<GetRandomDevAddrResponse>;

// Device Profile Service
using create_device_profile_request = CreateDeviceProfileRequest;
using create_device_profile_response = expected<CreateDeviceProfileResponse>;
using get_device_profile_request = GetDeviceProfileRequest;
using get_device_profile_response = expected<GetDeviceProfileResponse>;
using update_device_profile_request = UpdateDeviceProfileRequest;
using update_device_profile_response = expected<google::protobuf::Empty>;
using delete_device_profile_request = DeleteDeviceProfileRequest;
using delete_device_profile_response = expected<google::protobuf::Empty>;
using list_device_profile_request = ListDeviceProfileRequest;
using list_device_profile_response = expected<ListDeviceProfileResponse>;

// Device Queue Service
using enqueue_device_queue_item_request = EnqueueDeviceQueueItemRequest;
using enqueue_device_queue_item_response = expected<EnqueueDeviceQueueItemResponse>;
using flush_device_queue_request = FlushDeviceQueueRequest;
using flush_device_queue_response = expected<google::protobuf::Empty>;
using list_device_queue_items_request = ListDeviceQueueItemsRequest;
using list_device_queue_items_response = expected<ListDeviceQueueItemsResponse>;

// Gateway Service
using create_gateway_request = CreateGatewayRequest;
using create_gateway_response = expected<google::protobuf::Empty>;
using get_gateway_request = GetGatewayRequest;
using get_gateway_response = expected<GetGatewayResponse>;
using update_gateway_request = UpdateGatewayRequest;
using update_gateway_response = expected<google::protobuf::Empty>;
using delete_gateway_request = DeleteGatewayRequest;
using delete_gateway_response = expected<google::protobuf::Empty>;
using list_gateway_request = ListGatewayRequest;
using list_gateway_response = expected<ListGatewayResponse>;
using get_gateway_stats_request = GetGatewayStatsRequest;
using get_gateway_stats_response = expected<GetGatewayStatsResponse>;
using get_last_ping_request = GetLastPingRequest;
using get_last_ping_response = expected<GetLastPingResponse>;
using generate_gateway_client_certificate_request = GenerateGatewayClientCertificateRequest;
using generate_gateway_client_certificate_response = expected<GenerateGatewayClientCertificateResponse>;

// Gateway Profile Service
using create_gateway_profile_request = CreateGatewayProfileRequest;
using create_gateway_profile_response = expected<CreateGatewayProfileResponse>;
using get_gateway_profile_request = GetGatewayProfileRequest;
using get_gateway_profile_response = expected<GetGatewayProfileResponse>;
using update_gateway_profile_request = UpdateGatewayProfileRequest;
using update_gateway_profile_response = expected<google::protobuf::Empty>;
using delete_gateway_profile_request = DeleteGatewayProfileRequest;
using delete_gateway_profile_response = expected<google::protobuf::Empty>;
using list_gateway_profiles_request = ListGatewayProfilesRequest;
using list_gateway_profiles_response = expected<ListGatewayProfilesResponse>;

// Internal Service
using login_request = LoginRequest;
using login_response = expected<LoginResponse>;
using profile_request = google::protobuf::Empty;
using profile_response = expected<ProfileResponse>;
using global_search_request = GlobalSearchRequest;
using global_search_response = expected<GlobalSearchResponse>;
using create_api_key_request = CreateAPIKeyRequest;
using create_api_key_response = expected<CreateAPIKeyResponse>;
using delete_api_key_request = DeleteAPIKeyRequest;
using delete_api_key_response = expected<google::protobuf::Empty>;
using list_api_keys_request = ListAPIKeysRequest;
using list_api_keys_response = expected<ListAPIKeysResponse>;
using settings_request = google::protobuf::Empty;
using settings_response = expected<SettingsResponse>;
using open_id_connect_login_request = OpenIDConnectLoginRequest;
using open_id_connect_login_response = expected<OpenIDConnectLoginResponse>;
using get_devices_summary_request = GetDevicesSummaryRequest;
using get_devices_summary_response = expected<GetDevicesSummaryResponse>;
using get_gateways_summary_request = GetGatewaysSummaryRequest;
using get_gateways_summary_response = expected<GetGatewaysSummaryResponse>;

// Multicast Group Service
using create_multicast_group_request = CreateMulticastGroupRequest;
using create_multicast_group_response = expected<CreateMulticastGroupResponse>;
using get_multicast_group_request = GetMulticastGroupRequest;
using get_multicast_group_response = expected<GetMulticastGroupResponse>;
using update_multicast_group_request = UpdateMulticastGroupRequest;
using update_multicast_group_response = expected<google::protobuf::Empty>;
using delete_multicast_group_request = DeleteMulticastGroupRequest;
using delete_multicast_group_response = expected<google::protobuf::Empty>;
using list_multicast_group_request = ListMulticastGroupRequest;
using list_multicast_group_response = expected<ListMulticastGroupResponse>;
using add_device_to_multicast_group_request = AddDeviceToMulticastGroupRequest;
using add_device_to_multicast_group_response = expected<google::protobuf::Empty>;
using remove_device_from_multicast_group_request = RemoveDeviceFromMulticastGroupRequest;
using remove_device_from_multicast_group_response = expected<google::protobuf::Empty>;
using enqueue_multicast_queue_item_request = EnqueueMulticastQueueItemRequest;
using enqueue_multicast_queue_item_response = expected<EnqueueMulticastQueueItemResponse>;
using flush_multicast_group_queue_items_request = FlushMulticastGroupQueueItemsRequest;
using flush_multicast_group_queue_items_response = expected<google::protobuf::Empty>;
using list_multicast_group_queue_items_request = ListMulticastGroupQueueItemsRequest;
using list_multicast_group_queue_items_response = expected<ListMulticastGroupQueueItemsResponse>;

// Network Server Service
using create_network_server_request = CreateNetworkServerRequest;
using create_network_server_response = expected<CreateNetworkServerResponse>;
using get_network_server_request = GetNetworkServerRequest;
using get_network_server_response = expected<GetNetworkServerResponse>;
using update_network_server_request = UpdateNetworkServerRequest;
using update_network_server_response = expected<google::protobuf::Empty>;
using delete_network_server_request = DeleteNetworkServerRequest;
using delete_network_server_response = expected<google::protobuf::Empty>;
using list_network_server_request = ListNetworkServerRequest;
using list_network_server_response = expected<ListNetworkServerResponse>;
using get_adr_algorithms_request = GetADRAlgorithmsRequest;
using get_adr_algorithms_response = expected<GetADRAlgorithmsResponse>;

// Organization Service
using create_organization_request = CreateOrganizationRequest;
using create_organization_response = expected<CreateOrganizationResponse>;
using get_organization_request = GetOrganizationRequest;
using get_organization_response = expected<GetOrganizationResponse>;
using update_organization_request = UpdateOrganizationRequest;
using update_organization_response = expected<google::protobuf::Empty>;
using delete_organization_request = DeleteOrganizationRequest;
using delete_organization_response = expected<google::protobuf::Empty>;
using list_organization_request = ListOrganizationRequest;
using list_organization_response = expected<ListOrganizationResponse>;
using add_organization_user_request = AddOrganizationUserRequest;
using add_organization_user_response = expected<google::protobuf::Empty>;
using get_organization_user_request = GetOrganizationUserRequest;
using get_organization_user_response = expected<GetOrganizationUserResponse>;
using update_organization_user_request = UpdateOrganizationUserRequest;
using update_organization_user_response = expected<google::protobuf::Empty>;
using delete_organization_user_request = DeleteOrganizationUserRequest;
using delete_organization_user_response = expected<google::protobuf::Empty>;
using list_organization_users_request = ListOrganizationUsersRequest;
using list_organization_users_response = expected<ListOrganizationUsersResponse>;

// Service Profile Service
using create_service_profile_request = CreateServiceProfileRequest;
using create_service_profile_response = expected<CreateServiceProfileResponse>;
using get_service_profile_request = GetServiceProfileRequest;
using get_service_profile_response = expected<GetServiceProfileResponse>;
using update_service_profile_request = UpdateServiceProfileRequest;
using update_service_profile_response = expected<google::protobuf::Empty>;
using delete_service_profile_request = DeleteServiceProfileRequest;
using delete_service_profile_response = expected<google::protobuf::Empty>;
using list_service_profile_request = ListServiceProfileRequest;
using list_service_profile_response = expected<ListServiceProfileResponse>;

// User Service
using create_user_request = CreateUserRequest;
using create_user_response = expected<CreateUserResponse>;
using get_user_request = GetUserRequest;
using get_user_response = expected<GetUserResponse>;
using update_user_request = UpdateUserRequest;
using update_user_response = expected<google::protobuf::Empty>;
using delete_user_request = DeleteUserRequest;
using delete_user_response = expected<google::protobuf::Empty>;
using list_user_request = ListUserRequest;
using list_user_response = expected<ListUserResponse>;
using update_user_password_request = UpdateUserPasswordRequest;
using update_user_password_response = expected<google::protobuf::Empty>;

}
