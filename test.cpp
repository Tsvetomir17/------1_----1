#include <iostream>
#include <cstring>
#include <fstream>
    
/*
int main()
{
    std::ifstream userDataBase("UserDataBase.txt");
    if(!userDataBase.is_open())
    {
        std::cout << "Problem opening file" << std::endl;
        return 1;
    }

    char temp[1025];
    char username[65];
    char saveUsername[65];

    do
    {
        userDataBase >> username;
        if(strcmp(saveUsername, username) == 0) break;
        else strcpy(saveUsername, username);
        std::cout << username << std::endl;
    } while (userDataBase.getline(temp, 1024));
    



    userDataBase.close();
    return 0;
}
*/