#include "Travel.hpp"

bool Travel::checkIfYearIsLeap(const char time[])
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

bool Travel::checkIfTimePeriodIsCorrect(const char time[])
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

bool Travel::checkPhotosValidation(const char* photos)
{
    int size = strlen(photos);
    bool flagForNextPhoto = false;
    
    for(int i = 0; i < size; i++)
    {
        if(flagForNextPhoto == true)
        {
            if(photos[i] != ' ')
            {
                return false;
            }
            else
            {
                flagForNextPhoto = false;
                continue;
            }
        }

        if(photos[i] == '.')
        {
            if(photos[i+1] == 'j' && photos[i+2] == 'p' && photos[i+3] == 'e' && photos[i+4] == 'g')
            {
                i += 4;
                flagForNextPhoto = true;
            }

            else if(photos[i+1] == 'p' && photos[i+2] == 'n' && photos[i+3] == 'g')
            {
                i += 3;
                flagForNextPhoto = true;
            }

            else
            {
                return false;
            }
        }

        else if((photos[i] >= 'a' && photos[i] <= 'z') || (photos[i] >= 'A' && photos[i] <= 'Z') || (photos[i] >= '0' && photos[i] <= '9') || photos[i] == '_' || photos[i] == '-')
        {
            continue;
        }

        else
        {
            return false;
        }
    }

    return true;
}

void Travel::copy(const char* destination, const char timeStart[], const char timeEnd[], const int grade, const char* comment, const char* photos)
{
    this->destination = new char[strlen(destination) + 1];
    
    if(!this->destination)
    {
        std::cout << "Memory problem" << std::endl;
        this->deallocate();
        return;
    }

    strcpy(this->destination, destination);

    if(strlen(timeStart) != TIME_LENGHT - 1 && strlen(timeEnd) != TIME_LENGHT - 1)
    {
        std::cout << "Invalid time!" << std::endl;
        this->deallocate();
        return;
    }

    if(checkIfTimePeriodIsCorrect(timeStart) && checkIfTimePeriodIsCorrect(timeEnd) && comparePeriodStartAndEnd(timeStart, timeEnd))
    {
        strcpy(this->timePeriodStart, timeStart);
        strcpy(this->timePeriodEnd, timeEnd);
    }

    else
    {
        std::cout << "Invalid time!" << std::endl;
        this->deallocate();
        return;
    }

    this->grade = grade;
    
    this->comment = new char[strlen(comment) + 1];
    
    if(!this->comment)
    {
        std::cout << "Memory problem" << std::endl;
        this->deallocate();
        return;
    }

    strcpy(this->comment, comment);
    

    if(!checkPhotosValidation(photos))
    {
        std::cout << "Invalid photos" << std::endl;
        this->deallocate();
        return;
    }

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

Travel::Travel() : destination(nullptr), grade(1), photos(nullptr), comment(nullptr) {}

Travel::Travel(const char* destination, const char* timeStart, const char* timeEnd, const int grade, const char* comment, const char* photos)
{
    this->copy(destination, timeStart, timeEnd, grade, comment, photos);
}

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


std::istream& operator >> (std::istream& in, Travel& trip)
{
    char bufferDestination[MAX_LENGTH_TRAVEL] = {'\0',};
    char bufferTimeStart[TIME_LENGHT] = {'\0',};
    char bufferTimeEnd[TIME_LENGHT] = {'\0',};
    int bufferGrade;
    char bufferComment[MAX_LENGTH_TRAVEL] = {'\0',};
    char bufferPhotos[MAX_LENGTH_TRAVEL] = {'\0',};

    std::cout << "Destination: ";
    in.ignore();
    in.getline(bufferDestination, MAX_LENGTH_TRAVEL - 1);

    std::cout << "Time period start: ";
    in >> bufferTimeStart;
    std::cout << "Time period end: ";
    in.ignore();
    in >> bufferTimeEnd;

    std::cout << "Grade: ";
    in.ignore();
    in >> bufferGrade;

    std::cout << "Comment: ";
    in.ignore();
    in.getline(bufferComment, MAX_LENGTH_TRAVEL - 1);

    std::cout << "Photos: ";
    in.getline(bufferPhotos, MAX_LENGTH_TRAVEL - 1);

    trip.copy(bufferDestination, bufferTimeStart, bufferTimeEnd, bufferGrade, bufferComment, bufferPhotos);

    return in;
}

std::ostream& operator << (std::ostream& out, const Travel& trip)
{
    out << trip.destination << ' ' << trip.timePeriodStart << ' ' << trip.timePeriodEnd << ' ' << trip.grade
        << ' ' << trip.comment << ' ' << trip.photos << '\n';
    
    return out;
}

