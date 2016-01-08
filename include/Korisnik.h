#ifndef KORISNIK_H
#define KORISNIK_H
#include <iostream>
#include <string>
#include <fstream>

class Korisnik
{
    public:
        Korisnik(std::string="?",std::string="?",std::string="?",std::string="?");
        virtual ~Korisnik();
        virtual void login()=0;
    protected:
        std::string username , password;
        std::string name , last;
    private:

};

#endif // KORISNIK_H
