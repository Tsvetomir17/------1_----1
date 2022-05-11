#include "Date.hpp"

bool Date::checkIfYearIsLeap(const char time[])
{
    int year = 0;
    
    for(int i = 0; i < 4; i++)
    {
        year *= 10;
        year += (int)time[i] - '0';
    }

    if(year % 100 == 0 && year % 400 != 0)
    {
        return false;
    }

    if(year % 4 == 0)
    {
        return true;
    }

    return false;
}

bool Date::checkIfTimePeriodIsCorrect(const char time[])
{
    if(strlen(time) != TIME_LENGHT - 1)
    {
        return false;
    }

    if(time[4] != '-' || time[7] != '-')
    {
        return false;
    }

    for(int i = 0; i < 4; i++)
    {
        if(time[i] < '0' || time[i] > '9')
        {
            return false;
        }
    }

    if(time[5] < '0' || time[5] > '1')
    {
        return false;
    }

    if(time[5] == '0' && (time[6] < '0' || time[6] > '9'))
    {
        return false;
    }

    if(time[5] == '1' && (time[6] < '0' || time[6] > '2'))
    {
        return false;
    }

    if(time[8] < '0' || time[8] > '3')
    {
        return false;
    }

    if(time[9] < '0' || time[9] > '9')
    {
        return false;
    }

    if(time[8] == '3' && time[9] > '1')
    {
        return false;
    }

    if(checkIfYearIsLeap(time))
    {
        if((time[5] == '0' && time[6] == '2') && time[8] == '2' && (time[9] < '0' || time[9] > '9'))
        {
            return false;
        }
    }
    else
    {
        if((time[5] == '0' && time[6] == '2') && time[8] == '2' && (time[9] < '0' || time[9] > '8'))
        {
            return false;
        }
    }

    if((time[5] == '0' && (time[6] == '4' || time[6] == '6' || time[6] == '9')) && time[8] == '3' && time[9] != '0')
    {
        return false;
    } 

    if(time[5] == '1' && time[6] == '1' && time[9] != '0')
    {
        return false;
    }

    return true;
}

bool Date::comparePeriodStartAndEnd(const char timeStart[], const char timeEnd[])
{
    for(int i = 0; i < 10; i++)
    {
        if(timeStart[i] != timeEnd[i])
        {
            return timeEnd[i] > timeStart[i];
        }
    }

    return false;
}

Date::Date()
{
    timePeriodStart[TIME_LENGHT] = {'\0',};
    timePeriodEnd[TIME_LENGHT] = {'\0',};
}

void Date::setDate(const char start[], const char end[])
{
    std::cout << start << " " << end << std::endl;

    if(checkIfTimePeriodIsCorrect(start) && checkIfTimePeriodIsCorrect(end))
    {
        strcpy(this->timePeriodStart, start);
        strcpy(this->timePeriodEnd, end);
    }
}

const char* Date::getStart() const
{
    return this->timePeriodStart;
}

const char* Date::getEnd() const
{
    return this->timePeriodEnd;
}

std::istream& operator >> (std::istream& in, Date& date)
{
    char bufferTimeStart[Date::TIME_LENGHT] = {'\0',};
    char bufferTimeEnd[Date::TIME_LENGHT] = {'\0',};

    std::cout << "Note: The date format must be: yyyy-mm-dd" << std::endl;
    std::cout << "      (use the - symbol for separator)!  " << std::endl;

    std::cout << "Time period start: ";
    in >> bufferTimeStart;

    std::cout << "Time period end: ";
    in.ignore();
    in >> bufferTimeEnd;

    date.setDate(bufferTimeStart, bufferTimeEnd);

    return in;
}

std::ostream& operator << (std::ostream& out, const Date& date)
{
    out << date.timePeriodStart << ' ' << date.timePeriodEnd << ' ';

    return out;
}
