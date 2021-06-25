#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

using namespace chirpstack_cpp_client;

struct test_cache {
    int64_t network_server_id;
    api::NetworkServer network_server;
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

void test_create_network_server(chirpstack_client& client, test_cache& cache) {
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

void test_get_network_server(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_network_server_request request;
    request.set_id(cache.network_server_id);

    // Send request
    auto response = client.get_network_server(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get network-server: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.network_server = response.get().network_server();

    // Display response
    std::cout << "\tNetwork server " << cache.network_server.name() << std::endl;
    std::cout << "\t\tID: " << cache.network_server.id() << std::endl;
    std::cout << "\t\tServer: " << cache.network_server.server() << std::endl;
    std::cout << "\t\tEnable gateway discovery: " << std::boolalpha << cache.network_server.gateway_discovery_enabled() << std::endl;
    if (cache.network_server.gateway_discovery_enabled()) {
        std::cout << "\t\tGateway discovery interval: " << cache.network_server.gateway_discovery_interval() << std::endl;
        std::cout << "\t\tGateway discovery frequency: " << cache.network_server.gateway_discovery_tx_frequency() << std::endl;
        std::cout << "\t\tGateway discovery data-rate: " << cache.network_server.gateway_discovery_dr() << std::endl;
    }
}

void test_update_network_server(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_network_server_request request;
    *request.mutable_network_server() = cache.network_server;
    request.mutable_network_server()->set_gateway_discovery_enabled(false);

    // Send request
    auto response = client.update_network_server(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update network_server: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_network_server(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_network_server_request request;
    request.set_limit(10);

    // Send request
    auto response = client.list_network_server(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list network-server: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& network_server : response.get().result()) {
        std::cout << "\tNetwork server " << network_server.name() << std::endl;
        std::cout << "\t\tID: " << network_server.id() << std::endl;
        std::cout << "\t\tServer: " << network_server.server() << std::endl;
    }
}

void test_delete_network_server(chirpstack_client& client, test_cache& cache) {
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

void test_get_adr_algorithms(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_adr_algorithms_request request;
    request.set_network_server_id(cache.network_server_id);

    // Send request
    auto response = client.get_adr_algorithms(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get ADR algorithms: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tNetwork server " << cache.network_server.name() << "'s ADR algorithms" << std::endl;
    for (const auto& adr_algorithm : response.get().adr_algorithms()) {
        std::cout << "\t\tID: " << adr_algorithm.id() << ", ";
        std::cout << "\t\tName: " << adr_algorithm.name();
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    chirpstack_client_config config{};
    config.jwt_token = GLOBAL_JWT_TOKEN;
    chirpstack_client client{APPLICATION_SERVER, config};
    test_cache cache;

    generate_bash_files();

    std::cout << "TEST CREATE NETWORK-SERVER" << std::endl;
    test_create_network_server(client, cache);

    std::cout << "TEST GET NETWORK-SERVER" << std::endl;
    test_get_network_server(client, cache);

    std::cout << "TEST GET ADR ALGORITHMS" << std::endl;
    test_get_adr_algorithms(client, cache);

    std::cout << "TEST UPDATE NETWORK-SERVER" << std::endl;
    test_update_network_server(client, cache);

    std::cout << "TEST LIST NETWORK-SERVER" << std::endl;
    test_list_network_server(client, cache);

    std::cout << "TEST DELETE NETWORK-SERVER" << std::endl;
    test_delete_network_server(client, cache);

    std::cout << "\nDON'T FORGET TO RUN stop-sample-network-server.sh BASH SCRIPT AFTER TESTING" << std::endl;

    return EXIT_SUCCESS;
}