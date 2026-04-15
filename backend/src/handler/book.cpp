#include "handler/book.hpp"

BookHandler::BookHandler(const std::string &basePath)
    : BaseHandler(basePath)
{
    // Init mock data
    this->last_id_ = 0;

    this->last_id_ += 1;
    this->books_[last_id_] = Book{"50 оттенков серого", "Артем Меднов", 2012, last_id_};
    this->last_id_ += 1;
    this->books_[last_id_] = Book{"Майнкрафт строим вместе", "Роман Леднев", 2017, last_id_};
}

crow::response BookHandler::list(const crow::request &req)
{
    const char *q = req.url_params.get("q") != nullptr ? req.url_params.get("q") : "";

    crow::json::wvalue resp;
    crow::json::wvalue::list books;

    for (auto &book : this->books_)
    {
        crow::json::wvalue bookJson;
        bookJson["id"] = book.second.id;
        bookJson["title"] = book.second.title;
        bookJson["author"] = book.second.author;
        bookJson["year"] = book.second.year;

        books.push_back(bookJson);
    }

    resp["books"] = std::move(books);

    return crow::response(crow::OK, resp);
}

crow::response BookHandler::get(int id)
{
    if (this->books_.find(id) == this->books_.end()) {
        return this->not_found("Book not found");
    }

    Book book = this->books_[id];
    crow::json::wvalue bookJson;
    bookJson["id"] = book.id;
    bookJson["title"] = book.title;
    bookJson["author"] = book.author;
    bookJson["year"] = book.year;

    return crow::response(crow::OK, bookJson);
}

void BookHandler::registerRoutes(App &app)
{
    app.route_dynamic(this->basePath_)
        .methods(crow::HTTPMethod::GET) (
            [this](const crow::request &req)
            {
                return this->list(req);
            });
    
    app.route_dynamic(this->basePath_ + "/<int>")
        .methods(crow::HTTPMethod::GET) (
            [this](const crow::request &req, int id)
            {
                return this->get(id);
            });        
}