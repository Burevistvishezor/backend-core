#pragma once
#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& filename);
    ~Database();

    void init();
    void addAccount(const std::string& owner, double balance);
    void listAccounts();

private:
    sqlite3* db;
};
