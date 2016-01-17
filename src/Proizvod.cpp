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
    std::cout<<std::setw(71)<<"===== ==================== ================= ================="<<std::endl;
    std::cout<<std::setw(71)<<"   ID                NAZIV          KOLICINA  JEDINICNA CIJENA"<<std::endl;
    std::cout<<std::setw(71)<<"===== ==================== ================= ================="<<std::endl;
}

void Proizvod::footer() const
{
    std::cout<<std::setw(71)<<"===== ==================== ================= ================="<<std::endl<<std::endl;
}

void Proizvod::setMe(int i)
{
    id = i;
    std::cout<<std::setw(23)<<"Naziv: "; std::cin>>name;
    std::cout<<std::setw(26)<<"Kolicina: "; std::cin>>amount;
    std::cout<<std::setw(34)<<"Jedinicna cijena: "; std::cin>>jc;
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
    out<<"         "<<std::setfill('0')<<std::setw(5)<<src.id<<" ";
    std::cout.fill(' ');
    out<<std::setw(20)<<src.name<<" "<<std::setw(17)<<src.amount<<" "<<std::setw(17)<<src.jc;
    return out;
}

void Proizvod::modify()
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
        std::cout<<std::setw(53)<<"[2] - Izmjena kolicine"<<std::endl;
        std::cout<<std::setw(61)<<"[3] - Izmjena Jedinicne cijene"<<std::endl;
        std::cout<<std::setw(41)<<"[0] - Kraj"<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::cout<<std::setw(22)<<"Novo ime: ";
            std::cin>>name;
        }
        else if(c=='2')
        {
            std::cout<<std::setw(28)<<"Nova kolicina: ";
            std::cin>>amount;
        }
        else if(c=='3')
        {
            std::cout<<std::setw(35)<<"Nova jedinicna cijena: ";
            std::cin>>jc;
        }
        else if(c!='0')
            std::cout<<std::endl<<std::setw(48)<<"Nepoznata opcija!";
    } while(c!='0');
}
