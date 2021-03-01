#include "Team.h"
#include <iostream>
#include "Person.h"

using namespace std;

Team::Team(string name, Person leader)
:_name(name), _leader(leader)// "member initializer syntax" to assign object values to members
{}

Person Team::getLeader(){
    return _leader;
}

string Team::getName(){
    return _name;
}
