cmake_minimum_required(VERSION 3.16)
project(bookhub LANGUAGES CXX)

# Стандарты C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(OpenSSL REQUIRED)

include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external")

message(STATUS "Fetching Asio...")
# Asio - зависимость Crow
FetchContent_Declare(
	asio
	GIT_REPOSITORY 	https://github.com/chriskohlhoff/asio.git
	GIT_TAG 		asio-1-38-0
)
FetchContent_MakeAvailable(asio)

set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include CACHE PATH "ASIO include directory")

message(STATUS "Fetching Crow...")
# Crow - header-only, добавляется через include
FetchContent_Declare(
	Crow
	GIT_REPOSITORY 	https://github.com/CrowCpp/Crow.git
	GIT_TAG 		master
)
FetchContent_MakeAvailable(Crow)

message(STATUS "Fetching bcrypt...")
# bcrypt для хеширования паролей
FetchContent_Declare(
	libbcrypt
	GIT_REPOSITORY 	https://github.com/trusch/libbcrypt
	GIT_TAG			master
)
FetchContent_MakeAvailable(libbcrypt)

message(STATUS "Fetching cppcodec...")
# cppcodec для кодирования токенов в base64url
FetchContent_Declare(
	cppcodec	
	GIT_REPOSITORY  https://github.com/tplgy/cppcodec.git
	GIT_TAG			master
)
FetchContent_MakeAvailable(cppcodec)

message(STATUS "Fetching nlohmann/json...")
# nlohmann/json для сериализации и парсинга json
FetchContent_Declare(
	nlohmann	
	GIT_REPOSITORY  https://github.com/nlohmann/json.git
	GIT_TAG			master
)
FetchContent_MakeAvailable(nlohmann)

set(PQXX /usr/local/include/pqxx)
find_library(PQXX_LIB pqxx)

add_executable(bookhub 
	src/main.cpp
	src/server.cpp
	src/database/database.cpp
	src/repository/user.cpp
	src/auth/auth_manager.cpp
	src/auth/auth_middleware.cpp
	src/handler/user.cpp
	src/handler/book.cpp
)

target_link_libraries(bookhub PUBLIC
	Crow::Crow
	Threads::Threads
	PostgreSQL::PostgreSQL
	OpenSSL::SSL
	bcrypt
	${PQXX_LIB}	
)

# Где компилятору искать заколовочные файлы
target_include_directories(bookhub PUBLIC 
	include
	${PROJECT_SOURCE_DIR}/include
	${asio_SOURCE_DIR}/asio/include	
	${PostgreSQL_INCLUDE_DIRS}
	${bcrypt_SOURCE_DIR}/include
	${cppcodec_SOURCE_DIR}
	${nlohmann_SOURCE_DIR}/include
)

# Опции компиляции
if(MSVC)
	target_compile_options(bookhub PUBLIC /W4)
else()
	target_compile_options(bookhub PUBLIC -O2)
endif()

# Куда класть исполняемый файл
set_target_properties(bookhub PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

