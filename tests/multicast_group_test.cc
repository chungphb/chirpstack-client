#include "test_config.h"
#include <chirpstack_client/chirpstack_client.h>
#include <iostream>

using namespace chirpstack_cpp_client;

struct test_cache {
    api::ServiceProfile service_profile;
    std::string multicast_group_id;
    api::MulticastGroup multicast_group;
    std::string device_profile_id;
    int64_t application_id;
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

void create_application(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_application_request request;
    request.mutable_application()->set_name(test_config().app_name);
    request.mutable_application()->set_description(test_config().app_name);
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

void delete_application(chirpstack_client& client, test_cache& cache) {
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

void create_device_profile(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_device_profile_request request;
    request.mutable_device_profile()->set_name(test_config().dp_name);
    request.mutable_device_profile()->set_organization_id(cache.service_profile.organization_id());
    request.mutable_device_profile()->set_network_server_id(cache.service_profile.network_server_id());
    request.mutable_device_profile()->set_mac_version("1.0.3");
    request.mutable_device_profile()->set_reg_params_revision("B");
    request.mutable_device_profile()->set_supports_join(false);
    request.mutable_device_profile()->set_supports_class_b(true);
    request.mutable_device_profile()->set_class_b_timeout(16);
    request.mutable_device_profile()->set_ping_slot_period(16);
    request.mutable_device_profile()->set_ping_slot_dr(100);
    request.mutable_device_profile()->set_ping_slot_freq(900000000);

    // Send request
    auto response = client.create_device_profile(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create device-profile: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.device_profile_id = response.get().id();
}

void delete_device_profile(chirpstack_client& client, test_cache& cache) {
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

void create_device(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_device_request request;
    request.mutable_device()->set_dev_eui(test_config().dev_eui);
    request.mutable_device()->set_name(test_config().dev_eui);
    request.mutable_device()->set_description(test_config().dev_eui);
    request.mutable_device()->set_application_id(cache.application_id);
    request.mutable_device()->set_device_profile_id(cache.device_profile_id);

    // Send request
    auto response = client.create_device(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create device: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void activate_device(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    activate_device_request request;
    request.mutable_device_activation()->set_dev_eui(test_config().dev_eui);
    request.mutable_device_activation()->set_dev_addr(test_config().dev_address);
    request.mutable_device_activation()->set_app_s_key(test_config().dev_app_s_key);
    request.mutable_device_activation()->set_nwk_s_enc_key(test_config().dev_nwk_s_enc_key);
    request.mutable_device_activation()->set_s_nwk_s_int_key(test_config().dev_s_nwk_int_key);
    request.mutable_device_activation()->set_f_nwk_s_int_key(test_config().dev_f_nwk_int_key);

    // Send request
    auto response = client.activate_device(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to activate device: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void reactivate_device(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    activate_device_request request;
    request.mutable_device_activation()->set_dev_eui(test_config().dev_eui);
    request.mutable_device_activation()->set_dev_addr(test_config().mc_address);
    request.mutable_device_activation()->set_app_s_key(test_config().mc_app_s_key);
    request.mutable_device_activation()->set_nwk_s_enc_key(test_config().mc_nwk_s_key);
    request.mutable_device_activation()->set_s_nwk_s_int_key(test_config().mc_nwk_s_key);
    request.mutable_device_activation()->set_f_nwk_s_int_key(test_config().mc_nwk_s_key);

    // Send request
    auto response = client.activate_device(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to reactivate device: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void delete_device(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_device_request request;
    request.set_dev_eui(test_config().dev_eui);

    // Send request
    auto response = client.delete_device(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete device: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_create_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    create_multicast_group_request request;
    request.mutable_multicast_group()->set_name(test_config().mc_name);
    request.mutable_multicast_group()->set_service_profile_id(cache.service_profile.id());
    request.mutable_multicast_group()->set_mc_addr(test_config().mc_address);
    request.mutable_multicast_group()->set_mc_nwk_s_key(test_config().mc_nwk_s_key);
    request.mutable_multicast_group()->set_mc_app_s_key(test_config().mc_app_s_key);
    request.mutable_multicast_group()->set_f_cnt(0);
    request.mutable_multicast_group()->set_dr(100);
    request.mutable_multicast_group()->set_frequency(900000000);
    request.mutable_multicast_group()->set_group_type(api::MulticastGroupType::CLASS_B);
    request.mutable_multicast_group()->set_ping_slot_period(16);

    // Send request
    auto response = client.create_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to create multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.multicast_group_id = response.get().id();
}

void test_get_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    get_multicast_group_request request;
    request.set_id(cache.multicast_group_id);

    // Send request
    auto response = client.get_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to get multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Save response
    cache.multicast_group = response.get().multicast_group();

    // Display response
    std::cout << "\tMulticast-group " << cache.multicast_group.name() << std::endl;
    std::cout << "\t\tID: " << cache.multicast_group.id() << std::endl;
    std::cout << "\t\tService-profile ID: " << cache.multicast_group.service_profile_id() << std::endl;
    std::cout << "\t\tMulticast address: " << cache.multicast_group.mc_addr() << std::endl;
    std::cout << "\t\tMulticast network session key: " << cache.multicast_group.mc_nwk_s_key() << std::endl;
    std::cout << "\t\tMulticast application session key: " << cache.multicast_group.mc_app_s_key() << std::endl;
    std::cout << "\t\tFrame-counter: " << cache.multicast_group.f_cnt() << std::endl;
    std::cout << "\t\tData-rate: " << cache.multicast_group.dr() << std::endl;
    std::cout << "\t\tFrequency: " << cache.multicast_group.frequency() << std::endl;
    std::cout << "\t\tMulticast type: " << (cache.multicast_group.group_type() == api::MulticastGroupType::CLASS_B ? "B" : "C") << std::endl;
}

void test_update_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    update_multicast_group_request request;
    *request.mutable_multicast_group() = cache.multicast_group;
    request.mutable_multicast_group()->set_f_cnt(100);

    // Send request
    auto response = client.update_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to update multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_multicast_group_request request;
    request.set_limit(10);
    request.set_organization_id(cache.service_profile.organization_id());
    request.set_service_profile_id(cache.service_profile.id());

    // Send request
    auto response = client.list_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& multicast_group : response.get().result()) {
        std::cout << "\tMulticast-group " << multicast_group.name() << std::endl;
        std::cout << "\t\tID: " << multicast_group.id() << std::endl;
        std::cout << "\t\tService-profile ID: " << multicast_group.service_profile_id() << std::endl;
        std::cout << "\t\tService-profile name: " << multicast_group.service_profile_name() << std::endl;
    }
}

void test_delete_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    delete_multicast_group_request request;
    request.set_id(cache.multicast_group_id);

    // Send request
    auto response = client.delete_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to delete multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_add_device_to_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    add_device_to_multicast_group_request request;
    request.set_multicast_group_id(cache.multicast_group_id);
    request.set_dev_eui(test_config().dev_eui);

    // Send request
    auto response = client.add_device_to_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to add device to multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_remove_device_to_multicast_group(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    remove_device_from_multicast_group_request request;
    request.set_multicast_group_id(cache.multicast_group_id);
    request.set_dev_eui(test_config().dev_eui);

    // Send request
    auto response = client.remove_device_from_multicast_group(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to remove device from multicast-group: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_enqueue_multicast_queue_item(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    enqueue_multicast_queue_item_request request;
    request.mutable_multicast_queue_item()->set_multicast_group_id(cache.multicast_group_id);
    request.mutable_multicast_queue_item()->set_f_port(test_config().dev_f_port);
    request.mutable_multicast_queue_item()->set_data(test_config().dev_payload);

    // Send request
    auto response = client.enqueue_multicast_queue_item(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to enqueue multicast queue item: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    std::cout << "\tEnqueue item #" << response.get().f_cnt() << std::endl;
}

void test_flush_multicast_group_queue_items(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    flush_multicast_group_queue_items_request request;
    request.set_multicast_group_id(cache.multicast_group_id);

    // Send request
    auto response = client.flush_multicast_group_queue_items(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to flush multicast-group queue items: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void test_list_multicast_group_queue_items(chirpstack_client& client, test_cache& cache) {
    // Prepare request
    list_multicast_group_queue_items_request request;
    request.set_multicast_group_id(cache.multicast_group_id);

    // Send request
    auto response = client.list_multicast_group_queue_items(request);
    if (!response.is_valid()) {
        std::cerr << "Failed to list multicast-group queue items: " << response.error_code() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Display response
    for (const auto& multicast_queue_item : response.get().multicast_queue_items()) {
        std::cout << "\tQueue item #" << multicast_queue_item.f_cnt() << std::endl;
        std::cout << "\t\tF-Port: " << multicast_queue_item.f_port() << std::endl;
        std::cout << "\t\tData: " << multicast_queue_item.data() << std::endl;
    }
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
    if (test_config().app_name.empty()) {
        throw std::runtime_error("Invalid application name");
    }
    if (test_config().dp_name.empty()) {
        throw std::runtime_error("Invalid device-profile name");
    }
    if (test_config().dev_eui.empty()) {
        throw std::runtime_error("Invalid device EUI");
    }
    if (test_config().dev_address.empty()) {
        throw std::runtime_error("Invalid device address");
    }
    if (test_config().dev_app_s_key.empty() || test_config().dev_nwk_s_enc_key.empty()
        || test_config().dev_s_nwk_int_key.empty() || test_config().dev_f_nwk_int_key.empty()) {
        throw std::runtime_error("Invalid device session key");
    }
    if (test_config().dev_f_port < 0) {
        throw std::runtime_error("Invalid device f-port");
    }
    if (test_config().dev_payload.empty()) {
        throw std::runtime_error("Invalid device payload");
    }
    if (test_config().mc_address.empty()) {
        throw std::runtime_error("Invalid multicast-group address");
    }
    if (test_config().mc_app_s_key.empty() || test_config().mc_nwk_s_key.empty()) {
        throw std::runtime_error("Invalid multicast-group session key");
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

    std::cout << "CREATE DEVICE-PROFILE" << std::endl;
    create_device_profile(client, cache);

    std::cout << "CREATE APPLICATION" << std::endl;
    create_application(client, cache);

    std::cout << "CREATE DEVICE" << std::endl;
    create_device(client, cache);

    std::cout << "ACTIVATE DEVICE" << std::endl;
    activate_device(client, cache);

    std::cout << "TEST CREATE MULTICAST-GROUP" << std::endl;
    test_create_multicast_group(client, cache);

    std::cout << "TEST GET MULTICAST-GROUP" << std::endl;
    test_get_multicast_group(client, cache);

    std::cout << "TEST UPDATE MULTICAST-GROUP" << std::endl;
    test_update_multicast_group(client, cache);

    std::cout << "TEST LIST MULTICAST-GROUP" << std::endl;
    test_list_multicast_group(client, cache);

    std::cout << "TEST ADD DEVICE TO MULTICAST-GROUP" << std::endl;
    test_add_device_to_multicast_group(client, cache);

    std::cout << "REACTIVATE DEVICE" << std::endl;
    reactivate_device(client, cache);

    std::cout << "TEST ENQUEUE MULTICAST QUEUE ITEM" << std::endl;
    test_enqueue_multicast_queue_item(client, cache);

    std::cout << "TEST LIST MULTICAST-GROUP QUEUE ITEMS" << std::endl;
    test_list_multicast_group_queue_items(client, cache);

    std::cout << "TEST FLUSH MULTICAST-GROUP QUEUE ITEMS" << std::endl;
    test_flush_multicast_group_queue_items(client, cache);

    std::cout << "TEST REMOVE DEVICE FROM MULTICAST-GROUP" << std::endl;
    test_remove_device_to_multicast_group(client, cache);

    std::cout << "TEST DELETE MULTICAST-GROUP" << std::endl;
    test_delete_multicast_group(client, cache);

    std::cout << "DELETE DEVICE" << std::endl;
    delete_device(client, cache);

    std::cout << "DELETE APPLICATION" << std::endl;
    delete_application(client, cache);

    std::cout << "DELETE DEVICE-PROFILE" << std::endl;
    delete_device_profile(client, cache);

    return EXIT_SUCCESS;
}