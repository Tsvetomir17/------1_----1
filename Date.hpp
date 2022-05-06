#ifndef __DATE_HPP
#define __DATE_HPP

#include <iostream>
#include <cstring>

/// Константа за размер на периода
const int TIME_LENGHT = 11;

/// Този клас се използва за периода на пътуванията
///
/// Класът има два масива, съдържащи началото и края на периода на пътуването.
/// В него има проверки за валидността на датата.
class Date
{
private:

    /// Масив за началото на периода на пътуването
    char timePeriodStart[TIME_LENGHT];

    /// Масив за края на периода на пътуването
    char timePeriodEnd[TIME_LENGHT];

    /// Проверява дали годината от периода е високосна
    ///
    /// @param time подава се целият период (начален или краен)
    bool checkIfYearIsLeap(const char time[]);

    /// Проверява коректността на периода (дали е във формат гггг-мм-дд)
    bool checkIfTimePeriodIsCorrect(const char time[]);

    /// Проверява дали датата на началния период е преди датата на крайния период
    bool comparePeriodStartAndEnd(const char timeStart[], const char timeEnd[]);

public:

    /// Конструктор по подразбиране
    Date();

    /// Мутатор за периода, в който се извършва проверката за коректност
    void setDate(const char start[], const char end[]);

    /// Селектор за началото на периода
    const char* getStart() const;

    /// Селектор за края на периода
    const char* getEnd() const;

    ///Приятелска фунцкия за въвеждане на периода
    friend std::istream& operator >> (std::istream& in, Date& date);

    /// Приятелска фунцкия за извеждане на периода
    friend std::ostream& operator << (std::ostream& out, const Date& date);
};

#endif