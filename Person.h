#ifndef PERSON_H        // ifndef = if not defined
#define PERSON_H
#include <iostream>

class Person
{
    public:
        Person();
        std::string getName();
        void setName(std::string name);

    private:
        std::string _name;
};

#endif // PERSON_H
