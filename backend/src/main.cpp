#include "crow.h"

int main()
{
    crow::SimpleApp app;


    CROW_ROUTE(app, "/")
    ([](const crow::request& req){
        return crow::response(200, "Hello World");
    });

    CROW_ROUTE(app, "/<string>")
    ([](const crow::request& req, const std::string &value){
        return crow::response(200, "Hello " + value);
    });

    app.port(8080).multithreaded().run();
}
