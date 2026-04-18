#pragma once

#include "auth_manager.h"

class AuthMiddleware
{
private:
    std::shared_ptr<AuthManager> authManager = nullptr;

public:
};