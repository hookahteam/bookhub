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
        pqxx::result res = db->execParams(
            "INSERT INTO USERS (username, email, password_hash) "
            "VALUES (LOWER($1), LOWER($2), $3) "
            "ON CONFLICT DO NOTHING "
            "RETURNING id, username, email, password_hash;",
            {username, email, password_hash});
        
        if (res.empty()) {
            return {std::nullopt, false, UserError::UserAlreadyExists};
        }

        pqxx::row row = res[0];

        if (row["id"].is_null()) {
            std::cerr << "База вернула ID пользователя NULL" << std::endl;
            return {std::nullopt, false, UserError::UserAlreadyExists};
        }

        return {std::make_optional<User>(
            row["id"].as<int>(),
            row["username"].as<std::string>(), 
            row["email"].as<std::string>()),
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
    pqxx::result res = db->execParams(
        "SELECT id, username, email, password_hash, role FROM users "
        "WHERE id = $1;",
        {id});

    if (res.empty()) {return std::nullopt;}

    pqxx::row row = res[0];

    User user = User(
        row["id"].as<int>(), 
        row["username"].as<std::string>(), 
        row["email"].as<std::string>(),
        row["password_hash"].as<std::string>(),
        row["role"].as<std::string>()
    );

    return user;
}


std::optional<User> UserRepository::getByUsername(const std::string& username)
{
    pqxx::result res = db->execParams(
        "SELECT id, username, email FROM users "
        "WHERE username = LOWER($1);",
        {username});
    
    if (res.empty()) {return std::nullopt;}

    pqxx::row row = res[0];

    User user = User(
        row["id"].as<int>(), 
        row["username"].as<std::string>(), 
        row["email"].as<std::string>());

    return user;
}

std::optional<User> UserRepository::getByEmail(const std::string& email)
{
    pqxx::result res = db->execParams(
        "SELECT id, username, email FROM users "
        "WHERE email = LOWER($1);",
        {email});
    
    if (res.empty()) {return std::nullopt;}

    pqxx::row row = res[0];

    User user = User(
        row["id"].as<int>(), 
        row["username"].as<std::string>(), 
        row["email"].as<std::string>());

    return user;
}