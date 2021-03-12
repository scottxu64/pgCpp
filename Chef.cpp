#include "Chef.h"
#include "Worker.h"
#include <iostream>

using namespace std;

Chef::Chef(string name)
    :Worker(name){        // like initializer syntax to call parent constructor
}

string Chef::getCareer(){   // step3: implement function
    return "chef";
}
