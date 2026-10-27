#pragma once

#include <stdexcept>
#include <string>

#include <sqlite3.h>

class DatabaseException : public std::runtime_error {
public:
    explicit DatabaseException(const std::string& message)
        : std::runtime_error(message) {}
};

class Database {
public:
    explicit Database(const std::string& filename);
    ~Database();

    void init();
    void addAccount(const std::string& owner, double balance);
    void listAccounts() const;

private:
    sqlite3* db_;

    static std::string trim(const std::string& text);
    void checkError(int rc, const std::string& context) const;
};
