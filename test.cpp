#include "User.hpp"
#include <fstream>

int main()
{
    User neww;
    std::cin >> neww;
    
    std::ofstream UsersDataBase("UsersDataBase.txt", std::ios::app);

    if(!UsersDataBase.is_open())
    {
        std::cout << "Problems with file opening!" << std::endl;
        return 1;
    }

    UsersDataBase << neww;

    UsersDataBase.close();
    return 0;
}