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

namespace chirpstack_client {

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

// Device Service
using create_device_request = CreateDeviceRequest;
using create_device_response = expected<google::protobuf::Empty>;
using create_device_keys_request = CreateDeviceKeysRequest;
using create_device_keys_response = expected<google::protobuf::Empty>;

// Device Profile Service
using create_device_profile_request = CreateDeviceProfileRequest;
using create_device_profile_response = expected<CreateDeviceProfileResponse>;

// Device Queue Service

// Gateway Service
using create_gateway_request = CreateGatewayRequest;
using create_gateway_response = expected<google::protobuf::Empty>;

// Gateway Profile Service

// Internal Service

// Multicast Group Service

// Network Server Service

// Organization Service

// Service Profile Service
using get_service_profile_request = GetServiceProfileRequest;
using get_service_profile_response = expected<GetServiceProfileResponse>;

// User Service

}
