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

    while(choice != 0 && choiceAfterLogIn == 0)
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

            char currentUsername[65] = {'\0',};
            char currentPassword[65] = {'\0',};
            char tempWord[100] = {'\0',};
            int counterForSwitch = 1;

            bool flagIfThereIsSuchUser = false;

            while(!userDataBase.eof())
            {
                userDataBase >> tempWord;

                switch (counterForSwitch % 3)
                {
                    case 1: strcpy(currentUsername, tempWord); break;
                    case 2: strcpy(currentPassword, tempWord); break;
                    default:
                        if((strcmp(currentUsername, bufferUsername) == 0 && strcmp(currentPassword, bufferPassword) == 0))
                        {
                            flagIfThereIsSuchUser = true;
                        }
                        break;
                }

                counterForSwitch++;
                if(flagIfThereIsSuchUser) break;
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
                choice = -1;
            }
        }
    }

    char* fileName = new char[strlen(username) + 4];
    strcpy(fileName, username);
    strcat(fileName, ".db");

    while(choiceAfterLogIn != 0)
    {
        std::cout << std::endl << "Hello, " << username << "!" << std::endl;
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
            std::cout << std::endl << "1. Add trip\n2. Check destination\n\n0. Exit" << std::endl;

            std::cin >> choiceAfterLogIn;
            while(choiceAfterLogIn != 1 && choiceAfterLogIn != 2 && choiceAfterLogIn != 0)
            {
                std::cout << "Bad input! Try again: ";
                std::cin >> choiceAfterLogIn;
            }
        }

        while(choiceAfterLogIn == 2)
        {
            char bufferDestination[1025] = {'\0',};
            bool isVisited = false;

            std::cout << "Which destination would you like to check: ";
            std::cin >> bufferDestination;
            std::cout << std::endl;

            std::ifstream file("UserDataBase.txt");

            if(!file.is_open())
            {
                std::cout << "Problem opening file" << std::endl;
                return 1;
            }

            char tempUser[65];
            char tempUserSave[65];
            char tempLine[1025];
            
            do
            {
                file >> tempUser;
                if(strcmp(tempUserSave, tempUser) == 0) break;
                else strcpy(tempUserSave, tempUser);

                char* currentUserFileName = new char[strlen(tempUser) + 4];
                strcpy(currentUserFileName, tempUser);
                strcat(currentUserFileName, ".db");

                std::ifstream currentUserFile(currentUserFileName);
                if(!currentUserFile.is_open())
                {
                    std::cout << "Problem opening file!!!!!!!" << std::endl;
                    return 1;
                }

                char tempDestination[1025];
                char tempUserDestinationLine[1025];
                int index = 0;

                while(!currentUserFile.eof())
                {
                    index = 0;
                    currentUserFile.getline(tempUserDestinationLine, 1024);

                    while(tempUserDestinationLine[index] != ' ')
                    {
                        tempDestination[index] = tempUserDestinationLine[index];
                        index++;
                    }
                    tempDestination[index] = '\0';

                    if(strcmp(tempDestination, bufferDestination) == 0)
                    {
                        isVisited = true;
                        std::cout << tempUserDestinationLine << std::endl;
                    }
                }

                currentUserFile.close();

                delete[] currentUserFileName;

            } while (file.getline(tempLine, 1024));

            file.close();

            if(!isVisited)
            {
                std::cout << "No one has been there!" << std::endl;
            }

            std::cout  << std::endl << "1. Add trip\n2. Check destination\n\n0. Exit" << std::endl;

            std::cin >> choiceAfterLogIn;
            while(choiceAfterLogIn != 1 && choiceAfterLogIn != 2 && choiceAfterLogIn != 0)
            {
                std::cout << "Bad input! Try again: ";
                std::cin >> choiceAfterLogIn;
            }
        }
    }

    delete[] fileName;
    return 0;
}