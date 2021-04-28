#pragma once
#include <iostream>

class FreeStore
{
private:
	std::string _name;

public:
	FreeStore(std::string);
	~FreeStore();

	std::string GetName() const { return _name; }
};

