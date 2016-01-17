#include "utility.h"

int getIdFromFile(const std::string& fileName)
{
    int id;
    std::fstream src;
    src.open(fileName , std::ios::in | std::ios::binary);
    if(!src.is_open())
    {
        src.open(fileName , std::ios::out | std::ios::binary);
        if(src.is_open())
        {
            src.close();
            return 1;
        }
        else
            return 0;
    }
    else
    {
        src.read((char*)&id , sizeof(int));
        src.close();
            return id;
    }
}

bool setIdToFile(const std::string& fileName, int id)
{
    std::ofstream dest;
    dest.open(fileName , std::ios::out | std::ios::binary);
    if(dest.is_open())
    {
        dest.write((char*)&id , sizeof(int));
        dest.close();
        return true;
    }
    else
        return false;
}





