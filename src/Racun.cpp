#include "Racun.h"
#include <time.h>
#include <cstdlib>
#include <string>
#include <fstream>
Racun::Racun(int nn):n(nn)
{

}


void Racun::createBill(std::list <Proizvod> &myList,const std::string &fileName )
{
    char c;

    do
    {
        std::cout<<"Odabir proizvoda [1], Odustajanje [0] : ";
        std::cin>>c;
        if(c=='1')
        {
            addProduct(myList);
        }
        else if(c!='0') std::cout<<"Nepoznata opcija!"<<std::endl;
    }
    while(c!='0');
    writeList(myList , fileName);

    std::cout<<(*this);

    sendBillToFile("racun.txt");





}
void Racun::addProduct(std::list <Proizvod> &myList)
{
    bool ok;
    int i;
    double kol;
    typename std::list<Proizvod>::iterator it;
    do
    {
        std::cout<<"Sifra:";
        std::cin>>i;
        if((ok = goodId(myList,i,it)))
            std::cout<<std::endl<<std::setw(68)<<"Unijeli ste nepostojecu sifru , molimo ponovite unos!"<<std::endl<<std::endl;
    }
    while(ok) ;

    std::cout<<"Naziv: "<<it->getName()<<std::endl;
    std::cout<<"Stanje: "<<it->getAmount()<<std::endl;
    do
    {
        std::cout<<"Kolicina: ";
        std::cin >>kol;
        if(kol>it->getAmount()) std::cout<<"Greska! Trenutna kolicina: "<<it->getAmount()<<std::endl;
    }
    while(kol>it->getAmount());
    char c;
    std::cout<<"Dodaj na racun [1], Odustani [0] : ";
    std::cin>>c;
    if(c=='1')
    {
        Proizvod p(it->getId(),it->getName(),kol,it->getJc());
        (*this)+=p;
        it->setAmount(it->getAmount()-kol);
    }

}

Racun& Racun::operator+=(const Proizvod &pr)
{
    niz[n++]=pr;
    return *this;
}

void Racun::sendBillToFile(const std::string& fileName) const
{
    std::ofstream dest;
    dest.open(fileName , std::ios::out | std::ios::app);
    if(dest.is_open())
    {
        dest<<(*this);
        dest.close();

    }

}
std::ostream& operator<<(std::ostream& out,const Racun& r)
{

    r.header(out);
    double uk=0;
    for(int i=0; i<r.n; i++)
    {
        out<<std::setfill('0')<<std::setw(5)<<r.niz[i].getId()<<" ";
        std::cout.fill(' ');
        out<<std::setw(9)<<std::setfill(' ')<<r.niz[i].getName()<<std::setw(15)<<std::setfill(' ')
        <<r.niz[i].getAmount()<<"x"<<std::setw(17)<<r.niz[i].getJc()<<" "<<std::setw(17)<<r.niz[i].getJc()*r.niz[i].getAmount()<<std::endl;
        uk+=r.niz[i].getJc()*r.niz[i].getAmount();
    }
    out<<std::endl<<std::endl<<std::endl;
    out<<"Ukupna cijena za naplatu: "<<uk<<std::endl<<std::endl;
    r.footer(out);
    return out;

}

void Racun::header(std::ostream& out) const
{
    out<<"**************************************************************************"<<std::endl<<std::endl;
    out<<"                     MALOPRODAJNI FISKALNI RACUN"<<std::endl<<std::endl;
    out<<"**************************************************************************"<<std::endl<<std::endl;
    out<<"SIFRA     NAZIV             KOLICINA          CIJENA           UKUPNO"<<std::endl;
}
void Racun::footer(std::ostream& out) const
{
    out<<"**************************************************************************"<<std::endl<<std::endl;
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    out<<asctime (timeinfo)<<std::endl<<std::endl;
    out<<"Radnik: ";
    this->r.printName(out);
    out<<"                        ";

    out<<"Kupac: ";
    this->k.printK(out);
    out <<std::endl<<std::endl<<std::endl;

    out<<"**************************************************************************"<<std::endl<<std::endl;
    out<<"                        Dodjite nam opet!"<<std::endl<<std::endl;
    out<<"**************************************************************************"<<std::endl<<std::endl;
}


void Racun::getInfo(int idd,const std::string& pass,const std::string& namee,const std::string &lastt)
{
    Radnik rad(idd,pass,namee,lastt);
    this->r=rad;
}
void Racun::check(std::list <Kupac> &myListk)
{
    char c1;

        int id;


        std::cout<<"Unesite ID kupca[1], Odustani[0] ";
        std::cin>>c1;
        if(c1=='1')
{


        std::cout<<"ID: ";
        std::cin>>id;
        typename std::list<Kupac>::iterator i;
        bool ok;
        if (!(ok=goodId(myListk, id, i)))
        {
            k = *i;

        }
        else
        {
            char c2;


                std::cout<<"Dodaj novog kupca [1], odustani[0]: ";
                std::cin>>c2;

                if(c2=='1')
                this->r.addData(myListk);
                goodId(myListk, id, i);
                k = *i;

        }}

    else if (c1!='0') std::cout<<"Nepoznata funkcija!"<<std::endl;

    writeList(myListk , "kupacData.dat");

}

