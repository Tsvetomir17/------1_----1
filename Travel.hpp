#ifndef __TRAVEL_HPP
#define __TRAVEL_HPP

#include <iostream>
#include <cstring>
#include <fstream>

const size_t TIME_LENGHT = 11;
const size_t MAX_LENGTH_TRAVEL = 129;
const size_t MAX_LENGTH_TRAVEL2 = 513;

class Travel
{
private:
    char* destination;
    char timePeriodStart[TIME_LENGHT];
    char timePeriodEnd[TIME_LENGHT];
    int grade;
    char* comment;
    char* photos;

    bool checkIfTimePeriodIsCorrect(const char time[]);
    bool checkIfYearIsLeap(const char time[]);
    bool comparePeriodStartAndEnd(const char timeStart[], const char timeEnd[]);
    bool checkPhotosValidation(const char* photos);
    void copy(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos);
    void deallocate();

public:
    Travel();
    Travel(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos);
    Travel(const Travel& other);
    ~Travel();

    Travel& operator = (const Travel& other);

    friend std::istream& operator >> (std::istream& in, Travel& trip);
    friend std::ostream& operator << (std::ostream& out, const Travel& trip);

};



#endif