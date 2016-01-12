#include "Administrator.h"
#include "Radnik.h"
#include "Proizvod.h"

using namespace std;

int main()
{

    int a;
    Korisnik *k = nullptr;
    do
    {
        if((a=showLoginMenu(&k))==1)
            k->showMenu();
    } while(a!=0);
    delete k;
    return 0;
}

