#include "auth/auth_manager.h"


using b64 = cppcodec::base64_url;

AuthManager::AuthManager()
{
}

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
    std::string signing_input = b64::encode(header.dump()) + '.' + b64::encode(payload.dump());
    
    // getting signature
    std::vector<uint8_t> hmac_out = hmacSHA256(secretKey, signing_input);
    std::string signature_b64 = b64::encode(hmac_out);

    return signing_input + "." + signature_b64;
}

bool AuthManager::verifyHeader(std::string_view header_b64)
{
    std::vector<uint8_t> json_str = b64::decode(header_b64);
    json header = json::parse(json_str);

    if (header["alg"] != "HS256" || header["typ"] != "JWT") {
        return false;
    }
    return true;
}

bool AuthManager::verifyPayload(std::string_view payload_b64)
{
    std::vector<uint8_t> json_str = b64::decode(payload_b64);
    json payload = json::parse(json_str);

}

bool AuthManager::verifySignature(std::string_view signature_b64)
{

}

std::optional<int> AuthManager::validateToken(std::string_view token)
{
    if (token.empty()) {return std::nullopt;}

    size_t dot1 = token.find('.');
    if (dot1 == std::string_view::npos) return std::nullopt;
    size_t dot2 = token.find('.', dot1+1);
    if (dot2 == std::string_view::npos) return std::nullopt;


    // getting all separate parts
    std::string_view header_b64     = token.substr(0, dot1);
    std::string_view payload_b64    = token.substr(dot1 + 1, dot2 - dot1 - 1);
    std::string_view signature_b64  = token.substr(dot2 + 1);


    // verifying signature
    std::string signing_input = std::string(header_b64) + '.' + std::string(payload_b64);
    
    std::vector<uint8_t> hmac_out = hmacSHA256(secretKey, signing_input);
    std::string true_signature_b64 = b64::encode(hmac_out);

    if (signature_b64 != true_signature_b64) {return std::nullopt;}


    // decoding header and payload
    std::vector<uint8_t> header_json_str = b64::decode(header_b64);
    json header = json::parse(header_json_str);

    std::vector<uint8_t> payload_json_str = b64::decode(payload_b64);
    json payload = json::parse(payload_json_str);


    // verifying info
    if (header["alg"] != "HS256" || header["typ"] != "JWT") {return std::nullopt;}
    
    auto now = std::chrono::system_clock::now();
    int64_t now_time = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    
    if (payload["exp"] <= now_time) {return std::nullopt;}

    // type check for safety
    if (!payload.contains("sub") || !payload["sub"].is_number_unsigned()) {return std::nullopt;}

    // if all good, return userId from payload
    return payload["sub"].get<unsigned int>();
}