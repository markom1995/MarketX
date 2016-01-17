#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <list>

int getIdFromFile(const std::string&);
bool setIdToFile(const std::string& , int);



template <class T>
bool writeList(std::list<T>& src,const std::string& fileName)
{
    std::ofstream dest;
    dest.open(fileName , std::ios::out |std::ios::binary);
    if(dest.is_open())
    {
        for(typename std::list<T>::iterator it = src.begin() ; it!=src.end() ; ++it)
            it->writeToFile(dest);
        dest.close();
        return true;
    }
    return false;
}
template <class T>
bool goodId(std::list<T>& src , int id , typename std::list<T>::iterator& i)
{
    for(typename std::list<T>::iterator it = src.begin() ; it!=src.end() ; ++it)
            if (it->getId() == id)
            {
                i = it;
                return false;
            }
    return true;
}

#endif // UTILITY_H_INCLUDED
