#include "Chef.h"
#include "Person.h"
#include <iostream>

using namespace std;

Chef::Chef(int asset):Person(asset){        // call super constructor with parameters sample, not super()
}

string Chef::getCareer(){
    return "chef";
}
