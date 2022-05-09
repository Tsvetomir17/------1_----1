#include "Travel.hpp"

bool Travel::checkPhotosValidation(const char* photos)
{
    int size = strlen(photos);
    bool flagForNextPhoto = false;
    
    for(int i = 0; i < size; i++)
    {
        if(flagForNextPhoto)
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

void Travel::copy(const char* destination, const Date time, const int grade, const char* comment, const char* photos)
{
    if(destination != nullptr)
    {
        this->destination = new (std::nothrow) char[strlen(destination) + 1];

        strcpy(this->destination, destination);
    }
    else
    {
        std::cout << "Invalid destination!" << std::endl;
        this->deallocate();
        return;
    }

    if(!(strlen(time.getStart()) > 0 && strlen(time.getEnd())) > 0)
    {
        std::cout << "Invalid time!" << std::endl;
        this->deallocate();
        return;
    }

    this->grade = grade;
    
    this->comment = new (std::nothrow) char[strlen(comment) + 1];

    strcpy(this->comment, comment);
    
    if(!checkPhotosValidation(photos))
    {
        std::cout << "Invalid photos!" << std::endl;
        this->deallocate();
        return;
    }

    this->photos = new (std::nothrow) char[strlen(photos) + 1];

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

Travel::~Travel()
{
    this->deallocate();
}

Travel& Travel::operator = (const Travel& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other.destination, other.timePeriod, other.grade, other.comment, other.photos);
    }

    return *this;
}


std::istream& operator >> (std::istream& in, Travel& trip)
{
    char bufferDestination[Travel::MAX_LENGTH_TRAVEL] = {'\0',};
    int bufferGrade;
    char bufferComment[Travel::MAX_LENGTH_TRAVEL] = {'\0',};
    char bufferPhotos[Travel::MAX_LENGTH_TRAVEL] = {'\0',};

    std::cout << "Destination: ";
    in.ignore();
    in.getline(bufferDestination,  Travel::MAX_LENGTH_TRAVEL - 1);

    in >> trip.timePeriod;

    std::cout << "Grade: ";
    in.ignore();
    in >> bufferGrade;

    std::cout << "Comment: ";
    in.ignore();
    in.getline(bufferComment, Travel::MAX_LENGTH_TRAVEL - 1);

    std::cout << "Photos: ";
    in.getline(bufferPhotos, Travel::MAX_LENGTH_TRAVEL - 1);

    trip.copy(bufferDestination, trip.timePeriod, bufferGrade, bufferComment, bufferPhotos);

    return in;
}

std::ostream& operator << (std::ostream& out, const Travel& trip)
{
    out << trip.destination << ' ' << trip.timePeriod << trip.grade
        << ' ' << trip.comment << ' ' << trip.photos << '\n';
    
    return out;
}
