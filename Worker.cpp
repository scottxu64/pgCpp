#include "Worker.h"

#include <iostream>

using namespace std;

Worker::Worker(string name)
    :_name(name)
{}

string Worker::getName(){
    return _name;
}
