#include "User.hpp"

void User::copy(const char* username, const char* password, const char* emailAdress)
{
    if(checkIfUsernameIsCorrect(username))
    {
        this->username = new (std::nothrow) char[strlen(username) + 1];

        strcpy(this->username, username);
    }  
    else
    {
        std::cout << "Invalid username!" << std::endl;
        return;
    }

    if(password != nullptr)
    {
        this->password = new (std::nothrow) char[strlen(password) + 1];

        strcpy(this->password, password);
    }
    else
    {
        std::cout << "Invalid username!" << std::endl;
        this->deallocate();
        return; 
    }

    if(checkIfEmailAdressIsCorrect(emailAdress))
    {   
        this->emailAdress = new (std::nothrow) char[strlen(emailAdress) + 1];

        strcpy(this->emailAdress, emailAdress);
    }
    else
    {
        std::cout << "Invalid email adress!" << std::endl;
        this->deallocate();
        return;
    }


    char* fileName = new (std::nothrow) char[strlen(username) + 4];

    strcpy(fileName, username);
    strcat(fileName, ".db");

    std::ofstream createFile(fileName);
    if(!createFile.is_open())
    {
        std::cout << "Problem opening file" << std::endl;
        return;
    }
    createFile.close();

    delete[] fileName;
}

void User::deallocate()
{
    delete[] this->username;
    this->username = nullptr;

    delete[] this->password;
    this->password = nullptr;

    delete[] this->emailAdress;
    this->emailAdress = nullptr;
}

bool User::checkIfUsernameIsCorrect(const char* username)
{
    if(username == nullptr) return false;

    int usernameSize = strlen(username);
    
    for(int i = 0; i < usernameSize; i++)
    {
        if((username[i] < 'a' || username[i] > 'z') && (username[i] < 'A' || username[i] > 'Z') && (username[i] < '0' || username[i] > '9') || username[i] == ' ')
        {
            return false;
        }
    }

    std::ifstream file("UserDataBase.txt");

    if(!file.is_open())
    {
        return false;
    }

    char tempUserName[MAX_LENGTH];
    char tempUserLine[MAX_TEMP_ROW];
    int index = 0;

    while(!file.eof())
    {
        index = 0;
        file.getline(tempUserLine, MAX_TEMP_ROW);

        while(tempUserLine[index] != ' ')
        {
            tempUserName[index] = tempUserLine[index];
            index++;
        }

        tempUserName[index] = '\0';

        index = 0;
        while(tempUserName[index] != '\0' || username[index] != '\0')
        {
            if((tempUserName[index] >= 'A' && tempUserName[index] <= 'Z' && username[index] == tempUserName[index] + ' ') ||
               (username[index] >= 'A' && username[index] <= 'Z' && tempUserName[index] == username[index] + ' ') || // сравнява дали съвпават малка с голяма буква
               (tempUserName[index] == username[index]))  // сравнява дали са еднакви буквите
            {
                index++;
            }

            else
            {
                
                break;
            }
        }

        if(tempUserName[index] == '\0' && username[index] == '\0')
        {
            file.close();
            std::cout << "Username is taken!" << std::endl;
            return false;
        }
    }

    file.close();
    
    return true;
}

bool User::checkIfEmailAdressIsCorrect(const char* emailAdress)
{
    if(emailAdress == nullptr) return false;

    bool emailSymbolFlag = false;

    int size = strlen(emailAdress);
    int i = 0;

    while(i < size)
    {
        if(emailAdress[i] == '@')
        {
            emailSymbolFlag = true;
            i++;
        }

        if(emailSymbolFlag && emailAdress[i] == '.' && (i+1) < size)
        {
            return true;
        }

        i++;
    }

    return false;
}

User::User() : username(nullptr), password(nullptr), emailAdress(nullptr) {}

User::User(const char* username, const char* password, const char* emailAdress)
{
    this->copy(username, password, emailAdress);
}

User::User(const User& other)
{
    this->copy(other.username, other.password, other.emailAdress);
}

User::~User()
{
    this->deallocate();
}

User& User::operator = (const User& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other.username, other.password, other.emailAdress);
    }

    return *this;
}

std::istream& operator >> (std::istream& in, User& user)
{   
    char bufferUsername[User::MAX_LENGTH] = {'\0',}; 
    char bufferPassword[User::MAX_LENGTH] = {'\0',}; 
    char bufferEmailAdress[User::MAX_LENGTH] = {'\0',}; 

    std::cout << "Username: ";
    in.ignore();
    in.getline(bufferUsername, User::MAX_LENGTH);

    std::cout << "Password: ";
    in >> bufferPassword;
    
    std::cout << "Email: ";
    in.ignore();
    in >> bufferEmailAdress;

    user.copy(bufferUsername, bufferPassword, bufferEmailAdress);

    return in;
}

std::ostream& operator << (std::ostream& out, const User& user)
{
    out << user.username << ' ' << user.password << ' ' << user.emailAdress << '\n';

    return out;
}
