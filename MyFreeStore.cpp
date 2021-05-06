#include "MyFreeStore.h"

using namespace std;

MyFreeStore::MyFreeStore(string name) 
	:_name(name)
{
	cout << "constructor called" << endl;
}

MyFreeStore::~MyFreeStore()
{
	cout << "destructor called" << endl;
}

