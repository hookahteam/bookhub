#pragma once

#include <optional>
#include <chrono>
#include <sstream>
#include <string>

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "bcrypt/BCrypt.hpp"
#include "cppcodec/base64_url.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class AuthManager
{
private:
    std::string secretKey;
    int workload;
    int expTimeMinutes;

public:
    AuthManager();
    AuthManager(const std::string& secret, int load, int time);

    // helper functions
    std::vector<uint8_t>        hmacSHA256(const std::string& key, const std::string& data);

    bool verifyHeader(std::string_view header_b64);
    bool verifyPayload(std::string_view payload_b64);
    bool verifySignature(std::string_view signature_b64);
    
    // main functions
    std::string         hashPassword(const std::string& plain);
    bool                verifyPassword(const std::string& plain, const std::string& storedHash);
    std::string         generateToken(int userId, bool admin);
    std::optional<int>  validateToken(std::string_view token);
};
