#include "Database.h"
#include <iostream>
#include <sstream>
#include <cctype>

Database::Database(const std::string& filename) : db(nullptr)
{
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::string error = "Failed to open database: ";
        error += sqlite3_errmsg(db);
        sqlite3_close(db);
        db = nullptr;
        throw DatabaseException(error);
    }
}

Database::~Database()
{
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Database::checkError(int rc, const std::string& context)
{
    if (rc != SQLITE_OK && rc != SQLITE_ROW && rc != SQLITE_DONE) {
        std::string error = context + ": " + sqlite3_errmsg(db);
        throw DatabaseException(error);
    }
}

void Database::init()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "owner TEXT NOT NULL,"
        "balance REAL NOT NULL CHECK(balance >= 0),"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::string error = "Table creation failed: ";
        if (errMsg) {
            error += errMsg;
            sqlite3_free(errMsg);
        }
        throw DatabaseException(error);
    }
}

// Helper function to trim whitespace from strings
static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

void Database::addAccount(const std::string& owner, double balance)
{
    // Validate input parameters
    std::string trimmedOwner = trim(owner);
    if (trimmedOwner.empty()) {
        throw std::invalid_argument("Owner name cannot be empty");
    }
    
    if (balance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }

    const char* sql =
        "INSERT INTO accounts (owner, balance) VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    checkError(rc, "Failed to prepare statement");

    rc = sqlite3_bind_text(stmt, 1, trimmedOwner.c_str(), -1, SQLITE_TRANSIENT);
    checkError(rc, "Failed to bind owner name");
    
    rc = sqlite3_bind_double(stmt, 2, balance);
    checkError(rc, "Failed to bind balance");

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::string error = "Insert failed: " + std::string(sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        throw DatabaseException(error);
    }
    
    sqlite3_finalize(stmt);
    std::cout << "✓ Account created successfully for " << trimmedOwner 
              << " with balance: $" << balance << std::endl;
}

void Database::listAccounts() const
{
    const char* sql = "SELECT id, owner, balance, created_at FROM accounts ORDER BY id;";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw DatabaseException(std::string("Query failed: ") + sqlite3_errmsg(db));
    }

    bool hasRecords = false;
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "| ID | Owner                | Balance      | Created At          |" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hasRecords = true;
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* owner = sqlite3_column_text(stmt, 1);
        double balance = sqlite3_column_double(stmt, 2);
        const unsigned char* created = sqlite3_column_text(stmt, 3);

        printf("| %-2d | %-20s | $%-11.2f | %-19s |\n",
               id,
               reinterpret_cast<const char*>(owner),
               balance,
               reinterpret_cast<const char*>(created));
    }

    std::cout << std::string(70, '=') << std::endl;
    
    if (!hasRecords) {
        std::cout << "No accounts found." << std::endl;
    }

    sqlite3_finalize(stmt);
}
