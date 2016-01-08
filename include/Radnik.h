#ifndef RADNIK_H
#define RADNIK_H

#include "Korisnik.h"


class Radnik : public Korisnik
{
    public:
        Radnik(std::string="?",std::string="?",std::string="?",std::string="?",long=0);
        virtual ~Radnik();
        void login();
    protected:
        long key;
    private:
};

#endif // RADNIK_H
