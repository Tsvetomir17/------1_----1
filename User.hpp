#ifndef __USER_HPP
#define __USER_HPP
/// Клас за потребител
///
/// В този клас се създава потребител по подадени от потребителя име, парола и имейл адрес. 
/// Класът добавя тези данни във файла UserDataBase.txt и създава собстен файл на всеки потребител, който да съдържа тяхните пътувания.

#include <iostream>
#include <cstring>
#include <fstream>

/// Константа, която се използва за максималния размер на входните данни.
const int MAX_LENGTH = 65;

class User
{
private:
    /// Член-данна за потребителското име
    char* username;

    /// Член-данна за парола
    char* password;

    /// Член-данна за имейл адрес
    char* emailAdress;

    /// Функция, която създава даденият потребител по подадените данни
    ///
    /// Извършва проверките за коректност на потребителското име чрез checkIfUsernameIsCorrect() и на имейл адреса чрез checkIfEmailAdressIsCorrect()
    /// Създава собствен файл на потребителят, чието име е потребителското име + .db
    void copy(const char* username, const char* password, const char* emailAdress);

    /// Изтрива използваната динамична памет
    void deallocate();

    /// Проверява дали даденото потребителско име е коректно
    bool checkIfUsernameIsCorrect(const char* username);

    /// Проверява дали даденият имейл адрес е коректен
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

    /// Приятелска функция за въвеждане на данните
    friend std::istream& operator >> (std::istream& in, User& user);

    /// Приятелска фунцкия за извеждане на данните
    friend std::ostream& operator << (std::ostream& out, const User& user);
};

#endif