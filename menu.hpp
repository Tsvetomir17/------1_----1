#ifndef __MENU_HPP
#define __MENU_HPP

#include "Travel.hpp"
#include "User.hpp"

const size_t MAX_TEMP_ROW = 200;

class Menu
{
private:
    int choice;
    int choiceAfterLogIn;
    char username[MAX_LENGTH];
    char fileName[MAX_LENGTH + 4];

public:
    Menu();

    void setUsername(const char* username);
    
    void checkInputChoice(int userChoice);
    void checkInputChoiceAfterLogIn(int userChoice);
    int menuFirst();
    int menuSecond(int choiceAfterLogIn);

    int getRating(const char* arr);

    void printMenuFirst() const;
    void printMenuSecond() const;
};

#endif