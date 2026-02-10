cmake_minimum_required(VERSION 3.10)
project(bank_sqlite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(bank_sqlite
    src/main.cpp
    src/Database.cpp
)

target_link_libraries(bank_sqlite SQLite::SQLite3)
