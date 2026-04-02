#include "server.hpp"

Server::Server(const ServerConfig &config): config_(config)
{
    // Set up logging level
    if (this->config_.log_level == "debug") 
    {
        crow::logger::setLogLevel(crow::LogLevel::DEBUG);
    }
    else if (this->config_.log_level == "info")
    {
        crow::logger::setLogLevel(crow::LogLevel::INFO);
    }
    else if (this->config_.log_level == "warning")
    {
        crow::logger::setLogLevel(crow::LogLevel::WARNING);
    }
    else if (this->config_.log_level == "error")
    {
        crow::logger::setLogLevel(crow::LogLevel::ERROR);
    }
    else if (this->config_.log_level == "critical")
    {
        crow::logger::setLogLevel(crow::LogLevel::CRITICAL);
    }
    else
    {
        crow::logger::setLogLevel(crow::LogLevel::INFO);
    }

    // App init
    this->app_ = std::make_unique<App>();

    // Config cors
    if (this->config_.cors){
        auto &cors = this->app_->get_middleware<crow::CORSHandler>();
    
        cors
            .global()
            .methods(
                    crow::HTTPMethod::GET,
                    crow::HTTPMethod::POST,
                    crow::HTTPMethod::PUT,
                    crow::HTTPMethod::DELETE,
                    crow::HTTPMethod::OPTIONS)
            .headers("", "")
            .origin(this->config_.corsOrigin)
            .prefix("/api/")
            .max_age(3600);
    }
}

void Server::setup()
{
    // add handlers
    this->addHandler(std::make_shared<UserHandler>("/api/users"));

    setupStaticRoutes(*this->app_);
}

void Server::setupStaticRoutes(App &app)
{
    app.route_dynamic("/")
        .methods(crow::HTTPMethod::GET)(
            [this](const crow::request &req, crow::response &res) {
                res.set_static_file_info("front/index.html");
                res.end();
            });

    app.route_dynamic("/static/<string>/<string>")
        .methods(crow::HTTPMethod::GET)(
            [](const crow::request &req, crow::response &res, std::string folder, std::string file) {
                std::string full_path = "front/static/" + folder + "/" + file;
                res.set_static_file_info(full_path);
                res.end();
            });

}

void Server::addHandler(std::shared_ptr<IHandler> handler)
{
    this->handlers_.push_back(handler);
    handler->registerRoutes(*this->app_);
}

void Server::start()
{
    this->setup();
    this->app_->port(this->config_.port)
        .multithreaded()
        .concurrency(this->config_.threads)
        .run_async();
} 
