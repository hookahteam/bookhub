#include "auth/auth_middleware.h"

AuthMiddleware::AuthMiddleware()

{

}

AuthMiddleware::AuthMiddleware(std::shared_ptr<AuthManager> auth)
    : authManager(auth)
{

}

void AuthMiddleware::before_handle(
    crow::request& /*req*/, 
    crow::response& /*res*/, 
    AuthMiddleware::context& /*ctx*/)
{
    // std::string_view path = req.url;

    // std::cout << "Before_handle path: " << path << std::endl;
    
    // if (path.starts_with("/api/my-library"))
    // {
    //     // getting token
    //     std::string_view header = req.get_header_value("Authorization");
    //     if (header.empty() || !header.starts_with("Bearer ")) {
    //         res.code = 401;
    //         res.body = "{\"error\": \"no token\"}";
    //         res.set_header("Content-Type", "application/json");
    //         res.end();
    //         return;
    //     }

    //     std::string_view token = header.substr(7);
        
    //     // validating token
    //     auto user_id = authManager->validateToken(token);
    //     if (!user_id.has_value()) {
    //         res.code = 401;
    //         res.body = "{\"error\": \"invalid token\"}";
    //         res.set_header("Content-Type", "application/json");
    //         res.end();
    //         return;
    //     }

    //     // user_id saved in context
    //     ctx.user_id = user_id.value();
    // }
    // else {
    //     return;
    // }
}

void AuthMiddleware::after_handle(
    crow::request& req, 
    crow::response& res, 
    AuthMiddleware::context& ctx)
{

}