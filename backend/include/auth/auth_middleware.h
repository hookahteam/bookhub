#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "auth_manager.h"

class AuthMiddleware
{
private:
    std::shared_ptr<AuthManager> authManager = nullptr;

public:
    struct context { int user_id = 0; };

    AuthMiddleware();
    AuthMiddleware(std::shared_ptr<AuthManager> auth);
    void before_handle(crow::request& req, crow::response& res, AuthMiddleware::context& ctx);
    void after_handle(crow::request& req, crow::response& res, AuthMiddleware::context& ctx);
};