#include "Administrator.h"

Administrator::Administrator(std::string username , std::string password , std::string name , std::string last) :
    Korisnik::Korisnik(username,password,name,last)
{}

Administrator::~Administrator() {}

void Administrator::makeProfile()
{
        std::ofstream dest;
        std::string uName , pWord , nme , lst ;
        long key;
        std::cout<<"Unesite podatke o radniku:"<<std::endl;
        do
        {
            std::cout<<"    Korisnicko ime: ";
            std::cin>>uName;
        } while(searchLogin("login.dat",uName));
        std::cout<<"    Lozinka: "; std::cin>>pWord;
        std::cout<<"    Sifra: "; std::cin>>key;
        std::cout<<"    Ime: "; std::cin>>nme;
        std::cout<<"    Prezime: "; std::cin>>lst;
        dest.open("login.dat",std::ios::app|std::ios::binary);
        if(dest)
        {
            dest.write(uName.c_str(),50);
            dest.write(pWord.c_str(),20);
            dest.close();
        }
}
void Administrator::login()
{}
