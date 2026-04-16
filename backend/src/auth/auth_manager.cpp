#include "auth/auth_manager.h"

using b64 = cppcodec::base64_url;

AuthManager::AuthManager(const std::string& secret, int load, int time)
    : secretKey(secret), workload(load), expTimeMinutes(time)
{
}

std::vector<uint8_t> AuthManager::hmacSHA256(const std::string& key, const std::string& data)
{
    uint8_t hash[32];
    unsigned int hashLen;

    HMAC(
        EVP_sha256(),
        key.data(),
        static_cast<int>(key.size()),
        reinterpret_cast<unsigned char const*>(data.data()),
        static_cast<int>(data.size()),
        hash,
        &hashLen
    );

    return std::vector<uint8_t>(hash, hash+32);
}

std::string AuthManager::hashPassword(const std::string& plain)
{
    return BCrypt::generateHash(plain, workload);
}

bool AuthManager::verifyPassword(const std::string& plain, const std::string& storedHash)
{
    if (BCrypt::generateHash(plain, workload) == storedHash) {return true;}
    return false;
}

std::string AuthManager::generateToken(int userId, bool admin)
{
    // prepairing header
    json header = {
        {"alg", "HS256"},
        {"typ", "JWT"},
    };

    // prepairing payload
    auto now = std::chrono::system_clock::now();
    int64_t iat = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    int64_t exp = iat + expTimeMinutes * 60;

    json payload = {
        {"sub", userId},
        {"admin", admin},
        {"iat", iat},
        {"exp", exp},
    }; 

    // converting both to base64url
    std::string signing_input = b64::encode(header.dump()) + "." + b64::encode(payload.dump());
    
    // getting signature
    std::vector<uint8_t> hmac_out = hmacSHA256(secretKey, signing_input);
    std::string signature_b64 = b64::encode(hmac_out);

    return signing_input + "." + signature_b64;
}

std::optional<int> AuthManager::validateToken(const std::string& token)
{

}