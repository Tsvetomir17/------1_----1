#ifndef __USER_HPP
#define __USER_HPP

#include <iostream>
#include <cstring>  
#include <fstream>

/// Константа за максималния размер на всяка една от данните (потребителско име, парола и имейл адрес) при въвеждането им
const int MAX_LENGTH = 65;

/// Този клас се отнася за потребителите
///
/// Класът приема като параметри потребителско име, парола и имейл адрес. Създава личен файл на всеки нов потребител, чието име е потребителското име на потребителя.
/// Този файл съдържа неговите пътувания. Също така, при създаването на нов потребител, данните му се запазват във файл с име UserDataBase.txt
class User
{
private:

    /// Динамично заделен масив за потребителското име
    char* username;

    /// Динамично заделен масив за паролата
    char* password;

    /// Динамично заделен масив за имейл адреса
    char* emailAdress;

    /// По подадените параметри създава потребител и неговия файл
    /// @param username въведеното от потребителя потребителско име
    /// @param password въведената от потребителя парола
    /// @param emailAdress въведеният от потребителя имейл адрес
    void copy(const char* username, const char* password, const char* emailAdress);

    /// Изчиства цялата динамична памет. Използва в деструктора
    void deallocate();

    /// Проверява коректността на потребителското име (дали съдържат само латински букви и цифри)
    bool checkIfUsernameIsCorrect(const char* username);

    /// Проверява коректността на имейл адреса (дали има символа @)
    bool checkIfEmailAdressIsCorrect(const char* emailAdress);

public:
    
    /// Конструктор по подразбиране
    User();

    /// Конструктор с параметри
    User(const char* username, const char* password, const char* emailAdress);

    /// Конструктор за копиране
    User(const User& other);

    /// Деструктор
    ~User();

    /// Селектор за потребителското име
    const char* getUsername() const;

    /// Селектор за паролата
    const char* getPassword() const;

    /// Селектор за имейл адреса
    const char* getEmailAdress() const;

    /// Мутатор за потребителското име
    void setUsername(const char* username);

    /// Мутатор за паролата
    void setPassword(const char* password);

    /// Мутатор за имейл адреса
    void setEmailAdress(const char* emailAdress);

    /// Предефиниран оператор равно
    User& operator = (const User& other);

    /// Приятелска функция за въвеждане на входните данни
    friend std::istream& operator >> (std::istream& in, User& user);

    /// Приятелска фунцкия за извеждане на данните на потребителя
    friend std::ostream& operator << (std::ostream& out, const User& user);
};

#endif