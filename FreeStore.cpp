#include "FreeStore.h"

using namespace std;

FreeStore::FreeStore(string name) 
	:_name(name)
{
	cout << "constructor called" << endl;
}

FreeStore::~FreeStore()
{
	cout << "destructor called" << endl;
}

