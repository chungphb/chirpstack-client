//
// Created by vht on 6/24/21.
//

#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    std::string jwt_tag;
    std::string api_key_id;
    std::string jwt_token;
    bool enable_open_id_connect;
    api::ServiceProfile service_profile;
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

void test_login(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    login_request request;
    request.set_email(test_config().admin_username);
    request.set_password(test_config().admin_password);

    // Send request
    auto response = client.login(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to login as admin: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.jwt_tag = response.get().jwt();

    // Display response
    std::cout << "\tJWT tag: " << cache.jwt_tag << std::endl;
}

void test_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    profile_request request;

    // Send request
    auto response = client.profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tUser " << response.get().user().email() << std::endl;
    std::cout << "\t\tID: " << response.get().user().id() << std::endl;
    std::cout << "\t\tIs admin: " << std::boolalpha << response.get().user().is_admin() << std::endl;
    std::cout << "\t\tIs active: " << std::boolalpha << response.get().user().is_active() << std::endl;
    std::cout << "\t\tSession timeout: " << response.get().user().session_ttl() << std::endl;
    if (!response.get().user().note().empty()) {
        std::cout << "\t\tNote: " << response.get().user().note() << std::endl;
    }
    for (const auto& organization : response.get().organizations()) {
        std::cout << "\t\tIn organization " << organization.organization_name() << std::endl;
        std::cout << "\t\t\tID: " << organization.organization_id() << std::endl;
        std::cout << "\t\t\tIs admin: " << std::boolalpha << organization.is_admin() << std::endl;
        if (!organization.is_admin()) {
            std::cout << "\t\t\tIs device admin: " << std::boolalpha << organization.is_device_admin() << std::endl;
            std::cout << "\t\t\tIs gateway admin: " << std::boolalpha << organization.is_gateway_admin() << std::endl;
        }
    }
}

void test_global_search(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    global_search_request request;
    request.set_search("c");
    request.set_limit(10);

    // Send request
    auto response = client.global_search(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to global search: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tResult for \"c\"" << std::endl;
    for (const auto& result : response.get().result()) {
        std::cout << "\t\tKind = " << result.kind() << ": ";
        if (!result.organization_name().empty() && result.device_name().empty() && result.gateway_name().empty()) {
            std::cout << "Name = " << result.organization_name() << ", ";
            std::cout << "ID = " << result.organization_id();
            std::cout << std::endl;
        }
        if (!result.application_name().empty() && result.device_name().empty()) {
            std::cout << "Name = " << result.application_name() << ", ";
            std::cout << "ID = " << result.application_id();
            std::cout << std::endl;
        }
        if (!result.device_name().empty()) {
            std::cout << "Name = " << result.device_name() << " (";
            std::cout << "organization = " << result.organization_name() << ", ";
            std::cout << "application = " << result.application_name() << "), ";
            std::cout << "ID = " << result.device_dev_eui();
            std::cout << std::endl;
        }
        if (!result.gateway_name().empty()) {
            std::cout << "Name = " << result.gateway_name() << " (";
            std::cout << "organization = " << result.organization_name() << "), ";
            std::cout << "ID = " << result.gateway_mac();
            std::cout << std::endl;
        }
    }
}

void test_create_api_key(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_api_key_request request;
    request.mutable_api_key()->set_name(test_config().api_key_name);
    request.mutable_api_key()->set_is_admin(true);

    // Send request
    auto response = client.create_api_key(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create API key: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.api_key_id = response.get().id();
    cache.jwt_token = response.get().jwt_token();

    // Display response
    std::cout << "\tAPI key " << test_config().api_key_name << std::endl;
    std::cout << "\t\tID: " << response.get().id() << std::endl;
    std::cout << "\t\tJWT token: " << response.get().jwt_token() << std::endl;
}

void test_delete_api_key(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_api_key_request request;
    request.set_id(cache.api_key_id);

    // Send request
    auto response = client.delete_api_key(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete API key: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_api_keys(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_api_keys_request request;
    request.set_limit(10);
    request.set_is_admin(true);

    // Send request
    auto response = client.list_api_keys(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list API keys: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& api_key : response.get().result()) {
        std::cout << "\tAPI key " << api_key.name() << std::endl;
        std::cout << "\t\tID: " << api_key.id() << std::endl;
        std::cout << "\t\tIs admin: " << std::boolalpha << api_key.is_admin() << std::endl;
        std::cout << "\t\tOrganization ID: " << api_key.organization_id() << std::endl;
        std::cout << "\t\tApplication ID: " << api_key.application_id() << std::endl;
    }
}

void test_settings(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    settings_request request;

    // Send request
    auto response = client.settings(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get settings: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.enable_open_id_connect = response.get().openid_connect().enabled();

    // Display response
    std::cout << "\tBranding"<< std::endl;
    std::cout << "\t\tRegistration: " << response.get().branding().registration() << std::endl;
    std::cout << "\t\tFooter: " << response.get().branding().footer() << std::endl;
    std::cout << "\tOpenIDConnect"<< std::endl;
    std::cout << "\t\tEnabled: " << std::boolalpha << response.get().openid_connect().enabled() << std::endl;
    if (response.get().openid_connect().enabled()) {
        std::cout << "\t\tLogin URL: " << response.get().openid_connect().login_url() << std::endl;
        std::cout << "\t\tLogin label: " << response.get().openid_connect().login_label() << std::endl;
        std::cout << "\t\tLogout URL: " << response.get().openid_connect().logout_url() << std::endl;
    }
}

void test_open_id_connect_login(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    open_id_connect_login_request request;
    request.set_code("sample-code");
    request.set_state("sample-state");

    // Send request
    auto response = client.open_id_connect_login(request);
    if (!response.is_valid()) {
        if (!cache.enable_open_id_connect && response.error_code() == grpc::StatusCode::UNKNOWN) {
            std::cerr << "Warning: OpenID Connect is not enabled" << std::endl;
            return;
        } else {
            std::cerr << "Failed to login by OpenID Connect: " << response.error_code() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Display response
    std::cout << "\tJWT token: " << response.get().jwt_token() << std::endl;
}

void test_get_devices_summary(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_devices_summary_request request;
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.get_devices_summary(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get devices summary: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tActive count: " << response.get().active_count() << std::endl;
    std::cout << "\tInactive count: " << response.get().inactive_count() << std::endl;
    std::cout << "\tData-rate count" << std::endl;
    for (const auto& dr : response.get().dr_count()) {
        std::cout << "\t\tDR = " << dr.first << ": " << dr.second << std::endl;
    }
    std::cout << "\tNever seen count: " << response.get().inactive_count() << std::endl;
}

void test_get_gateways_summary(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_gateways_summary_request request;
    request.set_organization_id(cache.service_profile.organization_id());

    // Send request
    auto response = client.get_gateways_summary(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get gateways summary: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tActive count: " << response.get().active_count() << std::endl;
    std::cout << "\tInactive count: " << response.get().inactive_count() << std::endl;
    std::cout << "\tNever seen count: " << response.get().inactive_count() << std::endl;
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
    if (test_config().admin_username.empty()) {
        throw std::runtime_error("Invalid admin username");
    }
    if (test_config().admin_password.empty()) {
        throw std::runtime_error("Invalid admin password");
    }
    if (test_config().api_key_name.empty()) {
        throw std::runtime_error("Invalid API key name");
    }
}

int main(int argc, char** argv) {
    validate_config();

    chirpstack_client_config config{};
    chirpstack_client client{test_config().application_server, config};
    config.log_enabled = test_config().client_log_enabled;
    test_cache cache;

    std::cout << "TEST LOGIN" << std::endl;
    test_login(client, cache);
    client.set_jwt_token(cache.jwt_tag);

    std::cout << "TEST PROFILE" << std::endl;
    test_profile(client, cache);

    std::cout << "TEST GLOBAL SEARCH" << std::endl;
    test_global_search(client, cache);

    std::cout << "TEST CREATE API KEY" << std::endl;
    test_create_api_key(client, cache);

    std::cout << "TEST LIST API KEYS" << std::endl;
    test_list_api_keys(client, cache);

    std::cout << "TEST DELETE API KEY" << std::endl;
    test_delete_api_key(client, cache);

    std::cout << "TEST SETTINGS" << std::endl;
    test_settings(client, cache);

    std::cout << "TEST OPENID CONNECT LOGIN" << std::endl;
    test_open_id_connect_login(client, cache);

    std::cout << "GET SERVICE-PROFILE" << std::endl;
    get_service_profile(client, cache);

    client.set_jwt_token(test_config().jwt_token);
    std::cout << "TEST GET DEVICES SUMMARY" << std::endl;
    test_get_devices_summary(client, cache);

    std::cout << "TEST GET GATEWAYS SUMMARY" << std::endl;
    test_get_gateways_summary(client, cache);

    return EXIT_SUCCESS;
}