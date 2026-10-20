#include "Database.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "     Bank Account Management System" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Add account\n";
    std::cout << "2. List accounts\n";
    std::cout << "0. Exit\n";
    std::cout << "> ";
}

int main()
{
    try {
        Database db("bank.db");
        
        try {
            db.init();
            std::cout << "✓ Database initialized successfully\n";
        } catch (const DatabaseException& e) {
            std::cerr << "✗ Database initialization error: " << e.what() << std::endl;
            return 1;
        }

        int choice = -1;
        std::string name;
        double balance;

        while (true)
        {
            displayMenu();
            
            // Validate menu input
            if (!(std::cin >> choice)) {
                std::cerr << "✗ Invalid input. Please enter a number.\n";
                clearInputBuffer();
                continue;
            }

            if (choice == 0) {
                std::cout << "\nGoodbye!\n";
                break;
            }

            if (choice == 1) {
                clearInputBuffer();
                
                std::cout << "Owner name: ";
                if (!std::getline(std::cin, name)) {
                    std::cerr << "✗ Error reading input\n";
                    continue;
                }

                std::cout << "Initial balance: $";
                if (!(std::cin >> balance)) {
                    std::cerr << "✗ Invalid balance. Please enter a valid number.\n";
                    clearInputBuffer();
                    continue;
                }

                try {
                    db.addAccount(name, balance);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "✗ Invalid input: " << e.what() << std::endl;
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Database error: " << e.what() << std::endl;
                }
            }
            else if (choice == 2) {
                try {
                    db.listAccounts();
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Error listing accounts: " << e.what() << std::endl;
                }
            }
            else {
                std::cerr << "✗ Invalid choice. Please select 0, 1, or 2.\n";
            }
        }

        return 0;
    }
    catch (const DatabaseException& e) {
        std::cerr << "\n✗ Fatal database error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "\n✗ Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
#include "Database.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

std::string trimInput(const std::string& text) {
    const std::string whitespace = " \t\n\r";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "     Bank Account Management System" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Add account\n";
    std::cout << "2. List accounts\n";
    std::cout << "0. Exit\n";
    std::cout << "> ";
}

}  // namespace

int main() {
    try {
        Database db("bank.db");
        db.init();

        int choice = -1;
        while (true) {
            displayMenu();

            if (!(std::cin >> choice)) {
                std::cerr << "✗ Invalid input. Please enter a number.\n";
                clearInputBuffer();
                continue;
            }

            if (choice == 0) {
                std::cout << "\nGoodbye!\n";
                return 0;
            }

            if (choice == 1) {
                clearInputBuffer();

                std::cout << "Owner name: ";
                std::string owner;
                if (!std::getline(std::cin, owner)) {
                    std::cerr << "✗ Error reading owner name.\n";
                    continue;
                }
                owner = trimInput(owner);

                std::cout << "Initial balance: $";
                double balance = 0.0;
                if (!(std::cin >> balance)) {
                    std::cerr << "✗ Invalid balance. Please enter a valid number.\n";
                    clearInputBuffer();
                    continue;
                }

                try {
                    db.addAccount(owner, balance);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "✗ Invalid input: " << e.what() << std::endl;
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Database error: " << e.what() << std::endl;
                }
            } else if (choice == 2) {
                try {
                    db.listAccounts();
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Failed to list accounts: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "✗ Invalid choice. Please select 0, 1, or 2.\n";
            }
        }
    } catch (const DatabaseException& e) {
        std::cerr << "✗ Fatal database error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "✗ Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}#include "Database.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

std::string trimInput(const std::string& text) {
    const std::string whitespace = " \t\n\r";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "     Bank Account Management System" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Add account\n";
    std::cout << "2. List accounts\n";
    std::cout << "0. Exit\n";
    std::cout << "> ";
}

}  // namespace

int main() {
    try {
        Database db("bank.db");
        db.init();

        int choice = -1;
        while (true) {
            displayMenu();

            if (!(std::cin >> choice)) {
                std::cerr << "✗ Invalid input. Please enter a number.\n";
                clearInputBuffer();
                continue;
            }

            if (choice == 0) {
                std::cout << "\nGoodbye!\n";
                return 0;
            }

            if (choice == 1) {
                clearInputBuffer();

                std::cout << "Owner name: ";
                std::string owner;
                if (!std::getline(std::cin, owner)) {
                    std::cerr << "✗ Error reading owner name.\n";
                    continue;
                }
                owner = trimInput(owner);

                std::cout << "Initial balance: $";
                double balance = 0.0;
                if (!(std::cin >> balance)) {
                    std::cerr << "✗ Invalid balance. Please enter a valid number.\n";
                    clearInputBuffer();
                    continue;
                }

                try {
                    db.addAccount(owner, balance);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "✗ Invalid input: " << e.what() << std::endl;
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Database error: " << e.what() << std::endl;
                }
            } else if (choice == 2) {
                try {
                    db.listAccounts();
                } catch (const DatabaseException& e) {
                    std::cerr << "✗ Failed to list accounts: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "✗ Invalid choice. Please select 0, 1, or 2.\n";
            }
        }
    } catch (const DatabaseException& e) {
        std::cerr << "✗ Fatal database error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "✗ Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
#include "Database.h"

#include <cstdio>
#include <iostream>
#include <string>

Database::Database(const std::string& filename) : db_(nullptr) {
    const int rc = sqlite3_open(filename.c_str(), &db_);
    if (rc != SQLITE_OK) {
        std::string error = "Failed to open database: ";
        error += sqlite3_errmsg(db_);
        sqlite3_close(db_);
        db_ = nullptr;
        throw DatabaseException(error);
    }
}

Database::~Database() {
    if (db_ != nullptr) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

std::string Database::trim(const std::string& text) {
    const std::string whitespace = " \t\n\r";

    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }

    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

void Database::checkError(int rc, const std::string& context) const {
    if (rc != SQLITE_OK && rc != SQLITE_ROW && rc != SQLITE_DONE) {
        const std::string error = context + ": " + sqlite3_errmsg(db_);
        throw DatabaseException(error);
    }
}

void Database::init() {
    constexpr const char* sql =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "owner TEXT NOT NULL,"
        "balance REAL NOT NULL CHECK(balance >= 0),"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    char* error_message = nullptr;
    const int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &error_message);

    if (rc != SQLITE_OK) {
        std::string error = "Table creation failed: ";
        if (error_message != nullptr) {
            error += error_message;
            sqlite3_free(error_message);
        }
        throw DatabaseException(error);
    }
}

void Database::addAccount(const std::string& owner, double balance) {
    const std::string trimmed_owner = trim(owner);
    if (trimmed_owner.empty()) {
        throw std::invalid_argument("Owner name cannot be empty");
    }

    if (balance < 0.0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }

    constexpr const char* sql =
        "INSERT INTO accounts (owner, balance) VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    checkError(rc, "Failed to prepare insert statement");

    rc = sqlite3_bind_text(stmt, 1, trimmed_owner.c_str(), -1, SQLITE_TRANSIENT);
    checkError(rc, "Failed to bind owner name");

    rc = sqlite3_bind_double(stmt, 2, balance);
    checkError(rc, "Failed to bind balance");

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseException("Insert failed: " + std::string(sqlite3_errmsg(db_)));
    }

    sqlite3_finalize(stmt);
    std::cout << "✓ Account created successfully for " << trimmed_owner
              << " with balance: $" << balance << std::endl;
}

void Database::listAccounts() const {
    constexpr const char* sql =
        "SELECT id, owner, balance, created_at FROM accounts ORDER BY id;";

    sqlite3_stmt* stmt = nullptr;
    const int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw DatabaseException(std::string("Query failed: ") + sqlite3_errmsg(db_));
    }

    bool has_records = false;
    std::cout << "\n" << std::string(78, '=') << std::endl;
    std::cout << "| ID | Owner                | Balance      | Created At          |" << std::endl;
    std::cout << std::string(78, '=') << std::endl;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        has_records = true;

        const int id = sqlite3_column_int(stmt, 0);
        const unsigned char* owner = sqlite3_column_text(stmt, 1);
        const double balance = sqlite3_column_double(stmt, 2);
        const unsigned char* created = sqlite3_column_text(stmt, 3);

        std::printf("| %-2d | %-20s | $%-11.2f | %-19s |\n",
                    id,
                    reinterpret_cast<const char*>(owner),
                    balance,
                    reinterpret_cast<const char*>(created));
    }

    std::cout << std::string(78, '=') << std::endl;
    if (!has_records) {
        std::cout << "No accounts found." << std::endl;
    }

    sqlite3_finalize(stmt);
}
