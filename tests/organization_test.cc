#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    int64_t organization_id;
    api::Organization organization;
    int64_t user_id;
    api::OrganizationUser organization_user;
};

void create_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_user_request request;
    request.mutable_user()->set_session_ttl(60);
    request.mutable_user()->set_is_admin(false);
    request.mutable_user()->set_is_active(true);
    request.mutable_user()->set_email(test_config().usr_username);
    request.mutable_user()->set_note(test_config().usr_username);
    request.set_password(test_config().usr_password);

    // Send request
    auto response = client.create_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.user_id = response.get().id();
}

void delete_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_user_request request;
    request.set_id(cache.user_id);

    // Send request
    auto response = client.delete_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_create_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_organization_request request;
    request.mutable_organization()->set_name(test_config().org_name);
    request.mutable_organization()->set_display_name(test_config().org_display_name);
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

void test_get_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_organization_request request;
    request.set_id(cache.organization_id);

    // Send request
    auto response = client.get_organization(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get organization: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.organization = response.get().organization();

    // Display response
    std::cout << "\tOrganization " << cache.organization.name() << std::endl;
    std::cout << "\t\tDisplay name: " << std::boolalpha << cache.organization.display_name() << std::endl;
    std::cout << "\t\tID: " << cache.organization.id() << std::endl;
    std::cout << "\t\tCan have gateways: " << std::boolalpha << cache.organization.can_have_gateways() << std::endl;
    std::cout << "\t\tMax gateway count: " << cache.organization.max_gateway_count() << std::endl;
    std::cout << "\t\tMax device count: " << cache.organization.max_device_count() << std::endl;
}

void test_update_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_organization_request request;
    *request.mutable_organization() = cache.organization;
    request.mutable_organization()->set_max_device_count(1000);

    // Send request
    auto response = client.update_organization(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update organization: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_organization(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_organization_request request;
    request.set_limit(10);

    // Send request
    auto response = client.list_organization(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list organization: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& organization : response.get().result()) {
        std::cout << "\tOrganization " << organization.name() << std::endl;
        std::cout << "\t\tDisplay name: " << std::boolalpha << organization.display_name() << std::endl;
        std::cout << "\t\tID: " << organization.id() << std::endl;
        std::cout << "\t\tCan have gateways: " << std::boolalpha << organization.can_have_gateways() << std::endl;
    }
}

void test_delete_organization(chirpstack_client& client, test_cache& cache) {
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

void test_add_organization_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    add_organization_user_request request;
    request.mutable_organization_user()->set_organization_id(cache.organization_id);
    request.mutable_organization_user()->set_user_id(cache.user_id);
    request.mutable_organization_user()->set_is_admin(false);
    request.mutable_organization_user()->set_is_device_admin(true);
    request.mutable_organization_user()->set_is_gateway_admin(false);
    request.mutable_organization_user()->set_email(test_config().usr_username);

    // Send request
    auto response = client.add_organization_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to add organization user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_get_organization_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_organization_user_request request;
    request.set_organization_id(cache.organization_id);
    request.set_user_id(cache.user_id);

    // Send request
    auto response = client.get_organization_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get organization user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.organization_user = response.get().organization_user();

    // Display response
    std::cout << "\tOrganization " << cache.organization.name() << "'s user " << cache.organization_user.email() << std::endl;
    std::cout << "\t\tID: " << cache.organization_user.user_id() << std::endl;
    std::cout << "\t\tIs admin: " << std::boolalpha << cache.organization_user.is_admin() << std::endl;
    if (!cache.organization_user.is_admin()) {
        std::cout << "\t\tIs device admin: " << std::boolalpha << cache.organization_user.is_device_admin() << std::endl;
        std::cout << "\t\tIs gateway admin: " << std::boolalpha << cache.organization_user.is_gateway_admin() << std::endl;
    }
}

void test_update_organization_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_organization_user_request request;
    *request.mutable_organization_user() = cache.organization_user;
    request.mutable_organization_user()->set_is_admin(true);

    // Send request
    auto response = client.update_organization_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update organization user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_organization_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_organization_users_request request;
    request.set_organization_id(cache.organization_id);
    request.set_limit(10);

    // Send request
    auto response = client.list_organization_users(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list organization user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& organization_user : response.get().result()) {
        std::cout << "\tOrganization " << cache.organization.name() << "'s user " << organization_user.email() << std::endl;
        std::cout << "\t\tID: " << organization_user.user_id() << std::endl;
        std::cout << "\t\tIs admin: " << std::boolalpha << organization_user.is_admin() << std::endl;
        if (!organization_user.is_admin()) {
            std::cout << "\t\tIs device admin: " << std::boolalpha << organization_user.is_device_admin() << std::endl;
            std::cout << "\t\tIs gateway admin: " << std::boolalpha << organization_user.is_gateway_admin() << std::endl;
        }
    }
}

void test_delete_organization_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_organization_user_request request;
    request.set_organization_id(cache.organization_id);
    request.set_user_id(cache.user_id);

    // Send request
    auto response = client.delete_organization_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete organization user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {
    chirpstack_client_config config{};
    config.jwt_token = test_config().global_jwt_token;
    chirpstack_client client{test_config().application_server, config};
    test_cache cache;

    std::cout << "TEST CREATE ORGANIZATION" << std::endl;
    test_create_organization(client, cache);

    std::cout << "TEST GET ORGANIZATION" << std::endl;
    test_get_organization(client, cache);

    std::cout << "TEST UPDATE ORGANIZATION" << std::endl;
    test_update_organization(client, cache);

    std::cout << "TEST LIST ORGANIZATION" << std::endl;
    test_list_organization(client, cache);

    std::cout << "CREATE USER" << std::endl;
    create_user(client, cache);

    std::cout << "TEST ADD ORGANIZATION USER" << std::endl;
    test_add_organization_user(client, cache);

    std::cout << "TEST GET ORGANIZATION USER" << std::endl;
    test_get_organization_user(client, cache);

    std::cout << "TEST UPDATE ORGANIZATION USER" << std::endl;
    test_update_organization_user(client, cache);

    std::cout << "TEST LIST ORGANIZATION USER" << std::endl;
    test_list_organization_user(client, cache);

    std::cout << "TEST DELETE ORGANIZATION USER" << std::endl;
    test_delete_organization_user(client, cache);

    std::cout << "DELETE USER" << std::endl;
    delete_user(client, cache);

    std::cout << "TEST DELETE ORGANIZATION" << std::endl;
    test_delete_organization(client, cache);

    return EXIT_SUCCESS;
}