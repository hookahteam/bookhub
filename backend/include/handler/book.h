#pragma once

#include "../models/book.h"

#include "../types.h"

class BookHandler 
{
public:
    BookHandler(const std::string &basePath);
    void registerRoutes(App &app);

private:
    // list takes full request, cause we need specific page, limit etc.
    crow::response list(const crow::request &req);
    crow::response get(int id);
    // crow::response create(const crow::request &req);
    // crow::response update(int id, const crow::request &req);
    // crow::response remove(int id);

    std::string basePath_;
    std::unordered_map<int, Book> books_;
    int last_id_;
};