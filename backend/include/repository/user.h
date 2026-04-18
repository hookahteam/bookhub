#pragma once

#include "database/database.h"
#include "models/user.h"

class UserRepository
{
private:
    std::shared_ptr<Database> db;

public:
    UserRepository(std::shared_ptr<Database> db);

    RegisterResult create(
        const std::string& username, 
        const std::string& email, 
        const std::string& password_hash 
    );

    std::optional<User> getById(int id);
    std::optional<User> getByUsername(const std::string& username);
    std::optional<User> getByEmail(const std::string& email);
    std::vector<User>   list();
};