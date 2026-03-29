#pragma once

#include "interface.hpp"

#include <string>

class BaseHandler : public IHandler
{
public:
    explicit BaseHandler(const std::string &basePath);

protected:
    std::string basePath_;

    // Utility functions
    static crow::response bad_request(const std::string &message);
    static crow::response not_found(const std::string &message);
    static crow::response internal(const std::string &message);

};