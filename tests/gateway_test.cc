//
// Created by vht on 6/24/21.
//

#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    api::ServiceProfile service_profile;
    api::Gateway gateway;
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

void test_create_gateway(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_gateway_request request;
    request.mutable_gateway()->set_id(test_config().gtw_id);
    request.mutable_gateway()->set_name(test_config().gtw_id);
    request.mutable_gateway()->set_description(test_config().gtw_id);
    request.mutable_gateway()->mutable_location()->set_latitude(0);
    request.mutable_gateway()->mutable_location()->set_longitude(0);
    request.mutable_gateway()->mutable_location()->set_altitude(0);
    request.mutable_gateway()->mutable_location()->set_source(common::LocationSource::UNKNOWN);
    request.mutable_gateway()->mutable_location()->set_accuracy(0);
    request.mutable_gateway()->set_organization_id(cache.service_profile.organization_id());
    request.mutable_gateway()->set_network_server_id(cache.service_profile.network_server_id());
    request.mutable_gateway()->set_service_profile_id(cache.service_profile.id());

    // Send request
    auto response = client.create_gateway(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create gateway: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_get_gateway(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_gateway_request request;
    request.set_id(test_config().gtw_id);

    // Send request
    auto response = client.get_gateway(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get gateway: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.gateway = response.get().gateway();

    // Display response
    std::cout << "\tGateway " << cache.gateway.id() << std::endl;
    std::cout << "\t\tName: " << cache.gateway.name() << std::endl;
    std::cout << "\t\tDescription: " << cache.gateway.description() << std::endl;
    std::cout << "\t\tOrganization ID: " << cache.gateway.organization_id() << std::endl;
    std::cout << "\t\tNetwork-server ID: " << cache.gateway.network_server_id() << std::endl;
    std::cout << "\t\tLocation: (" << cache.gateway.location().latitude();
    std::cout << ", " << cache.gateway.location().longitude();
    std::cout << ", " << cache.gateway.location().altitude() << ")" << std::endl;
}

void test_update_gateway(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_gateway_request request;
    *request.mutable_gateway() = cache.gateway;
    auto description = test_config().gtw_id;
    description += "-" + std::to_string(cache.gateway.organization_id());
    description += "-" + std::to_string(cache.gateway.network_server_id());
    request.mutable_gateway()->set_description(description);

    // Send request
    auto response = client.update_gateway(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update gateway: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_gateway(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_gateway_request request;
    request.set_limit(10);
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.list_gateway(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list gateway: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& gateway : response.get().result()) {
        std::cout << "\tGateway " << gateway.id() << std::endl;
        std::cout << "\t\tName: " << gateway.name() << std::endl;
        std::cout << "\t\tDescription: " << gateway.description() << std::endl;
        std::cout << "\t\tOrganization ID: " << gateway.organization_id() << std::endl;
        std::cout << "\t\tNetwork-server ID: " << gateway.network_server_id() << std::endl;
        std::cout << "\t\tLocation: (" << gateway.location().latitude();
        std::cout << ", " << gateway.location().longitude();
        std::cout << ", " << gateway.location().altitude() << ")" << std::endl;
    }
}

void test_delete_gateway(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_gateway_request request;
    request.set_id(test_config().gtw_id);

    // Send request
    auto response = client.delete_gateway(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete gateway: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_get_gateway_stats(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_gateway_stats_request request;
    request.set_gateway_id(test_config().gtw_id);
    request.set_interval("minute");
    request.mutable_start_timestamp()->set_seconds(0);
    request.mutable_end_timestamp()->set_seconds(120);

    // Send request
    auto response = client.get_gateway_stats(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get gateway stats: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tGateway " << test_config().gtw_id  << "'s stats" << std::endl;
    for (const auto& stat : response.get().result()) {
        std::cout << "\t\tTimestamp: " << stat.timestamp().seconds() << std::endl;
        std::cout << "\t\t\tPackets received: " << stat.rx_packets_received() << std::endl;
        std::cout << "\t\t\tPackets received that passed the CRC check: " << stat.rx_packets_received_ok() << std::endl;
        std::cout << "\t\t\tPackets received for transmission: " << stat.tx_packets_received() << std::endl;
        std::cout << "\t\t\tPackets transmitted: " << stat.tx_packets_emitted() << std::endl;
    }
}

void test_get_last_ping(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_last_ping_request request;
    request.set_gateway_id(test_config().gtw_id);

    // Send request
    auto response = client.get_last_ping(request);
    if (!response.is_valid()) {
        if (response.error_code() == grpc::StatusCode::NOT_FOUND) {
            std::cout << "Warning: Have not received any ping from gateway " << test_config().gtw_id << std::endl;
            return;
        } else {
            std::cerr << "Failed to get last ping: " << response.error_code() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Display response
    std::cout << "\tGateway " << test_config().gtw_id  << "'s last ping" << std::endl;
    std::cout << "\t\tCreated at: " << response.get().created_at().seconds() << std::endl;
    std::cout << "\t\tFrequency: " << response.get().frequency() << std::endl;
    std::cout << "\t\tData-rate: " << response.get().dr() << std::endl;
    std::cout << "\t\tMeta-data: " << response.get().dr() << std::endl;
    for (const auto& ping_rx : response.get().ping_rx()) {
        std::cout << "\t\t\tRSSI: " << ping_rx.rssi() << ", ";
        std::cout << "\t\t\tLoRa SNR: " << ping_rx.lora_snr() << ", ";
        std::cout << "\t\t\tLocation: (" << ping_rx.latitude() << ", " << ping_rx.longitude() << ", " << ping_rx.altitude() << ")";
        std::cout << std::endl;
    }
}

void test_generate_gateway_client_certificate(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    generate_gateway_client_certificate_request request;
    request.set_gateway_id(test_config().gtw_id);

    // Send request
    auto response = client.generate_gateway_client_certificate(request);
    if (!response.is_valid()) {
        if (response.error_code() == grpc::StatusCode::UNKNOWN) {
            std::cout << "Warning: No CA certificate or CA key is configured" << std::endl;
            return;
        } else {
            std::cerr << "Failed to get last ping: " << response.error_code() << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cerr << "Failed to generate gateway client certificate: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tGateway " << test_config().gtw_id  << "'s client certificate" << std::endl;
    std::cout << "\t\tTLS certificate: " << response.get().tls_cert() << std::endl;
    std::cout << "\t\tTLS key: " << response.get().tls_key() << std::endl;
    std::cout << "\t\tCA certificate: " << response.get().ca_cert() << std::endl;
    std::cout << "\t\tExpires at: " << response.get().expires_at().seconds() << std::endl;
}

void validate_config() {
    if (test_config().application_server.empty()) {
        throw std::runtime_error("Invalid application server");
    }
    if (test_config().jwt_token.empty()) {
        throw std::runtime_error("Invalid JWT token");
    }
    if (test_config().service_profile_id.empty()) {
        throw std::runtime_error("Invalid service-profile ID");
    }
    if (test_config().gtw_id.empty()) {
        throw std::runtime_error("Invalid gateway ID");
    }
}

int main(int argc, char** argv) {
    validate_config();

    chirpstack_client_config config{};
    config.jwt_token = test_config().jwt_token;
    config.log_enabled = test_config().client_log_enabled;
    chirpstack_client client{test_config().application_server, config};
    test_cache cache;

    std::cout << "GET SERVICE-PROFILE" << std::endl;
    get_service_profile(client, cache);

    std::cout << "TEST CREATE GATEWAY" << std::endl;
    test_create_gateway(client, cache);

    std::cout << "TEST GET GATEWAY" << std::endl;
    test_get_gateway(client, cache);

    std::cout << "TEST UPDATE GATEWAY" << std::endl;
    test_update_gateway(client, cache);

    std::cout << "TEST LIST GATEWAY" << std::endl;
    test_list_gateway(client, cache);

    std::cout << "TEST GET GATEWAY STATS" << std::endl;
    test_get_gateway_stats(client, cache);

    std::cout << "TEST GET LAST PING" << std::endl;
    test_get_last_ping(client, cache);

    std::cout << "TEST GENERATE GATEWAY CLIENT CERTIFICATE" << std::endl;
    test_generate_gateway_client_certificate(client, cache);

    std::cout << "TEST DELETE GATEWAY" << std::endl;
    test_delete_gateway(client, cache);

    return EXIT_SUCCESS;
}