#pragma once

#include <memory>
#include <vector>
#include <string>

#include "crow.h"
#include "database/database.h"
#include "auth/auth_manager.h"
#include "auth/auth_middleware.h"
#include "repository/user.h"
#include "handler/user.h"
#include "handler/book.h"

#include "types.h"

struct ServerConfig {
    int port = 8080;
    int threads = 2;
    std::string log_level = "info";
    bool cors = true;
    std::string corsOrigin = "*";
};

class Server
{
public:
    explicit Server(const ServerConfig &config = ServerConfig());
 
    void start();

private:
    ServerConfig config_;
    std::unique_ptr<App> app_;

    std::shared_ptr<BookHandler> bookHandler;
    std::shared_ptr<UserHandler> userHandler;

    // Setup handlers
    void setup();
    void setupStaticRoutes(App &app);
};
