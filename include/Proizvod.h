#ifndef PROIZVOD_H
#define PROIZVOD_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include "utility.h"

class Proizvod
{
    friend std::ostream& operator<<(std::ostream& out , const Proizvod& src);

    public:
        Proizvod(int=0 , std::string="?" , double=0 , double=0);
        ~Proizvod() {};

        int getId() const;
        std::string getName() const;
        double getAmount() const;
        void setAmount(double) ;
        double getJc() const;

        void setMe(int);
        void modify();

        void writeToFile(std::ofstream& ) const;
        bool readFromFile(std::ifstream& );

        void header() const;
        void footer() const;

        bool operator<(const Proizvod& other) const;

    protected:
        int id;
        std::string name;
        double amount, jc;
};

#endif // PROIZVOD_H
