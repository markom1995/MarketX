#include "Radnik.h"

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
        std::cout<<"Dobrodosli "<<name<<" "<<last<<std::endl<<"Izaberite neku od ponudjenih opcija"<<std::endl;
        std::cout<<"Pregled sopstvenog naloga - 1"<<std::endl<<"Odjava sa sistema - 0"<<std::endl;
        std::cin>>c;
        if(c=='1')
            std::cout<<*this;
        else
            std::cout<<"Prijatan dan!"<<std::endl;
    } while(c!='0');
}
