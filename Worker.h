#ifndef WORKER_H
#define WORKER_H

#include <iostream>

using namespace std;

class Worker
{
    public:
        Worker(string);
        string getName();

        virtual string getCareer() =0;  // =0 means this is a pure virtual function. means no implementation in Worker class

    private:
        string _name;
};

#endif // WORKER_H
