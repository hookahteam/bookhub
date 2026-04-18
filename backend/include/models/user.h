#pragma once

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
    std::string password_hash;
    std::string role = "user";
};

struct LoginResult {
    bool success = false;
    UserError error = UserError::None;
};

struct RegisterResult {
    int userId = 0;
    bool success = false;
    UserError error = UserError::None;
};