#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    api::ServiceProfile service_profile;
    std::string device_profile_id;
    api::DeviceProfile device_profile;
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

void test_create_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_device_profile_request request;
    request.mutable_device_profile()->set_name(DEVICE_PROFILE_NAME);
    request.mutable_device_profile()->set_organization_id(cache.service_profile.organization_id());
    request.mutable_device_profile()->set_network_server_id(cache.service_profile.network_server_id());
    request.mutable_device_profile()->set_mac_version("1.0.3");
    request.mutable_device_profile()->set_reg_params_revision("B");
    request.mutable_device_profile()->set_supports_join(true);

    // Send request
    auto response = client.create_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create device-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.device_profile_id = response.get().id();
}

void test_get_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_device_profile_request request;
    request.set_id(cache.device_profile_id);

    // Send request
    auto response = client.get_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get device-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.device_profile = response.get().device_profile();

    // Display response
    std::cout << "\tDevice-profile " << cache.device_profile.name() << std::endl;
    std::cout << "\t\tID: " << cache.device_profile.id() << std::endl;
    std::cout << "\t\tOrganization ID: " << cache.device_profile.organization_id() << std::endl;
    std::cout << "\t\tNetwork-server ID: " << cache.device_profile.network_server_id() << std::endl;
    std::cout << "\t\tSupport Class B: " << std::boolalpha << cache.device_profile.supports_class_b() << std::endl;
    std::cout << "\t\tSupport Class C: " << std::boolalpha << cache.device_profile.supports_class_c() << std::endl;
    std::cout << "\t\tSupport OTAA: " << std::boolalpha << cache.device_profile.supports_join() << std::endl;
}

void test_update_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_device_profile_request request;
    *request.mutable_device_profile() = cache.device_profile;
    request.mutable_device_profile()->set_supports_class_b(true);

    // Send request
    auto response = client.update_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update device-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_device_profile_request request;
    request.set_limit(10);
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.list_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list device-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& device_profile : response.get().result()) {
        std::cout << "\tDevice-profile " << device_profile.name() << std::endl;
        std::cout << "\t\tID: " << device_profile.id() << std::endl;
        std::cout << "\t\tOrganization ID: " << device_profile.organization_id() << std::endl;
        std::cout << "\t\tNetwork-server ID: " << device_profile.network_server_id() << std::endl;
    }
}

void test_delete_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_device_profile_request request;
    request.set_id(cache.device_profile_id);

    // Send request
    auto response = client.delete_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete device-profile: " << response.error_code() << std::endl;
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

    std::cout << "TEST CREATE DEVICE-PROFILE" << std::endl;
    test_create_device_profile(client, cache);

    std::cout << "TEST GET DEVICE-PROFILE" << std::endl;
    test_get_device_profile(client, cache);

    std::cout << "TEST UPDATE DEVICE-PROFILE" << std::endl;
    test_update_device_profile(client, cache);

    std::cout << "TEST LIST DEVICE-PROFILE" << std::endl;
    test_list_device_profile(client, cache);

    std::cout << "TEST DELETE DEVICE-PROFILE" << std::endl;
    test_delete_device_profile(client, cache);

    return EXIT_SUCCESS;
}