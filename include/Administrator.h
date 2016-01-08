#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Korisnik.h"
#include "utility.h"

class Administrator : public Korisnik
{
    public:
        Administrator(std::string="?",std::string="?",std::string="?",std::string="?");
        virtual ~Administrator();
        void makeProfile();
        void login();

    protected:
    private:
};

#endif // ADMINISTRATOR_H
