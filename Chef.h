#ifndef CHEF_H
#define CHEF_H
#include "Worker.h"
#include <iostream>

using namespace std;

class Chef: public Worker
{
    public:
        Chef() = default;

        Chef(string);

        Chef(string name, string career);   // variable name is optional but can help understand its purpose.

        std::string getName() const;

        string getCareer(); // step2: declare function as usual

private:
    std::string _career;
};

#endif // CHEF_H
