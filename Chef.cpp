#include "Chef.h"
#include "Worker.h"
#include <iostream>

using namespace std;

Chef::Chef(string name)
    :Worker(name){        // like initializer syntax to call parent constructor
}

string Chef::getName() const{
    return "chef " + Worker::getName();
}

string Chef::getCareer(){   // step3: implement function as usual
    return "chef";
}

Chef::Chef(string name, string career)
    :Worker(name), _career(career)
{}