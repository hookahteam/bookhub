#include "repository/user.hpp"

RegisterResult UserRepository::create(int id, const std::string& username, const std::string& email)
{
    try {
        pqxx::result result = db->execParams(
            "INSERT INTO USERS (id, username, email)"
            "VALUES ($1, $2, $3)"
            "RETURNING id, username, email;",
            {id, username, email});
        
        if (result.empty()) {
            return {false, UserError::UserAlreadyExists};
        }
        User user = {id, username, email};
        return {true, UserError::None};
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl;
        return {false, UserError::DatabaseError};
    }
}

// UserRepository::getById(int id)
// {
//     pqxx::row row = db->execParams(
//         "SELECT id, name, email FROM users"
//         "WHERE id = $1;",
//         {id}).begin();

//     if (row.empty()) {return std::nullopt;}

//     User user = User(
//         row[0].as<int>(), 
//         row[1].as<std::string>(), 
//         row[2].as<std::string>());

//     return user;
// }