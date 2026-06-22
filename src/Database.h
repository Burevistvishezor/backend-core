#pragma once
#include <string>
#include <sqlite3.h>
#include <stdexcept>

/// Custom exception for database errors
class DatabaseException : public std::runtime_error {
public:
    explicit DatabaseException(const std::string& message) 
        : std::runtime_error(message) {}
};

class Database {
public:
    /// Initialize database with given filename
    /// @throws DatabaseException if database cannot be opened
    Database(const std::string& filename);
    
    /// Destructor - closes database connection
    ~Database();

    /// Create accounts table if it doesn't exist
    /// @throws DatabaseException if table creation fails
    void init();
    
    /// Add a new account to the database
    /// @param owner Account owner name (cannot be empty)
    /// @param balance Initial balance (must be non-negative)
    /// @throws DatabaseException if insert fails
    /// @throws std::invalid_argument if parameters are invalid
    void addAccount(const std::string& owner, double balance);
    
    /// List all accounts in the database
    /// @throws DatabaseException if query fails
    void listAccounts() const;

private:
    sqlite3* db;
    
    /// Check for SQLite errors and throw exception if needed
    /// @param rc SQLite return code
    /// @param context Description of operation for error message
    /// @throws DatabaseException if rc indicates an error
    void checkError(int rc, const std::string& context);
};
