#include "Database.h"
#include <iostream>

Database::Database(const std::string& filename) : db(nullptr)
{
    sqlite3_open(filename.c_str(), &db);
}

Database::~Database()
{
    sqlite3_close(db);
}

void Database::init()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "owner TEXT,"
        "balance REAL);";

    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}

void Database::addAccount(const std::string& owner, double balance)
{
    const char* sql =
        "INSERT INTO accounts (owner, balance) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, owner.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, balance);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void Database::listAccounts()
{
    const char* sql = "SELECT id, owner, balance FROM accounts;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::cout
            << "ID: " << sqlite3_column_int(stmt, 0)
            << " | Owner: " << sqlite3_column_text(stmt, 1)
            << " | Balance: " << sqlite3_column_double(stmt, 2)
            << std::endl;
    }

    sqlite3_finalize(stmt);
}
