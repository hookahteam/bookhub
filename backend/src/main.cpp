#include "crow.h"

int main()
{
    crow::SimpleApp app;


    CROW_ROUTE(app, "/add/<int>/<int>/") 
    ([](int a, int b){
        return a + b;
    });

    app.port(3000).multithreaded().run();
}
