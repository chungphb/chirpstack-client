//
// Created by vht on 6/24/21.
//

#pragma once

#include <cstdint>

const char* APPLICATION_SERVER = "localhost:8080";
const char* JWT_TOKEN =
        "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiMWZmZTRjYzgtODMwZi00MGM0LTlhMzAtYTE5Nz"
        "dkNjU2N2MyIiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYyMzc1NDQzMSwic3ViIjoiYXBpX2tleSJ9.f--PhXYG"
        "c61Kq_eMdf-ofxX8RUmNCDmtP9mauhzpq7k";
const char* SERVICE_PROFILE_ID = "a3bdf1e5-7d10-4191-8f70-5cf7d446a0b2";
const char* APPLICATION_NAME = "sample-application";
const char* DEVICE_PROFILE_NAME = "sample-device-profile";
const char* GATEWAY_PROFILE_NAME = "sample-gateway-profile";
const char* DEVICE_EUI = "0001020304050607";
const char* NWK_KEY = "000102030405060708090a0b0c0d0e0f";
const char* APP_KEY = "000102030405060708090a0b0c0d0e0f";
const char* DEVICE_ADDRESS = "00010203";
const char* APP_S_KEY = "000102030405060708090a0b0c0d0e0f";
const char* NWK_S_ENC_KEY = "000102030405060708090a0b0c0d0e0f";
const char* S_NWK_INT_KEY = "000102030405060708090a0b0c0d0e0f";
const char* F_NWK_INT_KEY = "000102030405060708090a0b0c0d0e0f";
const uint32_t F_PORT = 10;
const char* PAYLOAD = "packet_1234";
const char* GATEWAY_ID = "0001020304050607";
const char* GLOBAL_JWT_TOKEN =
        "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcGlfa2V5X2lkIjoiMDAxODQ2MDgtOWI0My00MjZkLWIyOGQ"
        "tNDBlM2I3Y2MwZmU1IiwiYXVkIjoiYXMiLCJpc3MiOiJhcyIsIm5iZiI6MTYyNDUzMzQ5NCwic3ViIjoiYXBpX2t"
        "leSJ9.LjLtatoAuOuab7hXMbhpXZuw8iPGQCt2lpTB1fEktVQ";
const uint32_t FREQUENCY = 900000000;
const uint32_t BANDWIDTH = 125;
const uint32_t SPREADING_FACTORS[] = {7, 8, 9, 10, 11, 12};
const char* USER = "sample@user.com";
const char* PASSWORD = "password";
const char* ORGANIZATION_NAME = "sample-organization";
const char* ORGANIZATION_DISPLAY_NAME = "Sample Organization";
const char* NETWORK_SERVER_NAME = "sample-network-server";
const char* NETWORK_SERVER_SERVER = "0.0.0.0:8500";
const char* SERVICE_PROFILE_NAME = "sample-service-profile";
const char* MULTICAST_GROUP_NAME = "sample-multicast-group";
const char* MULTICAST_ADDRESS = "0a0b0c0d";
const char* MC_NWK_S_KEY = "0f0e0d0c0b0a09080706050403020100";
const char* MC_APP_S_KEY = "0f0e0d0c0b0a09080706050403020100";