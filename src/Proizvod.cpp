#include "Proizvod.h"
#include <cstdlib>

Proizvod::Proizvod(int id , std::string name , double amount , double jc) :
    id(id) , name(name) , amount(amount) , jc(jc) {}

void Proizvod::writeToFile(std::ofstream& dest) const
{
    if(dest.is_open())
    {
        dest.write((char*)&id , sizeof(int));
        dest.write(name.c_str() , 20);
        dest.write((char*)&amount , sizeof(double));
        dest.write((char*)&jc , sizeof(double));
    }
}

bool Proizvod::readFromFile(std::ifstream& src)
{
    char nameBuff[20];
    if(src.is_open())
    {
        src.read((char*)&id , sizeof(int));
        src.read(nameBuff , 20);
        src.read((char*)&amount , sizeof(double));
        src.read((char*)&jc , sizeof(double));
        name = nameBuff;
        return true;
    }
    return false;
}

void Proizvod::header() const
{
    std::cout<<"===== ==================== ================= ================="<<std::endl;
    std::cout<<"   ID                NAZIV          KOLICINA  JEDINICNA CIJENA"<<std::endl;
    std::cout<<"===== ==================== ================= ================="<<std::endl;
}

void Proizvod::footer() const
{
    std::cout<<"===== ==================== ================= ================="<<std::endl;
}

void Proizvod::setMe(int i)
{
    id = i;
    std::cout<<"    Naziv: "; std::cin>>name;
    std::cout<<"    Kolicina: "; std::cin>>amount;
    std::cout<<"    Jedinicna cijena: "; std::cin>>jc;
}

bool Proizvod::operator<(const Proizvod& other) const
{
    return id<other.getId();
}

int Proizvod::getId() const
{
    return id;
}

std::ostream& operator<<(std::ostream& out , const Proizvod& src)
{
    out<<std::setfill('0')<<std::setw(5)<<src.id<<" ";
    std::cout.fill(' ');
    out<<std::setw(20)<<src.name<<" "<<std::setw(17)<<src.amount<<" "<<std::setw(17)<<src.jc;
    return out;
}

void Proizvod::modify()
{
    char c;
    do
    {
        std::cout<<"Izaberite jednu od ponudjenih opcija"<<std::endl<<std::endl;
        std::cout<<"[1] - Izmjena imena"<<std::endl;
        std::cout<<"[2] - Izmjena kolicine"<<std::endl;
        std::cout<<"[3] - Izmjena Jedinicne cijene"<<std::endl;
        std::cout<<"[0] - Kraj"<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::cout<<"Novo ime: ";
            std::cin>>name;
        }
        else if(c=='2')
        {
            std::cout<<"Nova kolicina: ";
            std::cin>>amount;
        }
        else if(c=='3')
        {
            std::cout<<"Nova jedinicna cijena: ";
            std::cin>>jc;
        }
        else if(c!='0')
            std::cout<<"Nepoznata opcija!";
    } while(c!='0');
}
