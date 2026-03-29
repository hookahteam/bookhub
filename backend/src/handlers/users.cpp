#include "users.hpp"

UserHandler::UserHandler(const std::string &basePath)
    : BaseHandler(basePath)
{
    // Init mock data
    this->last_id_ = 0;

    this->last_id_ += 1;
    this->users_[this->last_id_] = User{1, "John Doe", "john@example.com"};
    this->last_id_ += 1;
    this->users_[this->last_id_] = User{1, "Jone Doe", "jane@example.com"};
}

crow::response UserHandler::list(const crow::request &req)
{
    // Get search query
    const char *q = req.url_params.get("q") != nullptr ? req.url_params.get("q") : ""; 

    int page = 1;
    int limit = 10;

    const char *pageParam = req.url_params.get("page") != nullptr ? req.url_params.get("page") : "1";
    const char *limitParam = req.url_params.get("limit") != nullptr ? req.url_params.get("page") : "1";

    page = std::stoi(pageParam);
    limit = std::stoi(limitParam);

    std::cout << "Q: " << q << " Page and Limit: " << page << " " << limit << "\n";

    crow::json::wvalue resp;
    crow::json::wvalue::list users;

    for (auto &user : this->users_)
    {
        crow::json::wvalue userJson;
        userJson["id"] = user.second.id;
        userJson["username"] = user.second.username;
        userJson["email"] = user.second.email;

        users.push_back(std::move(userJson));
    }

    resp["users"] = std::move(users);

    return crow::response(crow::OK, resp);
}

crow::response UserHandler::get(int id)
{

}

crow::response UserHandler::create(const crow::request &req)
{

}

crow::response UserHandler::update(int id, const crow::request &req)
{

}

crow::response UserHandler::remove(int id)
{}

void UserHandler::registerRoutes(App &app)
{

}