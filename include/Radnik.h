#ifndef RADNIK_H
#define RADNIK_H

#include "Korisnik.h"
#include "utility.h"

class Radnik : public Korisnik
{
    friend std::ostream& operator<<(std::ostream& out , const Radnik& src);

    public:
        Radnik(int=0 , std::string="?" , std::string="?" , std::string="?");
        virtual ~Radnik() {};

        virtual void showMenu();
        virtual bool modify();

        void printName(std::ostream&) const;
    protected:
    private:
};

#endif // RADNIK_H
