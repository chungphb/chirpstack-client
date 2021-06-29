//
// Created by vht on 6/24/21.
//

#pragma once

#include <string>
#include <vector>

struct test_config {
    std::string application_server = "localhost::8080";
    std::string jwt_token;
    std::string service_profile_id;
    std::string global_jwt_token;
    std::string app_name = "sample-application";
    std::string dev_eui = "0001020304050607";
    std::string dev_nwk_key = "000102030405060708090a0b0c0d0e0f";
    std::string dev_app_key = "000102030405060708090a0b0c0d0e0f";
    std::string dev_address = "00010203";
    std::string dev_app_s_key = "000102030405060708090a0b0c0d0e0f";
    std::string dev_nwk_s_enc_key = "000102030405060708090a0b0c0d0e0f";
    std::string dev_s_nwk_int_key = "000102030405060708090a0b0c0d0e0f";
    std::string dev_f_nwk_int_key = "000102030405060708090a0b0c0d0e0f";
    int dev_f_port = 10;
    std::string dev_payload = "packet_1234";
    std::string dp_name = "sample-device-profile";
    std::string gtw_id = "0001020304050607";
    std::string gp_name = "sample-gateway-profile";
    int gp_bandwidth = 125;
    int gp_frequency = 900000000;
    std::vector<int> gp_spreading_factors = {7, 8, 9, 10, 11, 12};
    std::string admin_username = "admin";
    std::string admin_password = "admin";
    std::string api_key_name = "sample-api-key";
    std::string mc_name = "sample-multicast-group";
    std::string mc_address = "0a0b0c0d";
    std::string mc_app_s_key = "0f0e0d0c0b0a09080706050403020100";
    std::string mc_nwk_s_key = "0f0e0d0c0b0a09080706050403020100";
    std::string ns_name = "sample-network-server";
    std::string ns_server = "0.0.0.0:8500";
    std::string org_name = "sample-organization";
    std::string org_display_name = "Sample Organization";
    std::string sp_name = "sample-service-profile";
    std::string usr_username = "sample@user.com";
    std::string usr_password = "password";
    test_config();
    void parse();
};

test_config& test_config();