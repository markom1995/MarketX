#include "Administrator.h"
#include "Radnik.h"

using namespace std;

int main()
{
    char buffer1[50]={0};
    char buffer2[20]={0};
    ifstream in;
    Administrator ad;
    ad.makeProfile();
    in.open("login.dat");
    if(in)
    {
        in.read(buffer1,50);
        in.read(buffer2,20);
        cout<<buffer1<<endl<<buffer2;
    }
    in.close();
}
