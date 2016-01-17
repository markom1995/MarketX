#include "Korisnik.h"
#include "Administrator.h"
#include "Radnik.h"
#include "Proizvod.h"
#include <cstdlib>

Korisnik::Korisnik(int id , std::string password , std::string name , std::string last ) :
    id(id) , password(password) , name(name) , last(last) {}

bool Korisnik::findId(int key , int&pos , const std::string& fileName)
{
    std::ifstream src;
    src.open(fileName , std::ios::in | std::ios::binary);
    if(src.is_open())
    {
        int n;
        while(!src.eof())
        {
            src.read((char*)&n , sizeof(int));
            if(!src.eof())
            {
                if(n == key)
                {
                    pos = src.tellg();              // Odredjuje poziciju passworda
                    src.close();
                    return true;
                }
                src.seekg(60 , std::ios::cur);      // Pomjeraj na sledeci zapis
            }
        }
        src.close();
        return false;
    }
    std::cout<<"Greska prilikom otvaranja datoteke "<<fileName<<"!"<<std::endl;
    return false;
}
bool Korisnik::correctPassword(const std::string& password , int pos , const std::string& fileName)
{
    std::ifstream src;
    src.open(fileName , std::ios::in | std::ios::binary);
    if(src.is_open())
    {
        char pwBuff[20];
        src.seekg(pos , std::ios::beg);
        src.read(pwBuff , 20);              // Upisuje ispravan password u pwBuff (tip char*)
        if(pwBuff == password)              // Provjera da li je unijeti password ispravan
        {
            src.close();
            return true;
        }
            src.close();
            return false;
    }
    std::cout<<"Greska prilikom otvaranja datoteke "<<fileName<<"!"<<std::endl;
    return false;
}
bool Korisnik::login(const std::string& fileName)
{

    std::cout<<std::endl<<std::setw(71)<<"*** Za odustajanje od prijave prilikom unosa pritisnite [0] ***"<<std::endl<<std::endl;
    std::string pw;
    char nameBuff[20];
    char lastBuff[20];
    int i , pos;
    bool ok;
    do
    {
        std::cout<<std::setw(28)<<"Unesite vas ID: ";
        std::cin>>i;
        if(i==0)
        {
            std::cout<<std::endl;
            return false;
        }
        if(!(ok=findId(i,pos,fileName)))            // Provjera da li je ID postojeci
            std::cout<<std::setw(62)<<"Unijeli ste nepostojeci ID , molimo ponovite unos!"<<std::endl<<std::endl;
    }while(!ok);
    do
    {
        std::cout<<std::setw(34)<<"Unesite vasu lozinku: ";
        std::cin>>pw;
        if(pw=="0")
            return false;
        if(!(ok=correctPassword(pw,pos,fileName)))  // Provjera ispravnosti lozinke
            std::cout<<std::setw(64)<<"Unijeli ste pogresnu lozinku , molimo ponovite unos!"<<std::endl<<std::endl;
    }while(!ok);
    std::ifstream src;
    src.open(fileName , std::ios::in | std::ios::binary);
    if(src.is_open())
    {
        src.seekg(pos+20,std::ios::beg);            // Blok ucitavanja u buffere
        src.read(nameBuff , 20);
        src.read(lastBuff , 20);
        src.close();
    }
    else
        return false;
    id = i;                                         // Postavljanje vrijednosti
    password = pw;
    name = nameBuff;
    last = lastBuff;
    return true;
}
int showLoginMenu(Korisnik** k)
{
    if(*k != nullptr)
    {
        delete *k;
        *k = nullptr;
    }
    char c;
    std::cout<<std::setw(70)<<"************************************************************"<<std::endl<<std::endl;
    std::cout.fill(' ');
    std::cout<<std::setw(55)<<"**** Dobrodosli u Market-X ****"<<std::endl;
    std::cout<<std::setw(52)<<"*** Prijava na sistem ***"<<std::endl;
    std::cout<<std::endl<<std::setw(70)<<"************************************************************"<<std::endl<<std::endl;
    std::cout<<std::setw(58)<<"Izaberite jednu od ponudjenih opcija"<<std::endl<<std::endl;
    std::cout<<std::setw(49)<<"[1] - Administrator"<<std::endl;
    std::cout<<std::setw(42)<<"[2] - Radnik"<<std::endl;
    std::cout<<std::setw(53)<<"[3] - Pregled proizvoda"<<std::endl;
    std::cout<<std::setw(40)<<"[0] - Kraj"<<std::endl<<std::endl;
    std::cin>>c;

    if(c=='1')
    {
        *k = new Administrator;
        if((*k)->login("adminData.dat"))
            return 1;
        return 2;
    }
    else if(c=='2')
    {
        *k = new Radnik;
        if((*k)->login("radnikData.dat"))
            return 1;
        return 2;
    }
    else if(c=='3')
    {
        std::list<Proizvod> myList;
        *k=new Radnik;
        (*k)->getList(myList,"articleData.dat");
        (*k)->viewData(myList);
        return 2;
    }
    else
        return 0;
}

int Korisnik::getId() const
{
    return id;
}
void Korisnik::setMe(int i)
{
    id = i;
    std::cout<<std::setw(25)<<"Lozinka: "; std::cin>>password;
    std::cout<<std::setw(21)<<"Ime: "; std::cin>>name;
    std::cout<<std::setw(25)<<"Prezime: "; std::cin>>last;
}
void Korisnik::modify()
{
    char c;
    do
    {
        std::cout<<"Izaberite jednu od ponudjenih opcija"<<std::endl<<std::endl;
        std::cout<<"[1] - Izmjena imena"<<std::endl;
        std::cout<<"[2] - Izmjena prezimena"<<std::endl;
        std::cout<<"[3] - Izmjena passworda"<<std::endl;
        std::cout<<"[0] - Kraj"<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::cout<<"Novo ime: ";
            std::cin>>name;
        }
        else if(c=='2')
        {
            std::cout<<"Novo prezime: ";
            std::cin>>last;
        }
        else if(c=='3')
        {
            std::cout<<"Nova lozinka: ";
            std::cin>>password;
        }
        else if(c!='0')
            std::cout<<"Nepoznata opcija!";
    } while(c!='0');
}
bool Korisnik::writeToFile(std::ofstream& dest) const           // Fajl mora biti otvoren prije ulaska u funkciju
{
    if(dest.is_open())
    {
        dest.write((char*)&id , sizeof(int));
        dest.write(password.c_str() , 20);
        dest.write(name.c_str() , 20);
        dest.write(last.c_str() , 20);
        return true;
    }
    return false;
}
bool Korisnik::readFromFile(std::ifstream& src)                 // Fajl mora biti otvoren prije ulaska u funkciju
{
    char nameBuff[20] , lastBuff[20] , pwBuff[20];
    if(src.is_open())
    {
        src.read((char*)&id , sizeof(int));
        src.read(pwBuff , 20);
        src.read(nameBuff , 20);
        src.read(lastBuff , 20);
        password = pwBuff;
        name = nameBuff;
        last = lastBuff;
        return true;
    }
    return false;
}

void Korisnik::header() const
{
    std::cout<<std::endl<<std::setw(74)<<"===== ==================== ==================== ===================="<<std::endl;
    std::cout<<std::setw(74)<<"   ID              PREZIME                  IME              LOZINKA"<<std::endl;
    std::cout<<std::setw(74)<<"===== ==================== ==================== ===================="<<std::endl;
}
void Korisnik::footer() const
{
    std::cout<<std::setw(74)<<"===== ==================== ==================== ===================="<<std::endl<<std::endl;
}

bool Korisnik::operator<(const Korisnik& other) const
{
    return id<other.getId();
}

