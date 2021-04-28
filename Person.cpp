#include "Person.h"
// #include <iostream>     // This is already included in header file, when include header file, it will be copied over

using namespace std;

Person::Person() // class::method, here is the implementation of method.
:pPet(nullptr){
	cout << "person constructor" << endl;
}

Person::~Person()
{
	delete pPet;				// free store step 4: IMPORTANT: put delete logic in person destructor. so it will be destroyed along.
	cout << "person destructor" << endl;
}

void Person::setName(string name)
{
	_name = name;
}

string Person::getName()
{
	return _name;
}

string Person::getNameUsingThisRef()
{
	return this->_name; // this is a pointer to current object
}

string Person::getNameUsingThisDeRef()
{
	return (*this)._name;
}

// constant
void Person::methodForConstObj() const
{
	cout << "const method for const object" << endl;
}

Person::Person(string name, string nameConst)
	: _name(name), _nameConst(nameConst)
// "member initializer syntax" to assign values to const members (aka global variables aka field)
{
}

string Person::getNameConst()
{
	return _nameConst;
}

// operator overloading
Person::Person(int __asset)
{
	asset = __asset;
}

Person Person::operator+(Person oldPerson)
{
	Person newPerson;
	newPerson.asset = asset + oldPerson.asset;
	return newPerson;
}

Person Person::operator+(int __asset) 
{
	asset = asset + __asset;	// or: this->asset = this->asset + __asset;
	return *this;
}

Person operator+(int __asset, Person& person) {
	person.asset = person.asset + __asset;	// here by default can only access public members
	person._name;	// but if declared this operator overload as friend, then any member is accessible.
	return person;
}


// free store
void Person::addPet(string petName) {
	pPet = new FreeStore(petName);			// free store step 3: implement the add logic using free store
}
