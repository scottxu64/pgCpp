#ifndef CHEF_H
#define CHEF_H
#include "Person.h"
#include <iostream>

using namespace std;

class Chef: public Person
{
    public:
        Chef(int);

        string getCareer();
};

#endif // CHEF_H
