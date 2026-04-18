#pragma once

#include <memory>
#include <vector>
#include <string>

#include "crow.h"
#include "database/database.h"
#include "auth/auth_manager.h"
#include "repository/user.h"
#include "handler/user.h"
#include "handler/book.h"
#include "handler/interface.h"


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
    std::vector<std::shared_ptr<IHandler>> handlers_;

    // Setup handlers
    void setup();
    void setupStaticRoutes(App &app);
    void addHandler(std::shared_ptr<IHandler> handler);
};
