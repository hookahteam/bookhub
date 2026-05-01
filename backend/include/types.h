#pragma once

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "auth/auth_middleware.h"

using App = crow::App<crow::CORSHandler, AuthMiddleware>;