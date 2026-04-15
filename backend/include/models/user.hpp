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
};

struct LoginResult {
    bool success = false;
    UserError error = UserError::None;
};

struct RegisterResult {
    bool success = false;
    UserError error = UserError::None;
}