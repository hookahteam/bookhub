#include "repository/user.h"

UserRepository::UserRepository(std::shared_ptr<Database> db_) 
    : db(db_)
{
}

RegisterResult UserRepository::create(
        const std::string& username, 
        const std::string& email, 
        const std::string& password_hash 
    )
{
    try {
        pqxx::row row = db->execParams(
            "INSERT INTO USERS (username, email, password_hash) "
            "VALUES (LOWER($1), LOWER($2), $3) "
            "RETURNING id, username, email, password_hash;",
            {username, email, password_hash}).begin();
        
        if (row.empty()) {
            return {std::nullopt, false, UserError::UserAlreadyExists};
        }
        return {std::make_optional<User>(
            row[0].as<int>(), 
            row[1].as<std::string>(), 
            row[2].as<std::string>()), 
            true, 
            UserError::None};
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl;
        return {std::nullopt, false, UserError::DatabaseError};
    }
}

std::optional<User> UserRepository::getById(int id)
{
    pqxx::row row = db->execParams(
        "SELECT id, username, email, password_hash, role FROM users "
        "WHERE id = $1;",
        {id}).begin();

    if (row.empty()) {return std::nullopt;}

    User user = User(
        row[0].as<int>(), 
        row[1].as<std::string>(), 
        row[2].as<std::string>(),
        row[3].as<std::string>(),
        row[4].as<std::string>()
    );

    return user;
}


std::optional<User> UserRepository::getByUsername(const std::string& username)
{
    pqxx::row row = db->execParams(
        "SELECT id, username, email FROM users "
        "WHERE LOWER(username) = $1;",
        {username}).begin();
    
    if (row.empty()) {return std::nullopt;}

    User user = User(
        row[0].as<int>(), 
        row[1].as<std::string>(), 
        row[2].as<std::string>());

    return user;
}

std::optional<User> UserRepository::getByEmail(const std::string& email)
{
    pqxx::row row = db->execParams(
        "SELECT id, username, email FROM users "
        "WHERE LOWER(email) = $1;",
        {email}).begin();
    
    if (row.empty()) {return std::nullopt;}

    User user = User(
        row[0].as<int>(), 
        row[1].as<std::string>(), 
        row[2].as<std::string>());

    return user;
}