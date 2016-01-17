#ifndef KUPAC_H
#define KUPAC_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include "utility.h"

class Kupac
{
    friend std::ostream& operator<<(std::ostream& out , const Kupac& src);
    public:
        Kupac(int=0 , std::string="?" , std::string="?");
        virtual ~Kupac() {};

        int getId() const;
        void setMe(int);
        void modify() {};

        void writeToFile(std::ofstream& ) const;
        bool readFromFile(std::ifstream& );

        void header() const;
        void footer() const;

        bool operator<(const Kupac& other) const;

    protected:
        int id;
        std::string name, last;
};

#endif // KUPAC_H
