#ifndef __USER_HPP
#define __USER_HPP

#include <iostream>
#include <cstring>
#include <fstream>

const size_t MAX_LENGTH = 65;

class User
{
private:
    char* username;
    char* password;
    char* emailAdress;

    void copy(const char* username, const char* password, const char* emailAdress);
    void deallocate();
    bool checkIfUsernameIsCorrect(const char* username);
    bool checkIfEmailAdressIsCorrect(const char* emailAdress);

public:
    User();
    User(const char* username, const char* password, const char* emailAdress);
    User(const User& other);
    ~User();

    const char* getUsername() const;
    const char* getPassword() const;
    const char* getEmailAdress() const;

    void setUsername(const char* username);
    void setPassword(const char* password);
    void setEmailAdress(const char* emailAdress);

    User& operator = (const User& other);

    friend std::istream& operator >> (std::istream& in, User& user);
    friend std::ostream& operator << (std::ostream& out, const User& user);
};

#endif