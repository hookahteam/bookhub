#pragma once

#include "crow.h"

class IHandler
{
public:
    virtual void registerRoutes(crow::SimpleApp &app) = 0;

};