#include "utility.h"

bool searchLogin(const std::string& name , std::string key)
{
    std::ifstream src;
    src.open(name,std::ios::in|std::ios::binary);
    char buffer[50];
    if(src)
    {
        while(src.tellg()!=-1)
        {
            src.read(buffer,50);
        if(key == buffer)
            return true;
        src.seekg(20,std::ios::cur);
        }
        src.close();
    }
    return false;
}

