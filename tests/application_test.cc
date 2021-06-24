#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    api::ServiceProfile service_profile;
    int64_t application_id;
    api::Application application;
};

void get_service_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_service_profile_request request;
    request.set_id(SERVICE_PROFILE_ID);

    // Send request
    auto response = client.get_service_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get service-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.service_profile = response.get().service_profile();
}

void test_create_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_application_request request;
    request.mutable_application()->set_name(APPLICATION_NAME);
    request.mutable_application()->set_description(APPLICATION_NAME);
    request.mutable_application()->set_organization_id(cache.service_profile.organization_id());
    request.mutable_application()->set_service_profile_id(cache.service_profile.id());

    // Send request
    auto response = client.create_application(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create application: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.application_id = response.get().id();
}

void test_get_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_application_request request;
    request.set_id(cache.application_id);

    // Send request
    auto response = client.get_application(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get application: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.application = response.get().application();

    // Display response
    std::cout << "\tApplication " << cache.application.name() << std::endl;
    std::cout << "\t\tID: " << cache.application.id() << std::endl;
    std::cout << "\t\tDescription: " << cache.application.description() << std::endl;
    std::cout << "\t\tOrganization ID: " << cache.application.organization_id() << std::endl;
    std::cout << "\t\tService-profile ID: " << cache.application.service_profile_id() << std::endl;
}

void test_update_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_application_request request;
    *request.mutable_application() = cache.application;
    auto description = std::string(APPLICATION_NAME);
    description += "-" + std::to_string(cache.application.id());
    request.mutable_application()->set_description(description);

    // Send request
    auto response = client.update_application(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update application: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_application_request request;
    request.set_limit(10);
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.list_application(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list application: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& application : response.get().result()) {
        std::cout << "\tApplication " << application.name() << std::endl;
        std::cout << "\t\tID: " << application.id() << std::endl;
        std::cout << "\t\tDescription: " << application.description() << std::endl;
        std::cout << "\t\tOrganization ID: " << application.organization_id() << std::endl;
        std::cout << "\t\tService-profile ID: " << application.service_profile_id() << std::endl;
    }
}

void test_delete_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_application_request request;
    request.set_id(cache.application_id);

    // Send request
    auto response = client.delete_application(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete application: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {
    chirpstack_client_config config{};
    config.jwt_token = JWT_TOKEN;
    chirpstack_client client{APPLICATION_SERVER, config};
    test_cache cache;

    std::cout << "GET SERVICE-PROFILE" << std::endl;
    get_service_profile(client, cache);

    std::cout << "TEST CREATE APPLICATION" << std::endl;
    test_create_application(client, cache);

    std::cout << "TEST GET APPLICATION" << std::endl;
    test_get_application(client, cache);

    std::cout << "TEST UPDATE APPLICATION" << std::endl;
    test_update_application(client, cache);

    std::cout << "TEST LIST APPLICATION" << std::endl;
    test_list_application(client, cache);

    std::cout << "TEST DELETE APPLICATION" << std::endl;
    test_delete_application(client, cache);

    return EXIT_SUCCESS;
}