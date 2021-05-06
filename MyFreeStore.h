#pragma once
#include <iostream>

class MyFreeStore
{
private:
	std::string _name;

public:
	MyFreeStore(std::string);
	~MyFreeStore();

	std::string GetName() const { return _name; }
};

