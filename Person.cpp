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

void Person::setName(string name)
{
    _name = name;
}
string Person::getName()
{
    return _name;
}

void Person::methodForConstObj() const
{
    cout << "const method for const object" << endl;
}

Person::Person(string name, string nameConst)
    : _name(name), _nameConst(nameConst) // "member initializer syntax" to assign values to const members (aka global variables aka field)
{}

string Person::getNameConst()
{
    return _nameConst;
}
