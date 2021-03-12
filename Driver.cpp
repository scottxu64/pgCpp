#include "Driver.h"

#include <iostream>

using namespace std;

Driver::Driver(string name)
:Worker(name){
}

string Driver::getCareer(){
    return "driver";
}
