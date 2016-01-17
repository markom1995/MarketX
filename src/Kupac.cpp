#include "Kupac.h"
#include <cstdlib>

Kupac::Kupac(int id , std::string name , std::string last) :
    id(id), name(name) , last(last) {}

void Kupac::writeToFile(std::ofstream& dest) const
{
    if(dest.is_open())
    {
        dest.write((char*)&id , sizeof(int));
        dest.write(name.c_str() , 20);
        dest.write(last.c_str() , 20);
    }
}

bool Kupac::readFromFile(std::ifstream& src)
{
    char nameBuff[20], lastBuff[20];
    if(src.is_open())
    {
        src.read((char*)&id , sizeof(int));
        src.read(nameBuff , 20);
        src.read(lastBuff , 20);
        name = nameBuff;
        last = lastBuff;
        return true;
    }
    return false;
}

void Kupac::header() const
{
    std::cout<<std::endl<<std::setw(63)<<"===== ==================== ===================="<<std::endl;
    std::cout<<std::setw(63)<<"   ID              PREZIME                  IME"<<std::endl;
    std::cout<<std::setw(63)<<"===== ==================== ===================="<<std::endl;
}

void Kupac::footer() const
{
    std::cout<<std::setw(63)<<"===== ==================== ===================="<<std::endl<<std::endl;
}

void Kupac::setMe(int i)
{
    id = i;
    std::cout<<std::setw(21)<<"Ime: "; std::cin>>name;
    std::cout<<std::setw(25)<<"Prezime: "; std::cin>>last;
}

bool Kupac::operator<(const Kupac& other) const
{
    return id<other.getId();
}

int Kupac::getId() const
{
    return id;
}

std::ostream& operator<<(std::ostream& out , const Kupac& src)
{
    out<<"                "<<std::setfill('0')<<std::setw(5)<<src.id<<" ";
    std::cout.fill(' ');
    out<<std::setw(20)<<src.last<<" "<<std::setw(20)<<src.name;
    return out;
}

void Kupac::modify()
{
    char c;
    do
    {
        std::cout<<std::endl;
        header();
        std::cout<<*this<<std::endl;
        footer();
        std::cout<<std::endl;
        std::cout<<std::endl<<std::setw(58)<<"Izaberite jednu od ponudjenih opcija"<<std::endl<<std::endl;
        std::cout<<std::setw(50)<<"[1] - Izmjena imena"<<std::endl;
        std::cout<<std::setw(54)<<"[2] - Izmjena prezimena"<<std::endl;
        std::cout<<std::setw(41)<<"[0] - Kraj"<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::cout<<std::setw(22)<<"Novo ime: ";
            std::cin>>name;
        }
        else if(c=='2')
        {
            std::cout<<std::setw(26)<<"Novo prezime: ";
            std::cin>>last;
        }
        else if(c!='0')
            std::cout<<std::setw(49)<<"Nepoznata opcija!"<<std::endl<<std::endl;
    } while(c!='0');
}

void Kupac::printK(std::ostream& out) const
{
    out<<name<<" "<<last;
}
