#include "handler/user.hpp"

UserHandler::UserHandler(const std::string &basePath, std::shared_ptr<UserRepository> userRepo_)
    : BaseHandler(basePath), userRepo(userRepo_)
{
}

// crow::response UserHandler::list(const crow::request &req)
// {
//     // Get search query
//     const char *q = req.url_params.get("q") != nullptr ? req.url_params.get("q") : ""; 

//     int page = 1;
//     int limit = 10;

//     const char *pageParam = req.url_params.get("page") != nullptr ? req.url_params.get("page") : "1";
//     const char *limitParam = req.url_params.get("limit") != nullptr ? req.url_params.get("page") : "1";

//     page = std::stoi(pageParam);
//     limit = std::stoi(limitParam);

//     std::cout << "Q: " << q << " Page and Limit: " << page << " " << limit << "\n";

//     crow::json::wvalue resp;
//     crow::json::wvalue::list users;

//     for (auto &user : this->users_)
//     {
//         crow::json::wvalue userJson;
//         userJson["id"] = user.second.id;
//         userJson["username"] = user.second.username;
//         userJson["email"] = user.second.email;

//         users.push_back(std::move(userJson));
//     }

//     resp["users"] = std::move(users);

//     return crow::response(crow::OK, resp);
// }

// crow::response UserHandler::get(int id)
// {
//     if (this->users_.find(id) == this->users_.end())
//     {
//         return this->not_found("User not found");
//     }

//     User user = this->users_[id];
//     crow::json::wvalue userJson;
//     userJson["id"] = user.id;
//     userJson["username"] = user.username;
//     userJson["email"] = user.email;

//     return crow::response(crow::OK, userJson);
// }

crow::response UserHandler::create(const crow::request &req)
{
    crow::json::rvalue json = crow::json::load(req.body);
    
    std::string username = json["username"].s(); // .s() converts value to the string
    std::string email = json["email"].s();

    last_id_ += 1;
    auto res = userRepo->create(last_id_, username, email);

    if (res.success) {
        crow::json::wvalue resp;
        resp["id"] = last_id_;
        resp["username"] = username;
        resp["email"] = email;

        return crow::response(crow::CREATED, resp);
    }
    else if (res.error == UserError::UserAlreadyExists) {

    }
    else {
        // 500 Internal server error
    }

}

// crow::response UserHandler::update(int id, const crow::request &req)
// {
//     if (this->users_.find(id) == this->users_.end())
//     {
//         return this->not_found("User not found");
//     }

//     crow::json::rvalue json = crow::json::load(req.body);
    
//     std::string username = json["username"].s(); // .s() converts value to the string
//     std::string email = json["email"].s();

//     this->mutex_.lock();

//     User user = users_[id];
//     user.email = email;
//     user.username = username;
//     this->users_[id] = user;
    
//     this->mutex_.unlock();

//     crow::json::wvalue resp;
//     resp["id"] = user.id;
//     resp["username"] = user.username;
//     resp["email"] = user.email;

//     return crow::response(crow::CREATED, resp);
// }

// crow::response UserHandler::remove(int id)
// {
//     if (this->users_.find(id) == this->users_.end())
//     {
//         return this->not_found("User not found");
//     }

//     this->mutex_.lock();

//     this->users_.erase(id);
    
//     this->mutex_.unlock();

//     crow::json::wvalue resp;
//     resp["success"] = true;


//     return crow::response(crow::OK, resp);
// }

void UserHandler::registerRoutes(App &app)
{
    // app.route_dynamic(this->basePath_)
    //     .methods(crow::HTTPMethod::GET)(
    //         [this](const crow::request &req)
    //         {
    //             return this->list(req);
    //         });

    // app.route_dynamic(this->basePath_ + "/<int>")
    //     .methods(crow::HTTPMethod::GET)(
    //         [this](const crow::request &req, int id)
    //         {
    //             return this->get(id);
    //         });
        
    app.route_dynamic(this->basePath_)
        .methods(crow::HTTPMethod::POST)(
            [this](const crow::request &req)
            {
                return this->create(req);
            });

    // app.route_dynamic(this->basePath_ + "/<int>")
    //     .methods(crow::HTTPMethod::PUT)(
    //         [this](const crow::request &req, int id)
    //         {
    //             return this->update(id, req);
    //         });

    // app.route_dynamic(this->basePath_ + "/<int>")
    //     .methods(crow::HTTPMethod::DELETE)(
    //         [this](const crow::request &req, int id)
    //         {
    //             return this->remove(id);
    //         });    
}
