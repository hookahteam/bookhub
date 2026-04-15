#pragma once

#include "database/database.hpp"
#include "models/user.hpp"

class UserRepository
{
private:
    std::shared_ptr<Database> db;

public:
    UserRepository(std::shared_ptr<Database> db);

    RegisterResult  create(int id, const std::string& username, const std::string& email);
    LoginResult     getbyid(int id);
    std::vector<User> list();
};