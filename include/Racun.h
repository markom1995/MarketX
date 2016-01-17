#ifndef RACUN_H
#define RACUN_H

#include "Radnik.h"
#include "Proizvod.h"
#include "Kupac.h"
#include "Korisnik.h"
#include "Administrator.h"
#include <string>
#include <fstream>
#include "Radnik.h"
class Racun
{
        friend std::ostream& operator<<(std::ostream&,const Racun& );

    public:
        Racun(int n=0);
        void createBill(std::list <Proizvod> &myList,const std::string &fileName );
        void addProduct(std::list <Proizvod> &myList);
        void sendBillToFile(const std::string& fileName) const;
        Racun& operator+=(const Proizvod &pr);
        void header(std::ostream &) const;
        void footer(std::ostream &) const;
        void getInfo(int idd,const std::string&,const std::string&,const std::string &);
        void check(std::list <Kupac> &myListk); //provjera i unos id kupca

    protected:

    private:
        Proizvod niz[50];
        int n;
        Kupac k;
        Radnik r;


};

#endif // RACUN_H
