cmake_minimum_required(VERSION 3.16)
project(bookhub LANGUAGES CXX)

# Стандарты C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

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
	GIT_TAG 	master
)

FetchContent_MakeAvailable(Crow)

add_executable(bookhub 
	src/main.cpp
)

target_link_libraries(bookhub PUBLIC
	Crow::Crow
	Threads::Threads
)

# Где компилятору искать заколовочные файлы
target_include_directories(bookhub PUBLIC 
	include
	${PROJECT_SOURCE_DIR}/include
	${asio_SOURCE_DIR}/asio/include	
)

# Опции компиляции
if(MSVC)
	target_compile_options(bookhub PUBLIC /W4)
else()
	target_compile_options(bookhub PUBLIC -Wall -Wextra -O2)
endif()

# Куда класть исполняемый файл
set_target_properties(bookhub PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

