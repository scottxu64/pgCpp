#include "Person.h"
#include <iostream>

using namespace std;

Person::Person()    // class::method, here is the implementation of method.
{
    cout<<"person constructor"<<endl;
}

std::string Person::getName(){
    return Person::_name;
}

void Person::setName(std::string name){
    Person::_name = name;
}

