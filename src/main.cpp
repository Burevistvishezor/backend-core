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
