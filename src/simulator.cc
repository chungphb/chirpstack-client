#include <grpc++/grpc++.h>
#include <as/as.grpc.pb.h>
#include <as/external/api/serviceProfile.grpc.pb.h>
#include <as/external/api/gateway.grpc.pb.h>
#include <as/external/api/deviceProfile.grpc.pb.h>
#include <as/external/api/application.grpc.pb.h>
#include <as/external/api/device.grpc.pb.h>
#include <iostream>

namespace simulator {

const char* SERVICE_PROFILE_ID = "76b0bff0-7f2c-46b1-abed-c594f68ec643";
const char* JWT_TOKEN = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiYmExOTUyNDctMGM4YS00ZDNkLThiODEtMjQwNj"
                        "ZlNDg3NzYzIiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYyMTUyODcxMiwic3ViIjoiYXBpX2tleSJ9.GokacHKp"
                        "2iMHge2U6Ml_17fwYBkuIvFH4R6UGLytvxA";

const char* GATEWAY_ID = "0205010001090906";
const char* DEVICE_PROFILE_NAME = "dddddddd-dddd-dddd-dddd-dddddddddddd";
const char* APPLICATION_NAME = "aaaaaaaa-aaaa-aaaa-aaaaaaaaaaaa";
const char* DEVICE_EUI = "0005010201090906";
const char* NWK_KEY = "00000000000000000000000000000000";
const char* APP_KEY = "00000000000000000000000000000000";

api::GetServiceProfileRequest GenerateGetServiceProfileRequest() {
    api::GetServiceProfileRequest request;
    // Set service-profile ID
    request.set_id(SERVICE_PROFILE_ID);
    // Return request
    return request;
}

api::CreateGatewayRequest GenerateCreateGatewayRequest(const api::ServiceProfile& service_profile) {
    api::CreateGatewayRequest request;
    // Set gateway object to create
    api::Gateway* gateway = request.mutable_gateway();
    // Set gateway's ID
    gateway->set_id(GATEWAY_ID);
    // Set gateway's name
    gateway->set_name(GATEWAY_ID);
    // Set gateway's description
    gateway->set_description(GATEWAY_ID);
    // Set gateway's location
    common::Location* location = gateway->mutable_location();
    location->set_latitude(0);
    location->set_longitude(0);
    location->set_altitude(0);
    location->set_source(common::LocationSource::UNKNOWN);
    location->set_accuracy(0);
    // Set ID of the organization to which the gateway belongs
    gateway->set_organization_id(service_profile.organization_id());
    // Set ID of the network-server on which the gateway is provisioned
    gateway->set_network_server_id(service_profile.network_server_id());
    // Set ID of the associated service-profile
    gateway->set_service_profile_id(service_profile.id());
    // Return request
    return request;
}

api::CreateDeviceProfileRequest GenerateCreateDeviceProfileRequest(const api::ServiceProfile& service_profile) {
    api::CreateDeviceProfileRequest request;
    // Set device-profile object to create
    api::DeviceProfile* device_profile = request.mutable_device_profile();
    // Set device-profile's name
    device_profile->set_name(DEVICE_PROFILE_NAME);
    // Set ID of the organization to which the device-profile is assigned
    device_profile->set_organization_id(service_profile.organization_id());
    // Set ID of the network-server on which the device-profile is provisioned
    device_profile->set_network_server_id(service_profile.network_server_id());
    // Set the version of the LoRaWAN supported by the End-Device
    device_profile->set_mac_version("1.0.3");
    // Set the revision of the Regional Parameters document supported by the End-Device
    device_profile->set_reg_params_revision("B");
    // Set whether End-Device supports Join (OTAA) or not (ABP)
    device_profile->set_supports_join(true);
    // Return request
    return request;
}

api::CreateApplicationRequest GenerateCreateApplicationRequest(const api::ServiceProfile& service_profile) {
    api::CreateApplicationRequest request;
    // Set application object to create
    api::Application* application = request.mutable_application();
    // Set application's name
    application->set_name(APPLICATION_NAME);
    // Set application's description
    application->set_description(APPLICATION_NAME);
    // Set ID of the organization to which the application belongs.
    application->set_organization_id(service_profile.organization_id());
    // Set ID of the associated service-profile
    application->set_service_profile_id(service_profile.id());
    // Return request
    return request;
}

api::CreateDeviceRequest GenerateCreateDeviceRequest(int64_t application_id, std::string device_profile_id) {
    api::CreateDeviceRequest request;
    // Set device object to create
    api::Device* device = request.mutable_device();
    // Set device's EUI
    device->set_dev_eui(DEVICE_EUI);
    // Set device's name
    device->set_name(DEVICE_EUI);
    // Set device's description
    device->set_description(DEVICE_EUI);
    // Set ID of the application to which the device must be added
    device->set_application_id(application_id);
    // Set DeviceProfileID attached to the device
    device->set_device_profile_id(device_profile_id);
    // Return request
    return request;
}

api::CreateDeviceKeysRequest GenerateCreateDeviceKeysRequest() {
    api::CreateDeviceKeysRequest request;
    // Set device-keys object to create
    api::DeviceKeys* device_keys = request.mutable_device_keys();
    // Set device's EUI
    device_keys->set_dev_eui(DEVICE_EUI);
    // Set network root key
    device_keys->set_nwk_key(NWK_KEY);
    // Return request
    return request;
}

}

int main(int argc, char** argv) {
    using namespace simulator;
    auto channel = grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials());
    grpc::Status status;

    api::ServiceProfile service_profile;
    { // Get service profile
        auto stub = api::ServiceProfileService::NewStub(channel);
        auto request = GenerateGetServiceProfileRequest();
        api::GetServiceProfileResponse response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->Get(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to get service profile: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        } else {
            service_profile = response.service_profile();
        }
    }

    { // Create gateway
        auto stub = api::GatewayService::NewStub(channel);
        auto request = GenerateCreateGatewayRequest(service_profile);
        google::protobuf::Empty response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->Create(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to create gateway: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        }
    }

    std::string device_profile_id;
    { // Create device profile
        auto stub = api::DeviceProfileService::NewStub(channel);
        auto request = GenerateCreateDeviceProfileRequest(service_profile);
        api::CreateDeviceProfileResponse response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->Create(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to create device profile: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        } else {
            device_profile_id = response.id();
        }
    }

    int64_t application_id = -1;
    { // Create application
        auto stub = api::ApplicationService::NewStub(channel);
        auto request = GenerateCreateApplicationRequest(service_profile);
        api::CreateApplicationResponse response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->Create(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to create application: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        } else {
            application_id = response.id();
        }
    }

    { // Create device
        auto stub = api::DeviceService::NewStub(channel);
        auto request = GenerateCreateDeviceRequest(application_id, device_profile_id);
        google::protobuf::Empty response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->Create(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to create device: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        }
    }

    { // Create device keys
        auto stub = api::DeviceService::NewStub(channel);
        auto request = GenerateCreateDeviceKeysRequest();
        google::protobuf::Empty response;
        grpc::ClientContext context;
        context.AddMetadata("authorization", JWT_TOKEN);
        status = stub->CreateKeys(&context, request, &response);
        if (!status.ok()) {
            std::cerr << "Failed to create device keys: ";
            std::cerr << status.error_code() << " (" << status.error_message() << ")" << std::endl;
        }
    }
}