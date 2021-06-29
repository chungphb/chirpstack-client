#include "test_config.h"
#include <toml/toml.h>

test_config::test_config() {
    parse();
}

void test_config::parse() {
    // Parse config
    std::ifstream ifs("test_config.toml");
    toml::ParseResult res = toml::parse(ifs);
    if (!res.valid()) {
        throw std::runtime_error("Config file not exists");
    }
    const toml::Value& config = res.value;

    // General config

    const toml::Value* val = config.find("general.application_server");
    if (val && val->is<std::string>()) {
        application_server = val->as<std::string>();
    } else {
        throw std::runtime_error("Invalid application server");
    }

    val = config.find("test.jwt_token");
    if (val && val->is<std::string>()) {
        jwt_token = val->as<std::string>();
    } else {
        throw std::runtime_error("Invalid JWT token");
    }

    val = config.find("test.service_profile_id");
    if (val && val->is<std::string>()) {
        service_profile_id = val->as<std::string>();
    } else {
        throw std::runtime_error("Invalid service-profile ID");
    }

    val = config.find("test.global_jwt_token");
    if (val && val->is<std::string>()) {
        global_jwt_token = val->as<std::string>();
    } else {
        throw std::runtime_error("Invalid global JWT token");
    }

    // Application test config

    val = config.find("test.application.name");
    if (val && val->is<std::string>()) {
        app_name = val->as<std::string>();
    }

    // Device test config

    val = config.find("test.device.eui");
    if (val && val->is<std::string>()) {
        dev_eui = val->as<std::string>();
    }

    val = config.find("test.device.nwk_key");
    if (val && val->is<std::string>()) {
        dev_nwk_key = val->as<std::string>();
    }

    val = config.find("test.device.app_key");
    if (val && val->is<std::string>()) {
        dev_app_key = val->as<std::string>();
    }

    val = config.find("test.device.address");
    if (val && val->is<std::string>()) {
        dev_address = val->as<std::string>();
    }

    val = config.find("test.device.app_s_key");
    if (val && val->is<std::string>()) {
        dev_app_s_key = val->as<std::string>();
    }

    val = config.find("test.device.nwk_s_enc_key");
    if (val && val->is<std::string>()) {
        dev_nwk_s_enc_key = val->as<std::string>();
    }

    val = config.find("test.device.s_nwk_int_key");
    if (val && val->is<std::string>()) {
        dev_s_nwk_int_key = val->as<std::string>();
    }

    val = config.find("test.device.f_nwk_int_key");
    if (val && val->is<std::string>()) {
        dev_f_nwk_int_key = val->as<std::string>();
    }

    val = config.find("test.device.f_port");
    if (val && val->is<int>()) {
        dev_f_port = val->as<int>();
    }

    val = config.find("test.device.payload");
    if (val && val->is<std::string>()) {
        dev_payload = val->as<std::string>();
    }

    // Device-profile test

    val = config.find("test.device_profile.name");
    if (val && val->is<std::string>()) {
        dp_name = val->as<std::string>();
    }

    // Gateway test

    val = config.find("test.gateway.id");
    if (val && val->is<std::string>()) {
        gtw_id = val->as<std::string>();
    }

    // Gateway-profile test

    val = config.find("test.gateway_profile.name");
    if (val && val->is<std::string>()) {
        gp_name = val->as<std::string>();
    }

    val = config.find("test.gateway_profile.bandwidth");
    if (val && val->is<int>()) {
        gp_bandwidth = val->as<int>();
    }

    val = config.find("test.gateway_profile.frequency");
    if (val && val->is<int>()) {
        gp_frequency = val->as<int>();
    }

    val = config.find("test.gateway_profile.spreading_factors");
    if (val && val->is<toml::Array>()) {
        for (const toml::Value& s_factor : val->as<toml::Array>()) {
            if (s_factor.is<int>()) {
                gp_spreading_factors.push_back(s_factor.as<int>());
            }
        }
    }

    // Internal test

    val = config.find("test.internal.admin_username");
    if (val && val->is<std::string>()) {
        admin_username = val->as<std::string>();
    }

    val = config.find("test.internal.admin_password");
    if (val && val->is<std::string>()) {
        admin_password = val->as<std::string>();
    }

    val = config.find("test.internal.api_key_name");
    if (val && val->is<std::string>()) {
        api_key_name = val->as<std::string>();
    }

    // Multicast-group test

    val = config.find("test.multicast_group.name");
    if (val && val->is<std::string>()) {
        mc_name = val->as<std::string>();
    }

    val = config.find("test.multicast_group.address");
    if (val && val->is<std::string>()) {
        mc_address = val->as<std::string>();
    }

    val = config.find("test.multicast_group.app_s_key");
    if (val && val->is<std::string>()) {
        mc_app_s_key = val->as<std::string>();
    }

    val = config.find("test.multicast_group.nwk_s_key");
    if (val && val->is<std::string>()) {
        mc_nwk_s_key = val->as<std::string>();
    }

    // Network-server test

    val = config.find("test.network_server.name");
    if (val && val->is<std::string>()) {
        ns_name = val->as<std::string>();
    }

    val = config.find("test.network_server.server");
    if (val && val->is<std::string>()) {
        ns_server = val->as<std::string>();
    }

    // Organization test

    val = config.find("test.organization.name");
    if (val && val->is<std::string>()) {
        org_name = val->as<std::string>();
    }

    val = config.find("test.organization.display_name");
    if (val && val->is<std::string>()) {
        org_display_name = val->as<std::string>();
    }

    // Service-profile test

    val = config.find("test.service_profile.name");
    if (val && val->is<std::string>()) {
        sp_name = val->as<std::string>();
    }

    // User test

    val = config.find("test.user.username");
    if (val && val->is<std::string>()) {
        usr_username = val->as<std::string>();
    }

    val = config.find("test.user.password");
    if (val && val->is<std::string>()) {
        usr_password = val->as<std::string>();
    }
}

static struct test_config instance;

struct test_config& test_config() {
    return instance;
}