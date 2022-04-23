#include <iostream>
#include <cstring>

bool checkPhotosValidation(const char* photos)
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

int main()
{
    char buffer[1024];
    std::cin.getline(buffer, 1024);

    if(checkPhotosValidation(buffer)) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;

    return 0;
}