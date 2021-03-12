#ifndef DRIVER_H
#define DRIVER_H

#include "Worker.h"
#include <iostream>

using namespace std;

class Driver: public Worker
{
    public:
        Driver(string);
        string getCareer();
};

#endif // DRIVER_H
