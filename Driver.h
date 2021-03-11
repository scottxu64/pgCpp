#ifndef DRIVER_H
#define DRIVER_H

#include "Person.h"
#include <iostream>

using namespace std;

class Driver: public Person
{
    public:
        string getCareer();
};

#endif // DRIVER_H
