#include "Database.h"
#include <iostream>

int main()
{
    Database db("bank.db");
    db.init();

    int choice;
    std::string name;
    double balance;

    while (true)
    {
        std::cout << "\n1. Add account\n2. List accounts\n0. Exit\n> ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1)
        {
            std::cout << "Owner name: ";
            std::cin >> name;
            std::cout << "Initial balance: ";
            std::cin >> balance;
            db.addAccount(name, balance);
        }
        else if (choice == 2)
        {
            db.listAccounts();
        }
    }
}

