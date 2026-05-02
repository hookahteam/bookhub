#pragma once

#include "repository/user.h"
#include "auth/auth_manager.h"

#include "../types.h"

class UserHandler 
{
public:
    UserHandler(
        const std::string &basePath, 
        std::shared_ptr<UserRepository> userRepo, 
        std::shared_ptr<AuthManager> authManager);
    void registerRoutes(App &app);

private:
    // list takes full request, cause we need specific page, limit etc.
    crow::response login(const crow::request& req);
    crow::response reg(const crow::request& req);
    crow::response list(const crow::request& req); 
    crow::response get(int id);
    // crow::response update(int id, const crow::request &req);
    // crow::response remove(int id);

    std::string basePath_;
    std::shared_ptr<UserRepository> userRepo;
    std::shared_ptr<AuthManager> authManager;
};
