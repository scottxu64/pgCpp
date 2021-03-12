#ifndef CHEF_H
#define CHEF_H
#include "Worker.h"
#include <iostream>

using namespace std;

class Chef: public Worker
{
    public:
        Chef(string);

        string getCareer(); // step2: declare function as usual
};

#endif // CHEF_H
