#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

using namespace chirpstack_cpp_client;

struct test_cache {
    int64_t network_server_id;
    int64_t organization_id;
    std::string service_profile_id;
    api::ServiceProfile service_profile;
};

void generate_bash_files() {
    std::ofstream ofs;
    struct stat buf{};
    auto start = stat("start-sample-network-server.sh", &buf);
    auto stop = stat("stop-sample-network-server.sh", &buf);

    if (start != 0) {
        std::cout << "GENERATE start-sample-network-server.sh BASH SCRIPT" << std::endl;
        ofs.open("start-sample-network-server.sh", std::ofstream::out | std::ofstream::trunc);
        ofs << R"(#!/bin/bash)" << '\n';
        ofs << R"(chirpstack-network-server configfile > sample-ns-config.toml)" << '\n';
        ofs << R"(sed -i -E "s/bind=\".+\"/bind=\")" << NETWORK_SERVER_SERVER << R"(\"/" sample-ns-config.toml)" << '\n';
        ofs << R"(sed -i -E "s/dsn=\".*\"/dsn=\")";
        ofs << R"(postgres:\/\/sample_ns:sample_ns@localhost\/sample_ns?sslmode=disable)";
        ofs << R"(\"/" sample-ns-config.toml)" << '\n';
        ofs << R"(sudo -Hiu postgres -- psql -c "create role sample_ns with login password 'sample_ns';")" << '\n';
        ofs << R"(sudo -Hiu postgres -- psql -c "create database sample_ns with owner sample_ns;")" << '\n';
        ofs << R"(chirpstack-network-server --config sample-ns-config.toml)";
        ofs << std::endl;
        ofs.close();
    }

    if (stop != 0) {
        std::cout << "GENERATE stop-sample-network-server.sh BASH SCRIPT" << std::endl;
        ofs.open("stop-sample-network-server.sh", std::ofstream::out | std::ofstream::trunc);
        ofs << R"(#!/bin/bash)" << '\n';
        ofs << R"(kill $(ps aux | grep "chirpstack-network-server --config sample-ns-config.toml" | awk '{print $2}'))" << '\n';
        ofs << R"(sudo -Hiu postgres -- psql -c "drop database sample_ns;")" << '\n';
        ofs << R"(sudo -Hiu postgres -- psql -c "drop role sample_ns;")" << '\n';
        ofs << R"(rm -rf sample-ns-config.toml)";
        ofs << std::endl;
        ofs.close();
    }

    std::cout << "\nDON'T FORGET TO RUN start-sample-network-server.sh BASH SCRIPT BEFORE TESTING" << std::endl;
    std::cout << "\nPress ENTER to continue if sample network-server has been started..." << std::endl;
    std::cin.ignore();
}

void create_network_server(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_network_server_request request;
    request.mutable_network_server()->set_name(NETWORK_SERVER_NAME);
    request.mutable_network_server()->set_server(NETWORK_SERVER_SERVER);
    request.mutable_network_server()->set_gateway_discovery_enabled(true);
    request.mutable_network_server()->set_gateway_discovery_interval(24);
    request.mutable_network_server()->set_gateway_discovery_tx_frequency(960000000);
    request.mutable_network_server()->set_gateway_discovery_dr(100);

    // Send request
    auto response = client.create_network_server(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create network-server: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.network_server_id = response.get().id();
}

void delete_network_server(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_network_server_request request;
    request.set_id(cache.network_server_id);

    // Send request
    auto response = client.delete_network_server(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete network-server: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void create_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_organization_request request;
    request.mutable_organization()->set_name(ORGANIZATION_NAME);
    request.mutable_organization()->set_display_name(ORGANIZATION_DISPLAY_NAME);
    request.mutable_organization()->set_can_have_gateways(true);
    request.mutable_organization()->set_max_gateway_count(10);
    request.mutable_organization()->set_max_device_count(100);

    // Send request
    auto response = client.create_organization(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create organization: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.organization_id = response.get().id();
}

void delete_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_organization_request request;
    request.set_id(cache.organization_id);

    // Send request
    auto response = client.delete_organization(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete organization: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_create_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_service_profile_request request;
    request.mutable_service_profile()->set_name(SERVICE_PROFILE_NAME);
    request.mutable_service_profile()->set_organization_id(cache.organization_id);
    request.mutable_service_profile()->set_network_server_id(cache.network_server_id);
    request.mutable_service_profile()->set_dr_min(0);
    request.mutable_service_profile()->set_dr_max(1000);

    // Send request
    auto response = client.create_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.service_profile_id = response.get().id();
}

void test_get_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_service_profile_request request;
    request.set_id(cache.service_profile_id);

    // Send request
    auto response = client.get_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.service_profile = response.get().service_profile();

    // Display response
    std::cout << "\tService-profile " << cache.service_profile.name() << std::endl;
    std::cout << "\t\tID: " << cache.service_profile.id() << std::endl;
    std::cout << "\t\tOrganization ID: " << cache.service_profile.organization_id() << std::endl;
    std::cout << "\t\tNetwork-server ID: " << cache.service_profile.network_server_id() << std::endl;
    std::cout << "\t\tMinimum allowed data-rate: " << cache.service_profile.dr_min() << std::endl;
    std::cout << "\t\tMaximum allowed data-rate: " << cache.service_profile.dr_max() << std::endl;
}

void test_update_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_service_profile_request request;
    *request.mutable_service_profile() = cache.service_profile;
    request.mutable_service_profile()->set_dr_min(10);

    // Send request
    auto response = client.update_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_service_profile_request request;
    request.set_limit(10);
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.list_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& service_profile : response.get().result()) {
        std::cout << "\tService-profile " << service_profile.name() << std::endl;
        std::cout << "\t\tID: " << service_profile.id() << std::endl;
        std::cout << "\t\tOrganization ID: " << service_profile.organization_id() << std::endl;
        std::cout << "\t\tNetwork-server ID: " << service_profile.network_server_id() << std::endl;
    }
}

void test_delete_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_service_profile_request request;
    request.set_id(cache.service_profile_id);

    // Send request
    auto response = client.delete_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {
    chirpstack_client_config config{};
    config.jwt_token = GLOBAL_JWT_TOKEN;
    chirpstack_client client{APPLICATION_SERVER, config};
    test_cache cache;

    generate_bash_files();

    std::cout << "CREATE NETWORK-SERVER" << std::endl;
    create_network_server(client, cache);

    std::cout << "CREATE ORGANIZATION" << std::endl;
    create_organization(client, cache);

    std::cout << "TEST CREATE SERVICE-PROFILE" << std::endl;
    test_create_service_profile(client, cache);

    std::cout << "TEST GET SERVICE-PROFILE" << std::endl;
    test_get_service_profile(client, cache);

    std::cout << "TEST UPDATE SERVICE-PROFILE" << std::endl;
    test_update_service_profile(client, cache);

    std::cout << "TEST LIST SERVICE-PROFILE" << std::endl;
    test_list_service_profile(client, cache);

    std::cout << "TEST DELETE SERVICE-PROFILE" << std::endl;
    test_delete_service_profile(client, cache);

    std::cout << "DELETE ORGANIZATION" << std::endl;
    delete_organization(client, cache);

    std::cout << "DELETE NETWORK-SERVER" << std::endl;
    delete_network_server(client, cache);

    std::cout << "\nDON'T FORGET TO RUN stop-sample-network-server.sh BASH SCRIPT AFTER TESTING" << std::endl;

    return EXIT_SUCCESS;
}