#include "User.hpp"

void User::copy(const char* username, const char* password, const char* emailAdress)
{
    if(checkIfUsernameIsCorrect(username))
    {
        this->username = new char[strlen(username) + 1];

        if(!this->username)
        {
            this->deallocate();
            std::cout << "Memory problem" << std::endl;
            return;
        }

        strcpy(this->username, username);
    }
    
    else
    {
        std::cout << "Invalid username!" << std::endl;
        return;
    }


    this->password = new char[strlen(password) + 1];

    if(!this->password)
    {
        this->deallocate();
        std::cout << "Memory problem" << std::endl;
        return;
    }

    strcpy(this->password, password);


    if(checkIfEmailAdressIsCorrect(emailAdress))
    {   
        this->emailAdress = new char[strlen(emailAdress) + 1];

        if(!this->emailAdress)
        {
            this->deallocate();
            std::cout << "Memory problem" << std::endl;
            return;
        }

        strcpy(this->emailAdress, emailAdress);
    }

    else
    {
        std::cout << "Invalid email adress!" << std::endl;
        this->deallocate();
        return;
    }
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
    int usernameSize = strlen(username);
    for(int i = 0; i < usernameSize; i++)
    {
        if((username[i] < 'a' || username[i] > 'z') && (username[i] < 'A' || username[i] > 'Z') && (username[i] < '0' || username[i] > '9') || username[i] == ' ')
        {
            //std::cout << "Invalid username!" << std::endl;
            return false;
        }
    }

    return true;
}

bool User::checkIfEmailAdressIsCorrect(const char* emailAdress)
{
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

        if(emailSymbolFlag == true && emailAdress[i] == '.' && (i+1) < size)
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

const char* User::getUsername() const
{
    return this->username;
}

const char* User::getPassword() const
{
    return this->password;
}

const char* User::getEmailAdress() const
{
    return this->emailAdress;
}

void User::setUsername(const char* username)
{

    if(checkIfUsernameIsCorrect(username))
    {
        if(this->username != nullptr)
        {
            delete[] this->username;
            this->username = nullptr;
        }

        this->username = new char[strlen(username) + 1];

        if(!this->username)
        {
            this->deallocate();
            std::cout << "Memory problem" << std::endl;
            return;
        }

        strcpy(this->username, username);
    }
    
    else
    {
        std::cout << "Invalid username!" << std::endl;
        return;
    }

}

void User::setPassword(const char* password)
{
    if(this->password != nullptr)
    {
        delete[] this->password;
        this->password = nullptr;
    }

    this->password = new char[strlen(password) + 1];

    if(!this->password)
    {
        this->deallocate();
        std::cout << "Memory problem" << std::endl;
        return;
    }

    strcpy(this->password, password);
}

void User::setEmailAdress(const char* emailAdress)
{
    if(checkIfEmailAdressIsCorrect(emailAdress))
    {   
        if(this->emailAdress != nullptr)
        {
            delete[] this->emailAdress;
            this->password = nullptr;
        }

        this->emailAdress = new char[strlen(emailAdress) + 1];

        if(!this->emailAdress)
        {
            this->deallocate();
            std::cout << "Memory problem" << std::endl;
            return;
        }

        strcpy(this->emailAdress, emailAdress);
    }

    else
    {
        std::cout << "Invalid email adress!" << std::endl;
        this->deallocate();
        return;
    }
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
    char bufferUsername[65] = {'\0',}; 
    char bufferPassword[65] = {'\0',}; 
    char bufferEmailAdress[65] = {'\0',}; 
    std::cout << "Username: ";
    in.ignore();
    in.getline(bufferUsername, 65);
    //user.setUsername(buffer);

    std::cout << "Password: ";
    in.ignore();
    in >> bufferPassword;
    //user.setPassword(buffer);
    
    std::cout << "Email: ";
    in.ignore();
    in >> bufferEmailAdress;
    //user.setEmailAdress(buffer);

    user.copy(bufferUsername, bufferPassword, bufferEmailAdress);

    return in;
}

std::ostream& operator << (std::ostream& out, const User& user)
{
    out << user.username << ' ' << user.password << ' ' << user.emailAdress << '\n';

    return out;
}

