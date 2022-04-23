#include "Travel.hpp"

bool checkIfYearIsLeap(const char time[])
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

bool checkIfTimePeriodIsCorrect(const char time[])
{
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
        std::cout << "t1" <<std::endl;
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

bool Travel::comparePeriodStartAndEnd(const char timeStart[], const char timeEnd[])
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

void Travel::copy(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos)
{
    this->destination = new char[strlen(destination) + 1];
    
    if(!this->destination)
    {
        std::cout << "Memory problem" << std::endl;
        return;
    }

    strcpy(this->destination, destination);




    
    this->comment = new char[strlen(comment) + 1];
    
    if(!this->comment)
    {
        std::cout << "Memory problem" << std::endl;
        return;
    }

    strcpy(this->comment, comment);
    
    this->photos = new char[strlen(photos) + 1];
    
    if(!this->photos)
    {
        std::cout << "Memory problem" << std::endl;
        return;
    }

    strcpy(this->photos, photos);

}

void Travel::deallocate()
{
    delete[] this->destination;
    this->destination = nullptr;

    delete[] this->comment;
    this->comment = nullptr;

    delete[] this->photos;
    this->photos = nullptr;
}

Travel::Travel() : destination(nullptr), timePeriodStart({'\0',}), timePeriodEnd({'\0',}), grade(1), comment(nullptr), photos(nullptr) {}

Travel::Travel(const Travel& other)
{
    this->copy(other.destination, other.timePeriodStart, other.timePeriodEnd, other.grade, other.comment, other.photos);
}

Travel::~Travel()
{
    this->deallocate();
}

Travel& Travel::operator = (const Travel& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other.destination, other.timePeriodStart, other.timePeriodEnd, other.grade, other.comment, other.photos);
    }

    return *this;
}

/*
friend std::istream& operator >> (std::istream& in, Travel& trip);
friend std::ostream& operator << (std::ostream& out, const Travel& trip);
*/