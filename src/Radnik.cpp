#include "Radnik.h"
#include "Proizvod.h"
#include "Kupac.h"
#include "Racun.h"
#include "Korisnik.h"

Radnik::Radnik(int id , std::string password , std::string name , std::string last) :
    Korisnik::Korisnik(id , password , name , last) {}

Radnik::~Radnik() {}

void Radnik::login() {}

std::ostream& operator<<(std::ostream& out , const Radnik& src)
{
    out<<std::setfill('0')<<std::setw(5)<<src.id<<" ";
    std::cout.fill(' ');
    out<<std::setw(20)<<src.last<<" "<<std::setw(20)<<src.name<<" "<<std::setw(20)<<src.password;
    return out;
}
void Radnik::showMenu()
{
    char c;
    do
    {
        std::string welcome = "*** Dobrodosli " + name + " " + last + " ***";
        int w = (welcome.length())/2 + 40;
        std::cout<<std::endl<<std::setw(w)<<welcome<<std::endl<<std::endl<<std::endl;
        std::cout<<std::setw(57)<<"Izaberite neku od ponudjenih opcija"<<std::endl<<std::endl;
        std::cout<<std::setw(49)<<"[1] - Upravljanje proizvodima"<<std::endl;
        std::cout<<std::setw(45)<<"[2] - Upravljanje kupcima"<<std::endl;
        std::cout<<std::setw(42)<<"[3] - Izdavanje racuna"<<std::endl;
        std::cout<<std::setw(43)<<"[0] - Odjava sa sistema"<<std::endl<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::list<Proizvod> myList;
            getList(myList,"articleData.dat");
            showEditMenu(myList,"articleData.dat");
        }
        else if(c=='2')
        {
            std::list<Kupac> myList;
            getList(myList,"kupacData.dat");
            showEditMenu(myList,"kupacData.dat");
        }
        else if(c=='3')
        {
            Racun r;
            std::list<Kupac> myListk;
            getList(myListk,"kupacData.dat");
            r.check(myListk);
           std::list<Proizvod> myList;
           r.getInfo(id,password,name,last);
            getList(myList,"articleData.dat");
            r.createBill(myList,"articleData.dat");


        }

        else
            std::cout<<"Prijatan dan!"<<std::endl;
    } while(c!='0');
}

void Radnik::printName(std::ostream& out) const
{
    out<<name<<" "<<last;
}
