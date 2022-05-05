#ifndef __TRAVEL_HPP
#define __TRAVEL_HPP

#include <iostream>
#include <cstring>
#include <fstream>

/// Константа за размер на периода
const int TIME_LENGHT = 11;

/// Константа за максималния размер на всяка една от данните (дестинация, коментар и снимките) при въвеждането им
const int MAX_LENGTH_TRAVEL = 129;

/// Константа, която се използва, когато е нужно взимането на цялата информация за дадено пътуване
const int MAX_LENGTH_TRAVEL2 = 1025;

/// Този клас се отнася за пътуванията
///
/// Класът приема като параметри дестинация, период, оценка, коментар и множество от снимки. При добавянето на ново пътуване,
/// данните на пътуването се записват в базата данни на съответния потребител.
class Travel
{
private:

    /// Динамично заделен масив за дестинацията
    char* destination;

    /// Масив за началото на периода на пътуването
    char timePeriodStart[TIME_LENGHT];

    /// Масив за края на периода на пътуването
    char timePeriodEnd[TIME_LENGHT];

    /// Променлива за оценка на пътуването
    int grade;

    /// Динамично заделен масив за коментара към пътуването
    char* comment;

    /// Динамично заделен масив за множеството от снимки
    char* photos;

    /// Проверява дали годината от периода е високосна
    ///
    /// @param time подава се целият период (начален или краен)
    bool checkIfYearIsLeap(const char time[]);

    /// Проверява коректността на периода (дали е във формат гггг-мм-дд)
    bool checkIfTimePeriodIsCorrect(const char time[]);

    /// Проверява дали датата на началния период е преди датата на крайния период
    bool comparePeriodStartAndEnd(const char timeStart[], const char timeEnd[]);

    /// Проверява дали снимките в множеството са с правилен формат (.jpeg или .png)
    bool checkPhotosValidation(const char* photos);

    /// По подадените параметри създава пътуване
    ///
    /// @param destination въведената от потребителя дестинация
    /// @param timeStart въведеното от потребителя начало на периода
    /// @param timeEnd въведеният от потребителя край на периода
    /// @param grade въведената от потребителя оценка
    /// @param comment въведеният от потребителя коментар
    /// @param photos въведеното от потребителя множество от снимки
    void copy(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos);

    /// Изчиства цялата динамична памет. Използва в деструктора
    void deallocate();

public:

    /// Конструктор по подразбиране
    Travel();

    /// Конструктор с параметри
    Travel(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos);

    /// Конструктор за копиране
    Travel(const Travel& other);

    /// Деструктор
    ~Travel();

    /// Предефиниран оператор равно
    Travel& operator = (const Travel& other);

    /// Приятелска фунцкия за въвеждане на данните от потребителя
    friend std::istream& operator >> (std::istream& in, Travel& trip);

    /// Приятелска фунцкия за извеждане на данните от потребителя
    friend std::ostream& operator << (std::ostream& out, const Travel& trip);
};



#endif