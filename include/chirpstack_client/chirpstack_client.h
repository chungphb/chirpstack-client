//
// Created by chungphb on 2/6/21.
//

#pragma once

#include <chirpstack_client/data_types.h>
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

namespace chirpstack_client {

using namespace grpc;
using namespace api;

struct chirpstack_client_config {
    const char* jwt_token;
};

struct chirpstack_client {
public:
    chirpstack_client(const std::string& server_address, chirpstack_client_config config);

    // Application Service
    create_application_response create_application(const create_application_request& request);

    // Device Service
    create_device_response create_device(const create_device_request& request);
    create_device_keys_response create_device_keys(const create_device_keys_request& request);

    // Device Profile Service
    create_device_profile_response create_device_profile(const create_device_profile_request& request);

    // Device Queue Service

    // Gateway Service
    create_gateway_response create_gateway(const create_gateway_request& request);

    // Gateway Profile Service

    // Internal Service

    // Multicast Group Service

    // Network Server Service

    // Organization Service

    // Service Profile Service
    get_service_profile_response get_service_profile(const get_service_profile_request& request);

    // User Service

private:
    chirpstack_client_config _config;
    std::shared_ptr<Channel> _channel;
    std::unique_ptr<ApplicationService::Stub> _application_service_stub;
    std::unique_ptr<DeviceService::Stub> _device_service_stub;
    std::unique_ptr<DeviceProfileService::Stub> _device_profile_service_stub;
    std::unique_ptr<DeviceQueueService::Stub> _device_queue_service_stub;
    std::unique_ptr<GatewayService::Stub> _gateway_service_stub;
    std::unique_ptr<GatewayProfileService::Stub> _gateway_profile_service_stub;
    std::unique_ptr<InternalService::Stub> _internal_service_stub;
    std::unique_ptr<MulticastGroupService::Stub> _multicast_group_service_stub;
    std::unique_ptr<NetworkServerService::Stub> _network_server_service_stub;
    std::unique_ptr<OrganizationService::Stub> _organization_service_stub;
    std::unique_ptr<ServiceProfileService::Stub> _service_profile_service_stub;
    std::unique_ptr<UserService::Stub> _user_service_stub;
};

}