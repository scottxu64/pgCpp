#include "Person.h"
#include <iostream>

using namespace std;

Person::Person() // class::method, here is the implementation of method.
{
    cout << "person constructor" << endl;
}

Person::~Person()
{
    cout << "person deconstructor" << endl;
}

std::string Person::getName()
{
    return Person::_name;
}
void Person::setName(std::string name)
{
    Person::_name = name;
}

void Person::methodForConstObj() const
{
    cout << "const method for const object" << endl;
}

Person::Person(std::string name, std::string nameConst)
    : _name(name), _nameConst(nameConst) // "member initializer syntax" to assign values to const members (aka global variables aka field)
{
}

std::string Person::getNameConst()
{
    return Person::_nameConst;
}
