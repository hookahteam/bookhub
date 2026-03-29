#include "crow.h"

int main()
{
    crow::SimpleApp app;


    CROW_ROUTE(app, "/")
    ([](){
        return crow::response(200, "Hello World");
    });



    app.port(3000).multithreaded().run();
}
