#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Korisnik.h"
#include "utility.h"
#include "Radnik.h"

class Administrator : public Korisnik
{
    friend std::ostream& operator<<(std::ostream& out , const Administrator& src);

    public:

        Administrator(int=0 , std::string="?" , std::string="?" , std::string="?");
        virtual ~Administrator() {};

        virtual void showMenu();
        virtual bool modify() override;
    protected:
    private:
};

#endif // ADMINISTRATOR_H
