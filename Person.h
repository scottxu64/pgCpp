#ifndef PERSON_H // ifndef = if not defined
#define PERSON_H
#include <iostream>

using namespace std; // This is a bad sample, should not use using statement in header, to avoid side effects

class Person
{
public:
	Person();		// if we don't have any logic, just want the empty default constructor, can simplify like: Person() = default
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
	Person operator+(int asset);

private:
	string _name;
	const string _nameConst;
	friend Person operator+(int __asset, Person& person);	// define friend method by copying the free function's signature and perpend keyword `friend`
};

Person operator+(int __asset, Person& person);	// notice this is a free function
												// so anywhere when signature matching (int, Person) this will work
												// if accidently put this operator overload in Person class, then the signature will be: Person + (int, Person)

#endif // PERSON_H
