#ifndef PERSON_H // ifndef = if not defined
#define PERSON_H
#include <iostream>

using namespace std; // This is a bad sample, should not use using statement in header, to avoid side effects

class Person
{
public:
	Person();
	~Person(); // destructor

	void setName(string name);
	string getName();
	string getNameUsingThisRef();
	string getNameUsingThisDeRef();

	// constant
	void methodForConstObj() const;

	Person(string name, string nameConst);
	string getNameConst();

	// operator overloading
	int asset;
	Person(int); // TODO: seems I don't need a var name here...
	Person operator+(Person); // naming rule: start with 'operator', then what to overloading: '+'

private:
	string _name;
	const string _nameConst;
};

#endif // PERSON_H
