#include "User.hpp"
#include "Travel.hpp"

int main()
{
    std::cout << std::endl << std::endl << "Hello! Choose one of the following" << std::endl;
    std::cout << "1. Register new user\n2. Log in as already created user" << std::endl;

    int choice = 0;
    std::cin >> choice;

    while(choice != 1 && choice != 2)
    {
        std::cout << "Bad input! Try again: ";
        std::cin >> choice;
    }

    while(choice == 1)
    {
        std::cout << std::endl << "Create accont" << std::endl << std::endl;
        User newUser;
        std::cin >> newUser;

        std::ofstream userDataBase("UserDataBase.txt", std::ios::app);
        if(!userDataBase.is_open())
        {
            std::cout << "Problem opening file" << std::endl;
            return 1;
        }

        userDataBase << newUser;

        userDataBase.close();

        std::cout << "1. Register new user\n2. Log in as already created user" << std::endl;

        std::cin >> choice;

        while(choice != 1 && choice != 2)
        {
            std::cout << "Bad input! Try again: ";
            std::cin >> choice;
        }
    }

    

    return 0;
}