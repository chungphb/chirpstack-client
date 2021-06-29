#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    int64_t user_id;
    api::User user;
};

void test_create_user(chirpstack_client& client, test_cache& cache) {
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

void test_get_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_user_request request;
    request.set_id(cache.user_id);

    // Send request
    auto response = client.get_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.user = response.get().user();

    // Display response
    std::cout << "\tUser " << cache.user.email() << std::endl;
    std::cout << "\t\tEmail: " << cache.user.id() << std::endl;
    std::cout << "\t\tIs admin: " << std::boolalpha << cache.user.is_admin() << std::endl;
    std::cout << "\t\tIs active: " << std::boolalpha << cache.user.is_active() << std::endl;
    std::cout << "\t\tSession timeout: " << cache.user.session_ttl() << std::endl;
    std::cout << "\t\tNote: " << cache.user.note() << std::endl;
}

void test_update_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_user_request request;
    *request.mutable_user() = cache.user;
    request.mutable_user()->set_is_active(false);

    // Send request
    auto response = client.update_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_user(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_user_request request;
    request.set_limit(10);

    // Send request
    auto response = client.list_user(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list user: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& user : response.get().result()) {
        std::cout << "\tUser " << user.email() << std::endl;
        std::cout << "\t\tID: " << user.id() << std::endl;
        std::cout << "\t\tIs admin: " << std::boolalpha << user.is_admin() << std::endl;
        std::cout << "\t\tIs active: " << std::boolalpha << user.is_active() << std::endl;
        std::cout << "\t\tSession timeout: " << user.session_ttl() << std::endl;
    }
}

void test_delete_user(chirpstack_client& client, test_cache& cache) {
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

void test_update_user_password(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_user_password_request request;
    request.set_user_id(cache.user_id);
    auto password = test_config().usr_password + "123";
    request.set_password(password);

    // Send request
    auto response = client.update_user_password(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update user password: " << response.error_code() << std::endl;
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
    if (test_config().usr_username.empty()) {
        throw std::runtime_error("Invalid user username");
    }
    if (test_config().usr_password.empty()) {
        throw std::runtime_error("Invalid user password");
    }
}

int main(int argc, char** argv) {
    validate_config();

    chirpstack_client_config config{};
    config.jwt_token = test_config().global_jwt_token;
    config.log_enabled = test_config().client_log_enabled;
    chirpstack_client client{test_config().application_server, config};
    test_cache cache;

    std::cout << "TEST CREATE USER" << std::endl;
    test_create_user(client, cache);

    std::cout << "TEST GET USER" << std::endl;
    test_get_user(client, cache);

    std::cout << "TEST UPDATE USER PASSWORD" << std::endl;
    test_update_user_password(client, cache);

    std::cout << "TEST UPDATE USER" << std::endl;
    test_update_user(client, cache);

    std::cout << "TEST LIST USER" << std::endl;
    test_list_user(client, cache);

    std::cout << "TEST DELETE USER" << std::endl;
    test_delete_user(client, cache);

    return EXIT_SUCCESS;
}