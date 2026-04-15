#include "pqxx/pqxx"
#include <iostream>

class Database {
private:
    pqxx::connection cx;

public:
    Database(const std::string& db_name);
    ~Database();

    pqxx::result init();
    pqxx::result exec(const std::string& query);
    pqxx::result execParams(const std::string& query, const pqxx::params& params);
};