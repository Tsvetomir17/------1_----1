#include "Travel.hpp"

void copy(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char** photos);
void Travel::deallocate()
{
    delete[] this->destination;
    this->destination = nullptr;

    delete[] this->comment;
    this->comment = nullptr;

    ///////////////////////////////////////////
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