#include "Racun.h"
#include <time.h>
#include <cstdlib>
#include <string>
#include <fstream>
Racun::Racun(int nn):n(nn) {}

void Racun::createBill(std::list <Proizvod> &myList,const std::string &fileName )
{
    char c;
    do
    {
        std::cout<<std::setw(51)<<"[1] - Odabir proizvoda"<<std::endl;
        std::cout<<std::setw(49)<<"[2] - Kraj dodavanja"<<std::endl;
        std::cout<<std::setw(47)<<"[0] - Ponistavanje"<<std::endl<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            addProduct(myList);
        }
        else if(c!='0' && c!='2')
            std::cout<<std::setw(48)<<"Nepoznata opcija!"<<std::endl;
    }
    while(c!='0' && c!='2');
    if(c=='2')
    {
        writeList(myList , fileName);
        std::cout<<(*this);
        sendBillToFile("racun.txt");
    }
}
void Racun::addProduct(std::list <Proizvod> &myList)
{
    bool ok;
    int i;
    double kol;
    typename std::list<Proizvod>::iterator it;
    do
    {
        std::cout<<std::setw(19)<<"Sifra: ";
        std::cin>>i;
        if((ok = goodId(myList,i,it)))
            std::cout<<std::endl<<std::setw(68)<<"Unijeli ste nepostojecu sifru , molimo ponovite unos!"<<std::endl<<std::endl;
    }
    while(ok) ;
    std::cout<<std::setw(19)<<"Naziv: "<<it->getName()<<std::endl;
    std::cout<<std::setw(20)<<"Stanje: "<<it->getAmount()<<std::endl;
    do
    {
        std::cout<<std::setw(22)<<"Kolicina: ";
        std::cin >>kol;
        if(kol>it->getAmount())
            std::cout<<std::setw(56)<<"Greska! Trenutna kolicina: "<<it->getAmount()<<std::endl<<std::endl;
    }
    while(kol>it->getAmount());
    char c;
    std::cout<<std::setw(50)<<"[1] - Dodaj na racun"<<std::endl;
    std::cout<<std::setw(44)<<"[0] - Odustani"<<std::endl<<std::endl;
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
        out<<"             "<<std::setfill('0')<<std::setw(5)<<r.niz[i].getId()<<" ";
        out<<std::setw(20)<<std::setfill(' ')<<r.niz[i].getName()<<std::setw(8)<<std::setfill(' ')
           <<r.niz[i].getAmount()<<"x"<<std::setw(9)<<r.niz[i].getJc()<<std::setw(9)<<r.niz[i].getJc()*r.niz[i].getAmount()<<std::endl;
        uk+=r.niz[i].getJc()*r.niz[i].getAmount();
    }
    out<<std::endl<<std::endl;
    out<<std::setw(50)<<std::setfill(' ')<<"Ukupna cijena za naplatu: "<<uk<<std::endl<<std::endl;
    r.footer(out);
    return out;

}

void Racun::header(std::ostream& out) const
{
    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
    out<<std::setw(53)<<"MALOPRODAJNI FISKALNI RACUN"<<std::endl<<std::endl;
    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
    out<<std::setw(66)<<"SIFRA                NAZIV KOLICINA   CIJENA   UKUPNO"<<std::endl;
    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
}
void Racun::footer(std::ostream& out) const
{
    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    out<<std::setw(38)<<asctime (timeinfo)<<std::endl;
    out<<std::setw(21)<<"Radnik: ";
    this->r.printName(out);
    out<<"    Kupac: ";
    this->k.printK(out);
    out <<std::endl<<std::endl<<std::endl;

    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
    out<<std::setw(48)<<"Dodjite nam opet!"<<std::endl<<std::endl;
    out<<std::setw(66)<<"***** ******************** ******** ******** ********"<<std::endl<<std::endl;
}


void Racun::getInfo(int idd,const std::string& pass,const std::string& namee,const std::string &lastt)
{
    Radnik rad(idd,pass,namee,lastt);
    this->r = rad;
}
void Racun::check(std::list <Kupac> &myListk)
{
    std::cout<<std::setw(23)<<"Unesi kupca"<<std::endl<<std::endl;
    bool ok = true;
    int id;
    do
    {
        std::cout<<std::setw(16)<<"ID: ";
        std::cin>>id;
        typename std::list<Kupac>::iterator i;
        if (ok = !goodId(myListk, id, i))
            k = *i;
        else
        {
            char c2;
            std::cout<<std::setw(51)<<"[1] - Dodaj novog kupca"<<std::endl;
            std::cout<<std::setw(42)<<"[0] - Odustani"<<std::endl<<std::endl;
            std::cin>>c2;
            if(c2=='1')
            {
                k.setMe(id);
                myListk.push_back(k);
                ok = true;
            }
            else
                ok = false;
        }
    } while(!ok);
    writeList(myListk , "kupacData.dat");
}

