#include "Administrator.h"
#include "Radnik.h"

Administrator::Administrator(int id , std::string password , std::string name , std::string last) :
    Korisnik::Korisnik(id , password , name , last)
{}

void Administrator::showMenu()
{
    char c;
    do
    {
        std::string welcome = "*** Dobrodosli " + name + " " + last + " ***";
        int w = (welcome.length())/2 + 40;
        std::cout<<std::endl<<std::setw(w)<<welcome<<std::endl<<std::endl<<std::endl;
        std::cout<<std::setw(57)<<"Izaberite neku od ponudjenih opcija"<<std::endl<<std::endl;
        std::cout<<std::setw(61)<<"[1] - Upravljanje nalozima administratora"<<std::endl;
        std::cout<<std::setw(54)<<"[2] - Upravljanje nalozima radnika"<<std::endl;
        std::cout<<std::setw(43)<<"[0] - Odjava sa sistema"<<std::endl<<std::endl;
        std::cin>>c;
        if(c=='1')
        {
            std::list<Administrator> myList;
            getList(myList,"adminData.dat");
            showEditMenu(myList,"adminData.dat");
        }
        else if(c=='2')
        {
            std::list<Radnik> myList;
            getList(myList,"radnikData.dat");
            showEditMenu(myList,"radnikData.dat");
        }
        else if(c=='0')
            std::cout<<std::endl<<std::setw(50)<<"*** Prijatan dan ***"<<std::endl<<std::endl;
        else if(c!='0')
            std::cout<<std::setw(48)<<"Nepoznata opcija!"<<std::endl<<std::endl;

    } while(c!='0');
}

std::ostream& operator<<(std::ostream& out , const Administrator& src)
{
    out<<"      "<<std::setfill('0')<<std::setw(5)<<src.id<<" ";
    std::cout.fill(' ');
    out<<std::setw(20)<<src.last<<" "<<std::setw(20)<<src.name<<" "<<std::setw(20)<<src.password;
    return out;
}

bool Administrator::modify()
{
    do
    {
    std::cout<<std::endl;
    header();
    std::cout<<*this<<std::endl;
    footer();
    std::cout<<std::endl;
    }while(Korisnik::modify());
    return true;
}
