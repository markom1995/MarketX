#ifndef KORISNIK_H
#define KORISNIK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include "utility.h"

/*
     Metode i funkcije koje sadrze $ trebaju biti realizovane u kupcu i proizvodu
 */

class Korisnik
{
    friend int showLoginMenu(Korisnik**);

    public:

        Korisnik(int=0 , std::string="?" , std::string="?" , std::string="?");
        virtual ~Korisnik();

        int getId() const;
        bool login(const std::string&);

        void writeToFile(std::ofstream& ) const;            // $ Upis jednog u fajl
        bool readFromFile(std::ifstream& );                 // $ Citanje jednog iz fajla

        void header() const;                                // $ Pisanje header - a
        void footer() const;                                // $ Pisanje footer - a

        void setMe(int);                                    // $ Pravljenje novog
        bool operator<(const Korisnik& other) const;        // $ Operator poredjenja

        virtual void showMenu() = 0;                        // Prikazuje meni

        template<class T> bool getList(std::list<T>& , const std::string&);         // Generisanje liste
        template<class T> void showEditMenu(std::list<T>& , const std::string&);    // Prikazivanje menija za upravljanje
        template<class T> void addData(std::list<T>&);                              // Dodavanje novog u listu
        template<class T> void viewData(std::list<T>&);                             // Pregled svih
        template<class T> void deleteData(std::list<T>&);                           // Brisanje jednog

    protected:
        int id;
        std::string password;
        std::string name , last;

    private :
        bool findId(int , int& , const std::string&);                               // Pretrazuje ID u listi
        bool correctPassword(const std::string& , int , const std::string&);        // Provjera da li je lozinka ispravna
};

template<class T>
bool Korisnik::getList(std::list<T>& myList, const std::string& fileName)
{
    std::ifstream src;
    src.open(fileName , std::ios::in | std::ios::binary);
    if(src.is_open())
    {
        while(!src.eof())
        {
            T temp;
            temp.readFromFile(src);
            if(!src.eof())
                myList.push_back(temp);
        }
        src.close();
        return true;
    }
    else return false;
}

template <class T>
void Korisnik::viewData(std::list<T>& myList)
{
    T temp;
    temp.header();          // Ispis header -a
    myList.sort();          // Sortiranje liste , potrebno preklopiti <
    for(typename std::list<T>::iterator it = myList.begin() ; it != myList.end() ; ++it)
            std::cout<<*it<<std::endl;      // Ispis objekta klase T , potrebno napraviti <<
    temp.footer();          // Ispis footer - a
}

template<class T>
void Korisnik::deleteData(std::list<T>& myList)
{
        int key;
        std::cout<<"Unesite ID / Sifru po kojoj brisete: ";
        std::cin>>key;
        for(typename std::list<T>::iterator it = myList.begin() ; it != myList.end() ; ++it)
        {
            if(it->getId() == key)
            {
                myList.erase(it);       // Brise element na koji pokazuje iterator it
                return;
            }
        }
        std::cout<<"Pogresno unesen ID!"<<std::endl;
}

template<class T>
void Korisnik::addData(std::list<T>& myList)
{
    char c;
    T temp;
    int i;
    bool ok;
    typename std::list<T>::iterator ii;
    std::cout<<std::setw(28)<<"Unesite podatke:"<<std::endl;
    do
    {
        std::cout<<std::setw(28)<<"ID / Sifra: ";
        std::cin>>i;
        if(!(ok = goodId(myList,i,ii)))
            std::cout<<std::endl<<std::setw(68)<<"Unijeli ste postojeci ID / Sifru , molimo ponovite unos!"<<std::endl<<std::endl;
    } while(!ok) ;
    temp.setMe(i);              // Pravljenje novog objekta klase T
    std::cout<<"Potvrdite dodavanje [1] , Odustanite [ostalo] ?";
    std::cin>>c;
    if(c=='1')
        myList.push_back(temp);
    else
        std::cout<<"Dodavanje prekinuto!"<<std::endl;
}
template<class T>
void Korisnik::showEditMenu(std::list<T>& myList , const std::string& fileName)
{
        char c;
        do
        {
            std::cout<<std::setw(57)<<"Izaberite neku od ponudjenih opcija"<<std::endl<<std::endl;
            std::cout<<std::setw(51)<<"[1] - Dodavanje novog"<<std::endl;
            std::cout<<std::setw(48)<<"[2] - Pregled svih"<<std::endl;
            std::cout<<std::setw(51)<<"[3] - Brisanje jednog"<<std::endl;
            std::cout<<std::setw(40)<<"[0] - Kraj"<<std::endl<<std::endl;
            std::cin>>c;
        if(c=='1')
        {
            addData(myList);
        }
        else if(c=='2')
        {
            viewData(myList);
        }
        else if(c=='3')
        {
            deleteData(myList);
        }
        else if(c=='0')
        {
            if(writeList(myList , fileName))
                std::cout<<"Uspjesno azuriranje datoteke "<<fileName<<" !"<<std::endl;
            else
                std::cout<<"Greska prilikom otvaranja datoteke "<<fileName<<" !"<<std::endl;
        }
        else if(c!='0')
            std::cout<<"Nepoznata opcija"<<std::endl;
        } while(c!='0');
}

#endif // KORISNIK_H
