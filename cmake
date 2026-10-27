cmake_minimum_required(VERSION 3.16)
project(bank_sqlite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SQLite3 REQUIRED)

add_executable(bank_sqlite
    src/main.cpp
    src/Database.cpp
)

target_include_directories(bank_sqlite PRIVATE src)
target_link_libraries(bank_sqlite PRIVATE SQLite::SQLite3)
