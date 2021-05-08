#include "Worker.h"

#include <iostream>

using namespace std;

Worker::Worker(string name)
    :_name(name)
{}

string Worker::getName() const{
    return _name;
}

string Worker::getCareer() {
    return "";
}

void Worker::addPet(string petName)
{
    pPet.reset();
    pPet = make_shared<MyFreeStore>(petName); // no nullptr at constructor; no new FreeStore() needed
}

const string Worker::getPetName()
{
    return pPet ? pPet->GetName() : "";
}
