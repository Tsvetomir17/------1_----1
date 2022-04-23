#include "User.hpp"
#include "Travel.hpp"

int main()
{
    std::cout << std::endl << std::endl << "Hello! Choose one of the following" << std::endl;
    std::cout << "1. Register new user\n2. Log in as already created user\n\n0. Exit" << std::endl;

    int choice = -1;
    int choiceAfterLogIn = 0;
    std::cin >> choice;

    char username[65] = {'\0',};

    while(choice != 1 && choice != 2 && choice != 0)
    {
        std::cout << "Bad input! Try again: ";
        std::cin >> choice;
    }

    while(choice != 0)
    {    
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

            std::cout << "1. Register new user\n2. Log in as already created user\n\n0. Exit" << std::endl;

            std::cin >> choice;

            while(choice != 1 && choice != 2 && choice != 0)
            {
                std::cout << "Bad input! Try again: ";
                std::cin >> choice;
            }
        }

        while(choice == 2)
        {
            std::cout << std::endl << "Login as" << std::endl << std::endl;

            char bufferUsername[65] = {'\0',}; 
            char bufferPassword[65] = {'\0',}; 
            std::cout << "Username: ";
            std::cin.ignore();
            std::cin.getline(bufferUsername, 65);

            std::cout << "Password: ";
            std::cin >> bufferPassword;

            std::ifstream userDataBase("UserDataBase.txt");
            if(!userDataBase.is_open())
            {
                std::cout << "Problem opening file" << std::endl;
                return 1;
            }

            User tempUser;
            bool flagIfThereIsSuchUser = false;

            while(!userDataBase.eof())
            {
                userDataBase >> tempUser;
                if(tempUser.getUsername() == bufferUsername && tempUser.getPassword() == bufferPassword);
                flagIfThereIsSuchUser = true;
                break;
            }

            userDataBase.close();

            if(!flagIfThereIsSuchUser)
            {
                std::cout << "Wrong username or password" << std::endl;
                std::cout << "1. Register new user\n2. Log in as already created user\n\n0. Exit" << std::endl;

                std::cin >> choice;

                while(choice != 1 && choice != 2 && choice != 0)
                {
                    std::cout << "Bad input! Try again: ";
                    std::cin >> choice;
                }
            }
            else
            {
                choiceAfterLogIn = -1;
                strcpy(username, bufferUsername);
            }
        }
    }

    char* fileName = new char[strlen(username) + 4];
    strcpy(fileName, username);
    strcat(fileName, ".db");

    while(choiceAfterLogIn != 0)
    {
        std::cout << "Hello, " << username << "!" << std::endl;
        std::cout << "Choose one of the following: " << std::endl;
        std::cout << "1. Add trip\n2. Check destination\n\n0. Exit" << std::endl;

        std::cin >> choiceAfterLogIn;
        while(choiceAfterLogIn != 1 && choiceAfterLogIn != 2 && choiceAfterLogIn != 0)
        {
            std::cout << "Bad input! Try again: ";
            std::cin >> choiceAfterLogIn;
        }

        while(choiceAfterLogIn == 1)
        {
            Travel trip;
            std::cin >> trip;
            
            std::ofstream file(fileName, std::ios::app);
            if(!file.is_open())
            {
                std::cout << "Problem opening file" << std::endl;
                return 1;
            }

            file << trip;
            file.close();
            std::cout << "1. Add trip\n2. Check destination\n\n0. Exit" << std::endl;

            std::cin >> choiceAfterLogIn;
            while(choiceAfterLogIn != 1 && choiceAfterLogIn != 2 && choiceAfterLogIn != 0)
            {
                std::cout << "Bad input! Try again: ";
                std::cin >> choiceAfterLogIn;
            }
        }

        while(choiceAfterLogIn == 2)
        {
            /////
        }
    }

    return 0;
}