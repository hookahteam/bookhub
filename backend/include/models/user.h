#pragma once

#include <optional>
#include <string>

enum class UserError {
    None,
    UserAlreadyExists,
    InvalidCredentials,
    DatabaseError
};

struct User
{
    int id;
    std::string username;
    std::string email;
    std::string password_hash = "";
    std::string role = "user";
};

struct LoginResult {
    bool success = false;
    UserError error = UserError::None;
};

struct RegisterResult {
    std::optional<User> user = std::nullopt;
    bool success = false;
    UserError error = UserError::None;
};