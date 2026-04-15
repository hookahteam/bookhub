#include "database/database.hpp"

Database::Database(const std::string& db_name)
    :cx(std::format("dbname={}", db_name))
{
 
}

Database::~Database()
{

}

pqxx::result Database::init()
{
    pqxx::work tx(cx);
    pqxx::result res = tx.exec(
        "CREATE TABLE IF NOT EXISTS users("
        "id INT PRIMARY KEY NOT NULL,"
        "username VARCHAR(64) NOT NULL,"
        "first_name VARCHAR(64)"
        "last_name VARCHAR(64)"
        "email VARCHAR(64) NOT NULL);");

    tx.commit();
    return res;
}

pqxx::result Database::exec(const std::string& query)
{
    pqxx::work tx(cx);
    pqxx::result res = tx.exec(query);
    tx.commit();
    return res;
}

pqxx::result Database::execParams(const std::string& query, const pqxx::params& params)
{
    pqxx::work tx(cx);
    pqxx::result res = tx.exec_params(query, params);
    tx.commit();
    return res;
}