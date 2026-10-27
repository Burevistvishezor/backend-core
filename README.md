# backend-core

A small C++ backend project demonstrating SQLite persistence, prepared statements, and a clean project structure using CMake.

## Overview

backend-core is a lightweight example of a banking-style backend built in C++. It shows how to:
- connect to a SQLite database
- execute prepared SQL statements
- store and retrieve account records
- keep the project organized using a simple clean architecture-inspired layout
- build the project with CMake

This project is intended as a learning and demonstration project for:
- C++ application design
- SQLite integration
- database-backed CRUD development
- CMake-based project setup

## Features

- SQLite database integration
- Prepared SQL statements for safe queries
- Account creation and listing
- Simple CRUD-style data operations
- Modern CMake configuration
- Minimal dependencies and easy local setup

## Tech Stack

- C++
- SQLite3
- CMake

## Project Structure

```text
backend-core/
├── CmakeLists.txt
├── LICENSE
├── README.md
├── .gitignore
├── src/
│   ├── Database.h
│   ├── Database.cpp
│   └── main.cpp
└── build/
```

## Requirements

Before building, make sure you have:

- A C++17-compatible compiler
- CMake 3.16 or newer
- SQLite development libraries

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential cmake sqlite3 libsqlite3-dev
```

## Quick Start

```bash
git clone https://github.com/Burevistvishezor/backend-core.git
cd backend-core
mkdir -p build
cd build
cmake ..
make
./bank_sqlite
```

## Usage

Run the generated binary from the build directory and use the interactive menu to:
- create accounts
- store data in SQLite
- list stored accounts

## Build Notes

The project is configured to use C++17 and links against SQLite via CMake:

```cmake
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
```

## Why This Project

This repository is a practical example of:
- database-backed backend logic in C++
- handling SQLite operations cleanly
- building a small but realistic backend project
- creating a public open-source project with a simple structure

## Contributing

Contributions are welcome.

If you want to contribute:
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Open a pull request with a clear description

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Author

Burevistvishezor
