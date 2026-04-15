#pragma once

#include <memory>
#include <vector>
#include <string>

#include "crow.h"
#include "database/database.hpp"
#include "repository/user.hpp"
#include "handler/user.hpp"
#include "handler/book.hpp"
#include "handler/interface.hpp"


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
