#pragma once

#include <unordered_map>
#include <mutex>

#include "base.hpp"
#include "user.hpp"

class UserHandler : public BaseHandler
{
public:
    UserHandler(const std::string &basePath);
    void registerRoutes(crow::SimpleApp &app);

private:
    // list takes full request, cause we need specific page, limit etc.
    crow::response list(const crow::request &req); 
    crow::response get(int id);
    crow::response create(const crow::request &req);
    crow::response update(int id, const crow::request &req);
    crow::response remove(int id);

    std::unordered_map<int, User> users_;
};