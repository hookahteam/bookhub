#pragma once

#include <optional>
#include <chrono>

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
    AuthManager(const std::string& secret, int load, int time);

    std::vector<uint8_t> hmacSHA256(const std::string& key, const std::string& data);
    
    std::string         hashPassword(const std::string& plain);
    bool                verifyPassword(const std::string& plain, const std::string& storedHash);
    std::string         generateToken(int userId, bool admin);
    std::optional<int>  validateToken(const std::string& token);
};
