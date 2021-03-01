#ifndef TEAM_H
#define TEAM_H
#include "Person.h"
#include <iostream>

using namespace std;

class Team
{
    public:
        Team(string name, Person leader);
        Person getLeader();
        string getName();

    private:
        string _name;
        Person _leader; // when composition has person object, it must be initialized in constructor
};

#endif // TEAM_H
