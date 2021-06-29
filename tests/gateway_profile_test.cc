#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    api::ServiceProfile service_profile;
    std::string gateway_profile_id;
    api::GatewayProfile gateway_profile;
};

void get_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_service_profile_request request;
    request.set_id(test_config().service_profile_id);

    // Send request
    auto response = client.get_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.service_profile = response.get().service_profile();
}

void test_create_gateway_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_gateway_profile_request request;
    request.mutable_gateway_profile()->set_name(test_config().gp_name);
    request.mutable_gateway_profile()->set_network_server_id(cache.service_profile.network_server_id());
    request.mutable_gateway_profile()->add_channels(0);
    request.mutable_gateway_profile()->add_channels(1);
    request.mutable_gateway_profile()->add_channels(2);
    auto extra_channel = request.mutable_gateway_profile()->add_extra_channels();
    extra_channel->set_modulation(common::Modulation::LORA);
    extra_channel->set_bandwidth(test_config().gp_bandwidth);
    extra_channel->set_frequency(test_config().gp_frequency);
    for (const auto& spreading_factor : test_config().gp_spreading_factors) {
        extra_channel->add_spreading_factors(spreading_factor);
    }

    // Send request
    auto response = client.create_gateway_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create gateway-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.gateway_profile_id = response.get().id();
}

void test_get_gateway_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_gateway_profile_request request;
    request.set_id(cache.gateway_profile_id);

    // Send request
    auto response = client.get_gateway_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get gateway-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.gateway_profile = response.get().gateway_profile();

    // Display response
    std::cout << "\tGateway-profile " << cache.gateway_profile.name() << std::endl;
    std::cout << "\t\tID: " << cache.gateway_profile.id() << std::endl;
    std::cout << "\t\tNetwork-server ID: " << cache.gateway_profile.network_server_id() << std::endl;
    std::cout << "\t\tChannels: {";
    const auto& channels = cache.gateway_profile.channels();
    for (auto it = channels.begin(); it != channels.end(); ) {
        std::cout << *it;
        ++it;
        std::cout << (it != channels.end() ? ", " : "}");
    }
    std::cout << std::endl;
    std::cout << "\t\tExtra channels: " << std::endl;
    for (const auto& extra_channel : cache.gateway_profile.extra_channels()) {
        std::cout << "\t\t\t";
        std::cout << "Bandwidth = " << extra_channel.bandwidth() << ", ";
        std::cout << "Frequency = " << extra_channel.frequency() << ", ";
        std::cout << "Spreading factors = {";
        const auto& spreading_factors = extra_channel.spreading_factors();
        for (auto it = spreading_factors.begin(); it != spreading_factors.end(); ) {
            std::cout << *it;
            ++it;
            std::cout << (it != spreading_factors.end() ? ", " : "}");
        }
        std::cout << std::endl;
    }
}

void test_update_gateway_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_gateway_profile_request request;
    *request.mutable_gateway_profile() = cache.gateway_profile;
    request.mutable_gateway_profile()->add_extra_channels();
    auto extra_channel = request.mutable_gateway_profile()->add_extra_channels();
    extra_channel->set_modulation(common::Modulation::LORA);
    extra_channel->set_bandwidth(test_config().gp_bandwidth);
    extra_channel->set_frequency(test_config().gp_frequency + 200000);
    for (const auto& spreading_factor : test_config().gp_spreading_factors) {
        extra_channel->add_spreading_factors(spreading_factor);
    }

    // Send request
    auto response = client.update_gateway_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update gateway-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_gateway_profiles(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_gateway_profiles_request request;
    request.set_limit(10);
    request.set_network_server_id(cache.service_profile.network_server_id());

    // Send request
    auto response = client.list_gateway_profiles(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list gateway-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& gateway_profile : response.get().result()) {
        std::cout << "\tGateway-profile " << gateway_profile.name() << std::endl;
        std::cout << "\t\tID: " << gateway_profile.id() << std::endl;
        std::cout << "\t\tNetwork-server ID: " << gateway_profile.network_server_id() << std::endl;
    }
}

void test_delete_gateway_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_gateway_profile_request request;
    request.set_id(cache.gateway_profile_id);

    // Send request
    auto response = client.delete_gateway_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete gateway-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void validate_config() {
    if (test_config().application_server.empty()) {
        throw std::runtime_error("Invalid application server");
    }
    if (test_config().global_jwt_token.empty()) {
        throw std::runtime_error("Invalid global JWT token");
    }
    if (test_config().service_profile_id.empty()) {
        throw std::runtime_error("Invalid service-profile ID");
    }
    if (test_config().gp_name.empty()) {
        throw std::runtime_error("Invalid gateway-profile name");
    }
    if (test_config().gp_bandwidth < 0) {
        throw std::runtime_error("Invalid gateway-profile bandwidth");
    }
    if (test_config().gp_frequency < 0) {
        throw std::runtime_error("Invalid gateway-profile frequency");
    }
    if (test_config().gp_spreading_factors.size() == 0) {
        throw std::runtime_error("Invalid gateway-profile spreading-factors");
    } else {
        for (const auto& spreading_factor : test_config().gp_spreading_factors) {
            if (spreading_factor < 0) {
                throw std::runtime_error("Invalid gateway-profile spreading-factor");
            }
        }
    }
}

int main(int argc, char** argv) {
    validate_config();

    chirpstack_client_config config{};
    config.jwt_token = test_config().global_jwt_token;
    config.log_enabled = test_config().client_log_enabled;
    chirpstack_client client{test_config().application_server, config};
    test_cache cache;

    std::cout << "GET SERVICE-PROFILE" << std::endl;
    get_service_profile(client, cache);

    std::cout << "TEST CREATE GATEWAY-PROFILE" << std::endl;
    test_create_gateway_profile(client, cache);

    std::cout << "TEST GET GATEWAY-PROFILE" << std::endl;
    test_get_gateway_profile(client, cache);

    std::cout << "TEST UPDATE GATEWAY-PROFILE" << std::endl;
    test_update_gateway_profile(client, cache);

    std::cout << "TEST LIST GATEWAY-PROFILE" << std::endl;
    test_list_gateway_profiles(client, cache);

    std::cout << "TEST DELETE GATEWAY-PROFILE" << std::endl;
    test_delete_gateway_profile(client, cache);

    return EXIT_SUCCESS;
}