#include "database/database.h"

Database::Database(const std::string& db_name)
    :cx(std::format("dbname={}", db_name))
{
    init();
}

Database::~Database()
{

}

pqxx::result Database::init()
{
    pqxx::work tx(cx);
    pqxx::result res = tx.exec(
        "CREATE TABLE IF NOT EXISTS users("
        "id             SERIAL      PRIMARY KEY,"
        "username       VARCHAR(64) UNIQUE NOT NULL,"
        "email          VARCHAR(64) UNIQUE NOT NULL,"
        "password_hash  TEXT        NOT NULL,"
        "role           VARCHAR(20) DEFAULT 'user' NOT NULL);"
    );

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