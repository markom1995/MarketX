#include "Radnik.h"

Radnik::Radnik(std::string username , std::string password , std::string name , std::string last , long key) :
    Korisnik::Korisnik(username,password,name,last)
{this->key = key;}

Radnik::~Radnik() {}

void Radnik::login() {}
